#include "rasterizer.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"
#include "../../components/camera.hpp"

#include "graphics/renderer.hpp"
#include "math/vector2.hpp"

#include <cmath>
#include <imgui.h>

void Rasterizer::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();

    _texture = renderer.createTexture(_width, _height);

    _zBufferSize = _width * _height;
    _zBuffer = new float[_zBufferSize];
}

void Rasterizer::update(float deltaTime) {
    if (!_registry || !_zBuffer) { return; }

    auto& renderer = Renderer::getInstance();

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();

    static bool drawAxis = true;

    ImGui::Begin("Renderer");
    ImGui::Checkbox("Draw Axis", &drawAxis);
    if (ImGui::CollapsingHeader("Camera Transform")) {
        ImGui::Text("Translation");
        ImGui::SliderFloat("Tx", &camTrans.Translation.X, -40, 40);
        ImGui::SliderFloat("Ty", &camTrans.Translation.Y, -40, 40);
        ImGui::SliderFloat("Tz", &camTrans.Translation.Z, -40, 40);
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Rx", &camTrans.Rotation.X, -40, 40);
        ImGui::SliderFloat("Ry", &camTrans.Rotation.Y, -40, 40);
        ImGui::SliderFloat("Rz", &camTrans.Rotation.Z, -40, 40);
        ImGui::Text("Scale");
        ImGui::SliderFloat("Sx", &camTrans.Scale.X, -40, 40);
        ImGui::SliderFloat("Sy", &camTrans.Scale.Y, -40, 40);
        ImGui::SliderFloat("Sz", &camTrans.Scale.Z, -40, 40);
    }
    ImGui::End();

    std::fill(_zBuffer, _zBuffer + _zBufferSize, _far);

    {
        auto stream = _texture->lock();
        stream.clear(Color::black());

        Vector3 t[3];
        auto vp = _projection * camTrans.getMatrix();

        for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
            auto mvp = vp * transform.getMatrix();

            for (int i = 0; i < object.Indices.size(); i += 3) {
                auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
                auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
                auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

                if (v0.W > 0 || v1.W > 0 || v2.W > 0) {
                    continue;
                }

                t[0] = Vector3 { v0.X, v0.Y, v0.Z };
                t[1] = Vector3 { v1.X, v1.Y, v1.Z };
                t[2] = Vector3 { v2.X, v2.Y, v2.Z };

                rasterizeTriangle(t, camTrans.Translation, stream);
            }
        }
    }

    Renderer::getInstance().drawTexture(*_texture);

}

void Rasterizer ::terminate() {
    delete[] _zBuffer;
}

void Rasterizer::rasterizeTriangle(const Vector3 t[3], const Vector3& light, Texture::Stream& stream) {
    // Back-face culling
    auto normal = (t[1] - t[0]).cross(t[2] - t[0]).normalize();
    if (normal.length() < 0) { return; }

    Vector2 r0 = toRaster(t[0]);
    Vector2 r1 = toRaster(t[1]);
    Vector2 r2 = toRaster(t[2]);

    // Sort all points from top (0) to bottom (2) using the Y component
    if (r2.Y > r0.Y) { std::swap(r2, r0); }
    if (r1.Y > r0.Y) { std::swap(r1, r0); }
    if (r1.Y > r2.Y) { std::swap(r2, r1); }

    auto top = static_cast<int32>(r0.Y);
    auto middle = static_cast<int32>(r1.Y);
    auto bottom = static_cast<int32>(r2.Y);

    // Check if there is any surface between the triangle top and bottom.
    if(top == bottom) { return; }

    /*
     * Cross product between the top of the triangle and the bottom.
     * This will determine whether the bend is on the left or right:
     *
     * We take the directional vectors:
     * v0 = r1 - r2
     * v1 = r0 - r2
     *
     * Followed by the cross product
     * x = v0 x v1
     *
     * Where x < 0 means the bend is on the right side
     */
    auto v0 = r1 - r2;
    auto v1 = r0 - r2;

    /*
     * Todo: Cleanup and impl correct bresenham algorithm
     */
    std::function<std::tuple<int32, float, int32, float>(float)> interpTop;
    std::function<std::tuple<int32, float, int32, float>(float)> interpBottom;

    if (v0.cross(v1) > 0) {
        interpBottom = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r2.X, r2.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[2].Z, t[2].Y, y),
                static_cast<int32>(interpAtoB(r1.X, r1.Y, r2.X, r2.Y, y)),
                interpAtoB(t[1].Z, t[1].Y, t[2].Z, t[2].Y, y)
            );
        };
        interpTop = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r2.X, r2.Y, r0.X, r0.Y, y)),
                interpAtoB(t[2].Z, t[2].Y, t[0].Z, t[0].Y, y),
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r1.X, r1.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[1].Z, t[1].Y, y)
            );
        };
    } else {
        interpBottom = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r2.X, r2.Y, r1.X, r1.Y, y)),
                interpAtoB(t[2].Z, t[2].Y, t[1].Z, t[1].Y, y),
                static_cast<int32>(interpAtoB(r2.X, r2.Y, r0.X, r0.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[2].Z, t[2].Y, y)
            );
        };
        interpTop = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r1.X, r1.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[1].Z, t[1].Y, y),
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r2.X, r2.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[2].Z, t[2].Y, y)
            );
        };
    }

    auto& renderer = Renderer::getInstance();

    auto y = bottom;
    if (bottom < middle) {
        for(; y < middle; ++y) {
            auto [l, zL, r, zR] = interpBottom(static_cast<float>(y));
            for (auto x = l; x < r; ++x) {

                auto i = x + y * _width;
                auto z = interpAtoB(zL, static_cast<float>(l), zR, static_cast<float>(r), static_cast<float>(x));
                if (_zBuffer[i] < z) { continue; }
                _zBuffer[i] = z;

                auto s = getShade(light, normal);
                auto c = static_cast<uint8>(s * 255);
                stream.setPixel(i, Color::white());
            }
        }
    }

    if (middle < top) {
        for(; y < top; ++y) {
            auto [l, zL, r, zR] = interpTop(static_cast<float>(y));
            for (auto x = l; x < r; ++x) {

                auto i = x + y * _width;
                auto z = interpAtoB(zL, static_cast<float>(l), zR, static_cast<float>(r), static_cast<float>(x));
                if (_zBuffer[i] < z) { continue; }
                _zBuffer[i] = z;

                auto s = getShade(light, normal);
                auto c = static_cast<uint8>(s * 255);
                stream.setPixel(i, Color::white());
            }
        }
    }
}

Vector2 Rasterizer::toRaster(const Vector3& v) const {
    return {
            (1 + v.X / v.Z) * 0.5f * static_cast<float>(_width),
            (1 - v.Y / v.Z) * 0.5f * static_cast<float>(_height),
    };
}

float Rasterizer::getShade(const Vector3& light, const Vector3& normal) {
    return std::abs(normal.dot(light));
}

float Rasterizer::interpAtoB(float fromA, float fromB, float toA, float toB, float atB) {
    return fromA - (fromA - toA) * ((fromB - atB) / (fromB - toB));
}