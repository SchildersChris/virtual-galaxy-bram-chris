#include "rasterizer.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"
#include "../../components/camera.hpp"

#include "graphics/renderer.hpp"

#include <cmath>
#include <imgui.h>
#include <sys/param.h>

void Rasterizer::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();

    _zBufferSize = _width * _height;
    _zBuffer = new float[_zBufferSize];

    _projection = utils::getProjectionMatrix(_fov, _near, _far,
                                             static_cast<float>(_width) /
                                             static_cast<float>(_height));
}

void Rasterizer::update(float deltaTime) {
    if (!_registry || !_zBuffer) { return; }
    std::fill(_zBuffer, _zBuffer + _zBufferSize, _far);

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();

    static bool drawAxis = true;

    ImGui::Begin("Renderer");
    ImGui::Checkbox("Draw Axis", &drawAxis);
    if (ImGui::CollapsingHeader("Camera Position")) {
        ImGui::SliderFloat("X", &camTrans.Translation.X, -100, 100);
        ImGui::SliderFloat("Y", &camTrans.Translation.Y, -100, 100);
        ImGui::SliderFloat("Z", &camTrans.Translation.Z, -100, 100);
    }
    ImGui::End();

    auto& renderer = Renderer::getInstance();

    Vector3 t[3];
    Vector3 r[3];

    auto vp = _projection * camTrans.getMatrix();
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto mvp = vp * transform.getMatrix();

        for (int i = 0; i < object.Indices.size(); i += 3) {
            auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
            auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
            auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

            if (v0.W > 0 || v0.W < -_far ||
                v1.W > 0 || v1.W < -_far ||
                v2.W > 0 || v2.W < -_far) {
                continue;
            }

            t[0] = Vector3 { v0.X, v0.Y, v0.Z };
            t[1] = Vector3 { v1.X, v1.Y, v1.Z };
            t[2] = Vector3 { v2.X, v2.Y, v2.Z };

            r[0] = toRaster(v0);
            r[1] = toRaster(v1);
            r[2] = toRaster(v2);

            rasterizeTriangle(t, r);
        }

        if (drawAxis) {
            auto c = Vector3 { 0, 0, 0 } * mvp;
            auto x = Vector3 { 1, 0, 0 } * mvp;
            auto y = Vector3 { 0, 1, 0 } * mvp;
            auto z = Vector3 { 0, 0, 1 } * mvp;

            auto rC = toRaster(c);
            auto rX = toRaster(x);
            auto rY = toRaster(y);
            auto rZ = toRaster(z);

            renderer.drawLine({rC.X, rC.Y}, {rX.X, rX.Y}, Color::green());
            renderer.drawLine({rC.X, rC.Y}, {rY.X, rY.Y}, Color::red());
            renderer.drawLine({rC.X, rC.Y}, {rZ.X, rZ.Y}, Color::blue());
        }
    }
}

void Rasterizer::terminate() {
    delete[] _zBuffer;
}

void Rasterizer::rasterizeTriangle(const Vector3 t[3], const Vector3 r[3]) {
    auto& renderer = Renderer::getInstance();

    float rMaxY = std::max(r[0].Y, std::max(r[1].Y, r[2].Y));
    float rMinY = std::min(r[0].Y, std::min(r[1].Y, r[2].Y));
    float rMaxX = std::max(r[0].X, std::max(r[1].X, r[2].X));
    float rMinX = std::min(r[0].X, std::min(r[1].X, r[2].X));

    int32 w = _width - 1;
    int32 h = _height - 1;

    /*
     * We test whether the box is completely outside the raster image dimensions
     * if this is true we can immediately return
     */
    if (rMinX > static_cast<float>(w) || rMaxX < 0 || rMinY > static_cast<float>(h) || rMaxY < 0)
        return;

    // Calculate raster image bounding box
    int32 minY = std::max(0, static_cast<int32>(std::floor(rMinY)));
    int32 maxY = std::min(h, static_cast<int32>(std::floor(rMaxY)));
    int32 minX = std::max(0, static_cast<int32>(std::floor(rMinX)));
    int32 maxX = std::min(w, static_cast<int32>(std::floor(rMaxX)));

    // Triangle normal vector
    auto normal = (t[1] - t[0]).cross(t[2] - t[0]).normalize();

    // Total area of triangle
    float area = utils::edgeFunction(r[0], r[1], r[2]);

    for (int32 y = minY; y <= maxY; ++y) {
        for (int32 x = minX; x <= maxX; ++x) {
            Vector3 p = { static_cast<float>(x), static_cast<float>(y), 0 };

            float a[3] = {
                utils::edgeFunction(r[1], r[2], p),
                utils::edgeFunction(r[2], r[0], p),
                utils::edgeFunction(r[0], r[1], p)
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

            auto s = getShade(z, t, a, normal);

            renderer.drawPoint(x, y, Color(s, s, s, 255));
        }
    }
}

Vector3 Rasterizer::toRaster(const Vector4& v) const {
    return {
        (1 + v.X / v.Z) * 0.5f * static_cast<float>(_width),
        (1 - v.Y / v.Z) * 0.5f * static_cast<float>(_height),
        v.Z
    };
}

uint8 Rasterizer::getShade(float z, const Vector3 c[3], const float a[3], const Vector3& normal) const {
    float px = (c[0].X / -c[0].Z) * a[0] + (c[1].X / -c[1].Z) * a[1] + (c[2].X / -c[2].Z) * a[2];
    float py = (c[0].Y / -c[0].Z) * a[0] + (c[1].Y / -c[1].Z) * a[1] + (c[2].Y / -c[2].Z) * a[2];

    Vector3 viewDirection = {px * z, py * z, -z };
    return (uint8)(normal.dot(viewDirection.normalize()) * 255);
}

