#include "rasterizer.hpp"

#include "graphics/renderer.hpp"
#include "math/utils.hpp"

#include <cmath>

void Rasterizer::init(entt::registry& registry) {
    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();

    _zBufferSize = _width * _height;
    _zBuffer = new float[_zBufferSize];
}

void Rasterizer::update(float deltaTime) {
    assert(_zBuffer);
    std::fill(_zBuffer, _zBuffer + _zBufferSize, _far);
}

void Rasterizer::updateObject(const Matrix4x4& mvp, const Object& object) {
    auto& renderer = Renderer::getInstance();

    Vector3 t[3];
    Vector3 r[3];
    for (int i = 0; i < object.Indices.size(); i += 3) {
        auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
        auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
        auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

        if (v0.W > -_near || v0.W < -_far ||
            v1.W > -_near || v1.W < -_far ||
            v2.W > -_near || v2.W < -_far) {
            continue;
        }
        t[0] = Vector3 { v0.X, v0.Y, v0.Z };
        t[1] = Vector3 { v1.X, v1.Y, v1.Z };
        t[2] = Vector3 { v2.X, v2.Y, v2.Z };

        r[0] = renderer.toRaster(v0);
        r[1] = renderer.toRaster(v1);
        r[2] = renderer.toRaster(v2);


        auto shade = getShade((t[1] - t[0]).cross(t[2] - t[0]).normalize());
        renderer.setColor(object.BaseColor * shade);

        rasterizeTriangle(r);
    }
    renderer.setColor(Color::black());

}

void Rasterizer::terminate() {
    delete[] _zBuffer;
}

void Rasterizer::rasterizeTriangle(const Vector3 r[3]) {
    assert(_zBuffer);
    auto& renderer = Renderer::getInstance();

    auto r0 = Vector2 { r[0].X, r[0].Y };
    auto r1 = Vector2 { r[1].X, r[1].Y };
    auto r2 = Vector2 { r[2].X, r[2].Y };

    float rMaxY = std::max(r0.Y, std::max(r1.Y, r2.Y));
    float rMinY = std::min(r0.Y, std::min(r1.Y, r2.Y));
    float rMaxX = std::max(r0.X, std::max(r1.X, r2.X));
    float rMinX = std::min(r0.X, std::min(r1.X, r2.X));

    int32 w = _width - 1;
    int32 h = _height - 1;
    if (rMinX > static_cast<float>(w) || rMaxX < 0 || rMinY > static_cast<float>(h) || rMaxY < 0)
        return;

    int32 minY = std::max(0, static_cast<int32>(std::floor(rMinY)));
    int32 maxY = std::min(h, static_cast<int32>(std::floor(rMaxY)));
    int32 minX = std::max(0, static_cast<int32>(std::floor(rMinX)));
    int32 maxX = std::min(w, static_cast<int32>(std::floor(rMaxX)));

    // Total area of triangle
    float area = utils::edgeFunction(r0, r1, r2);

    for (int32 y = minY; y <= maxY; ++y) {
        for (int32 x = minX; x <= maxX; ++x) {
            Vector2 p = { static_cast<float>(x), static_cast<float>(y) };

            float a[3] = {
                utils::edgeFunction(r1, r2, p),
                utils::edgeFunction(r2, r0, p),
                utils::edgeFunction(r0, r1, p)
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

            renderer.drawPoint(x, y);
        }
    }
}

float Rasterizer::getShade(const Vector3& normal) {
    return normal.dot(Vector3 { 0, 0, 1 });
}