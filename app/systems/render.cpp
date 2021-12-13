#include "render.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"

#include <graphics/renderer.hpp>
#include <math/vector2.hpp>
#include <cmath>

void Render::init(entt::registry& registry) {
    _registry = &registry;

    // Setup z-buffer algorithm
    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();

    _zBufferSize = _width * _height;
    _zBuffer = new float[_zBufferSize];
}

void Render::update(float deltaTime, Buffer& frame) {
    if (!_registry || !_zBuffer) { return; }

    std::fill(_zBuffer, _zBuffer + _zBufferSize, _far);

    Vector3 light = {0.f, 0.f, 1.f};
    Vector3 triangle[3];
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        for (int i = 0; i < object.Indices.size(); i += 3) {
            triangle[0] = object.Vertices[object.Indices[i] - 1];
            triangle[1] = object.Vertices[object.Indices[i+1] - 1];
            triangle[2] = object.Vertices[object.Indices[i+2] - 1];

            rasterizeTriangle(frame, triangle, light);
        }
    }
}

void Render ::terminate() {
    delete[] _zBuffer;
}

void Render::rasterizeTriangle(Buffer& frame, const Vector3 t[3], const Vector3& light) {
    // Back-face culling
    auto normal = (t[1] - t[0]).cross(t[2] - t[0]).normalize();
//    if (normal.Z < 0) { return; }

    Vector2 r0 = toRaster(t[0].proj());
    Vector2 r1 = toRaster(t[1].proj());
    Vector2 r2 = toRaster(t[2].proj());

    // Sort all points from top (0) to bottom (2) using the Y component
    if (r2.Y > r1.Y) { std::swap(r2, r1); }
    if (r1.Y > r0.Y) { std::swap(r1, r0); }
    if (r2.Y > r0.Y) { std::swap(r2, r0); }

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
    std::function<std::tuple<int32, float, int32, float>(float)> interp;
    if (v0.cross(v1) > 0) {
        interp = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r2.X, r2.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[2].Z, t[2].Y, y),
                static_cast<int32>(interpAtoB(r1.X, r1.Y, r2.X, r2.Y, y)),
                interpAtoB(t[1].Z, t[1].Y, t[2].Z, t[2].Y, y)
            );
        };
    } else {
        interp = [&](float y) {
            return std::make_tuple(
                static_cast<int32>(interpAtoB(r1.X, r1.Y, r2.X, r2.Y, y)),
                interpAtoB(t[1].Z, t[1].Y, t[2].Z, t[2].Y, y),
                static_cast<int32>(interpAtoB(r0.X, r0.Y, r2.X, r2.Y, y)),
                interpAtoB(t[0].Z, t[0].Y, t[2].Z, t[2].Y, y)
            );
        };
    }

    auto y = bottom + 1;
    if (middle > bottom) {
        for(; y < middle; ++y) {
            auto [l, zL, r, zR] = interp(static_cast<float>(y));
            for (auto x = l; x < r; ++x) {

                auto i = x + y * _width;
                auto z = interpAtoB(zL, static_cast<float>(l), zR, static_cast<float>(r), static_cast<float>(x));
                if (_zBuffer[i] < z) { continue; }
                _zBuffer[i] = z;

                auto s = getShade(light, normal);
                auto c = static_cast<uint8>(s * 255);
                frame.setPixel(i, c, c, c, 255);
            }
        }
    }

    if (top > middle) {
        for(; y < top; ++y) {
            auto [l, zL, r, zR] = interp(static_cast<float>(y));
            for (auto x = l; x < r; ++x) {

                auto i = x + y * _width;
                auto z = interpAtoB(zL, static_cast<float>(l), zR, static_cast<float>(r), static_cast<float>(x));
                if (_zBuffer[i] < z) { continue; }
                _zBuffer[i] = z;

                auto s = getShade(light, normal);
                auto c = static_cast<uint8>(s * 255);
                frame.setPixel(i, c, c, c, 255);
            }
        }
    }
}

Vector2 Render::toRaster(const Vector2& v) const {
    return {
        (1 + v.X) * 0.5f * static_cast<float>(_width),
        (1 - v.Y) * 0.5f * static_cast<float>(_height)
    };
}

float Render::getShade(const Vector3& light, const Vector3& normal) {
    return std::abs(normal.dot(light));
}

float Render::interpAtoB(float fromA, float fromB, float toA, float toB, float atB) {
    return fromA - (fromA - toA) * ((fromB - atB) / (fromB - toB));
}

