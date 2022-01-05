#include "wireframe.hpp"

#include "graphics/renderer.hpp"

void Wireframe::updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) {
    auto mvp = vp * m;
    auto& renderer = Renderer::getInstance();

    for (int i = 0; i < object.Indices.size(); i += 3) {
        // Fetch triangle points based on their respective indices
        auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
        auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
        auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

        // Clipping between viewing frustum
        if (v0.W > -_near || v0.W < -_far ||
            v1.W > -_near || v1.W < -_far ||
            v2.W > -_near || v2.W < -_far) {
            continue;
        }

        // Convert the points to raster coordinates
        auto r0 = renderer.toRaster(v0).toVector2();
        auto r1 = renderer.toRaster(v1).toVector2();
        auto r2 = renderer.toRaster(v2).toVector2();

        // Draw the triangle wireframe
        renderer.drawLine(r0, r1, object.BaseColor);
        renderer.drawLine(r1, r2, object.BaseColor);
        renderer.drawLine(r2, r0, object.BaseColor);
    }
    renderer.setColor(Color::black());
}
