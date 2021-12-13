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

    Vector3 triangle[3];
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        for (int i = 0; i < object.Indices.size(); i += 3) {
            triangle[0] = object.Vertices[object.Indices[i]];
            triangle[1] = object.Vertices[object.Indices[i+1]];
            triangle[2] = object.Vertices[object.Indices[i+2]];

            rasterizeTriangle(frame, triangle);
        }
    }
}

void Render ::terminate() {
    delete[] _zBuffer;
}

void Render::rasterizeTriangle(Buffer& frame, Vector3 triangle[3]) {
    Vector2 r0 = toRaster(triangle[0].proj());
    Vector2 r1 = toRaster(triangle[1].proj());
    Vector2 r2 = toRaster(triangle[2].proj());

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

    int32 left, right;

    // Right
    if (v0.cross(v1) > 0) {
        left = static_cast<int32>(r0.X);
        right = static_cast<int32>(r1.X);
    } else { // Left
        right = static_cast<int32>(r0.X);
        left = static_cast<int32>(r1.X);
    }

    // Draw bottom to middle
    int32 y = bottom + 1;
    for(; y < middle; ++y) {
        for (int32 x = left; x < right; ++x) {
            frame.setPixel(x, y, 255, 255, 255, 255);
        }
    }

    // Draw middle to top
    for(; y < top; ++y) {
        for (int32 x = left; x < right; ++x) {
            frame.setPixel(x, y, 255, 255, 255, 255);
        }
    }
}

Vector2 Render::toRaster(const Vector2& v) const {
    return {
        (1 + v.X) * 0.5f * static_cast<float>(_width),
        (1 - v.Y) * 0.5f * static_cast<float>(_height)
    };
}
