#include "rasterizer2.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"
#include "../../components/camera.hpp"

#include "graphics/renderer.hpp"

#include <cmath>
#include <imgui.h>

void Rasterizer2::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();

    _texture = renderer.createTexture(_width, _height);

    _zBufferSize = _width * _height;
    _zBuffer = new float[_zBufferSize];
}

void Rasterizer2::update(float deltaTime) {
    if (!_registry || !_zBuffer) { return; }
    std::fill(_zBuffer, _zBuffer + _zBufferSize, _far);

    auto& renderer = Renderer::getInstance();

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();

    static bool drawAxis = true;

    ImGui::Begin("Renderer");
    ImGui::Checkbox("Test", &drawAxis);
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

    {
        auto stream = _texture->lock();
        stream.clear(Color::black());
        Vector3 t[3];
        Vector3 r[3];

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

                r[0] = toRaster(t[0]);
                r[1] = toRaster(t[1]);
                r[2] = toRaster(t[2]);

                rasterizeTriangle(t, r, camTrans.Translation, stream);
            }
        }
    }

    Renderer::getInstance().drawTexture(*_texture);
}

void Rasterizer2 ::terminate() {
    delete[] _zBuffer;
}

void Rasterizer2::rasterizeTriangle(const Vector3 t[3], const Vector3 r[3], const Vector3& light, Texture::Stream& stream) {
    // Back-face culling
    auto normal = (t[1] - t[0]).cross(t[2] - t[0]).normalize();
    if (normal.length() < 0) { return; }

    float rMaxY = std::max(r[0].Y, std::max(r[1].Y, r[2].Y));
    float rMinY = std::min(r[0].Y, std::min(r[1].Y, r[2].Y));
    float rMaxX = std::max(r[0].X, std::max(r[1].X, r[2].X));
    float rMinX = std::min(r[0].X, std::min(r[1].X, r[2].X));

    int w = _width - 1;
    int h = _height - 1;

    /*
     * We test weather the box is completely out side of the raster image dimensions
     * if this is true we can immediately return
     */
    if (rMinX > (float)w || rMaxX < 0 || rMinY > (float)h || rMaxY < 0)
        return;

    // Calculate raster image bounding box
    int minY = std::max(0, (int)floorf(rMinY));
    int maxY = std::min(h, (int)floorf(rMaxY));
    int minX = std::max(0, (int)floorf(rMinX));
    int maxX = std::min(w, (int)floorf(rMaxX));

    // Total area of triangle
    float area = edgeFunction(&r[0], &r[1], &r[2]);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            Vector3 p = { (float)x, (float)y, 0 };

            float a[3] = {
                edgeFunction(&r[1], &r[2], &p),
                edgeFunction(&r[2], &r[0], &p),
                edgeFunction(&r[0], &r[1], &p)
            };

            if (a[0] < 0 || a[1] < 0 || a[2] < 0)
                continue;

            a[0] /= area;
            a[1] /= area;
            a[2] /= area;

            float z = 1 / (r[0].Z * a[0] + r[1].Z * a[1] + r[2].Z * a[2]);
            if (z >= _zBuffer[y * _width + x])
                continue;

            _zBuffer[y * _width + x] = z;
            auto s = getShade(light, normal);
            auto c = static_cast<uint8>(s * 255);
            stream.setPixel(y * _width + x, Color(c, c, c, 255));
        }
    }
}

Vector3 Rasterizer2::toRaster(const Vector3& v) const {
    return {
        (1 + v.X / v.Z) * 0.5f * static_cast<float>(_width),
        (1 - v.Y / v.Z) * 0.5f * static_cast<float>(_height),
        -v.Z
    };
}

//
float Rasterizer2::getShade(const Vector3& light, const Vector3& normal) {
    return std::abs(normal.dot(light));
}

// unsigned char Rasterizer2::getPixelShade(float z, const Vector3 c[3], const float a[3]) {
//    /*
//     * Interpolate correct shade value distribution using barycentric coordinate system.
//     * Later this value will be used as scalar value together with the actual triangle shade color.
//     */
//    float px = (c[0].X / -c[0].Z) * a[0] + (c[1].X / -c[1].Z) * a[1] + (c[2].X / -c[2].Z) * a[2];
//    float py = (c[0].Y / -c[0].Z) * a[0] + (c[1].Y / -c[1].Z) * a[1] + (c[2].Y / -c[2].Z) * a[2];
//
//    Vector3 viewDirection = {px * -z, py * -z, z };
//    Vector3 nViewDirection = viewDirection.normalize();
//
//    Vector3 line1 = c[1] - c[0];
//    Vector3 line2 = c[2] - c[0];
//    Vector3 cross = line1.cross(line2);
//
//    Vector3 nCamera = cross.normalize();
//
//    return (unsigned char)std::max(0.f, nCamera.dot(nViewDirection) * 255);
//}

float Rasterizer2::edgeFunction(const Vector3* v1, const Vector3* v2, const Vector3* p) {
    return (p->X - v1->X) * (v2->Y - v1->Y) - (p->Y - v1->Y) * (v2->X - v1->X);
}
