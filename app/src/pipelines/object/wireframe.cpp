#include "wireframe.hpp"

#include "graphics/renderer.hpp"

void Wireframe::updateObject(const Matrix4x4& mvp, const Object& object) {
    auto& renderer = Renderer::getInstance();

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

        r[0] = renderer.toRaster(v0);
        r[1] = renderer.toRaster(v1);
        r[2] = renderer.toRaster(v2);

        auto r0 = Vector2 { r[0].X, r[0].Y };
        auto r1 = Vector2 { r[1].X, r[1].Y };
        auto r2 = Vector2 { r[2].X, r[2].Y };

        renderer.drawLine(r0, r1, object.BaseColor);
        renderer.drawLine(r1, r2, object.BaseColor);
        renderer.drawLine(r2, r0, object.BaseColor);
    }
    renderer.setColor(Color::black());
}
