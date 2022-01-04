#include "wireframe.hpp"

#include "graphics/renderer.hpp"

void Wireframe::updateObject(const Matrix4x4& mvp, const Object& object) {
    auto& renderer = Renderer::getInstance();

    for (int i = 0; i < object.Indices.size(); i += 3) {
        auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
        auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
        auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

        if (v0.W > -_near || v0.W < -_far ||
            v1.W > -_near || v1.W < -_far ||
            v2.W > -_near || v2.W < -_far) {
            continue;
        }

        auto r0 = renderer.toRaster(v0).toVector2();
        auto r1 = renderer.toRaster(v1).toVector2();
        auto r2 = renderer.toRaster(v2).toVector2();

        renderer.drawLine(r0, r1, object.BaseColor);
        renderer.drawLine(r1, r2, object.BaseColor);
        renderer.drawLine(r2, r0, object.BaseColor);
    }
    renderer.setColor(Color::black());
}
