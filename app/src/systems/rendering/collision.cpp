#include "collision.hpp"
#include "../../components/transform.hpp"

#include "math/vector4.hpp"
#include "../../components/collider.hpp"

#include "graphics/renderer.hpp"
#include <imgui.h>

void Collision::init(entt::registry& registry, float near, float far) {
    _registry = &registry;
    _near = near;
    _far = far;
}

void Collision::update(float deltaTime) {
    ImGui::BeginChild("Collision");
    ImGui::Checkbox("Draw Collision", &_drawCollision);
    ImGui::EndChild();
}

void Collision::updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) {
    auto mvp = vp * m;
    auto center = Vector4 { 0, 0, 0, 1} * mvp;

    float minX = center.X;
    float maxX = center.X;

    float minY = center.Y;
    float maxY = center.Y;

    float minZ = center.Z;
    float maxZ = center.Z;

    for (int i = 0; i < object.Indices.size(); ++i) {
        auto v = object.Vertices[object.Indices[i] - 1] * mvp;

        if (v.X < minX) { minX = v.X; }
        if (v.X > maxX) { maxX = v.X; }

        if (v.Y < minY) { minY = v.Y; }
        if (v.Y > maxY) { maxY = v.Y; }

        if (v.Z < minZ) { minZ = v.Z; }
        if (v.Z > maxZ) { maxZ = v.Z; }
    }

    if (_drawCollision && center.W < -_near && center.W > -_far) {
        drawBox(Vector3 { minX, minY, minZ }, Vector3 { maxX, maxY, maxZ });
    }

    for (auto&& [e, transform, o, collider] : _registry->view<Transform, Object, Collider>().each()) {
        if (entity == e) { continue; }

        auto otherMvp = vp * transform.getMatrix();
        auto otherCenter = Vector4 { 0, 0, 0, 1} * otherMvp;

        float otherMinX = otherCenter.X;
        float otherMaxX = otherCenter.X;
        float otherMinY = otherCenter.Y;
        float otherMaxY = otherCenter.Y;
        float otherMinZ = otherCenter.Z;
        float otherMaxZ = otherCenter.Z;

        for (int i = 0; i < o.Indices.size(); ++i) {
            auto v = o.Vertices[o.Indices[i] - 1] * otherMvp;

            if (v.X < otherMinX) { otherMinX = v.X; }
            if (v.X > otherMaxX) { otherMaxX = v.X; }

            if (v.Y < otherMinY) { otherMinY = v.Y; }
            if (v.Y > otherMaxY) { otherMaxY = v.Y; }

            if (v.Z < otherMinZ) { otherMinZ = v.Z; }
            if (v.Z > otherMaxZ) { otherMaxZ = v.Z; }
        }

        if (_drawCollision && otherCenter.W < -_near && otherCenter.W > -_far) {
            drawBox(Vector3 { otherMinX, otherMinY, otherMinZ }, Vector3 { otherMaxX, otherMaxY, otherMaxZ });
        }

        if ( (minX <= otherMaxX && maxX >= otherMinX) &&
             (minY <= otherMaxY && maxY >= otherMinY) &&
             (minZ <= otherMaxZ && maxZ >= otherMinZ)) {
            collider.OnCollide(entity);
        }
    }

}

void Collision::drawBox(const Vector3& min, const Vector3& max) {
    auto& renderer = Renderer::getInstance();

    auto minP = renderer.toRaster(Vector4 { min.X, min.Y, min.Z, 1 }).toVector2();
    auto maxP = renderer.toRaster(Vector4 { max.X, max.Y, max.Z, 1 }).toVector2();

    auto minXP = renderer.toRaster(Vector4 { max.X, min.Y, min.Z, 1 }).toVector2();
    auto minYP = renderer.toRaster(Vector4 { min.X, max.Y, min.Z, 1 }).toVector2();
    auto minZP = renderer.toRaster(Vector4 { min.X, min.Y, max.Z, 1 }).toVector2();
    auto maxXP = renderer.toRaster(Vector4 { min.X, max.Y, max.Z, 1 }).toVector2();
    auto maxYP = renderer.toRaster(Vector4 { max.X, min.Y, max.Z, 1 }).toVector2();
    auto maxZP = renderer.toRaster(Vector4 { max.X, max.Y, min.Z, 1 }).toVector2();

    // Draw 3 lines (coordinate system) from min pos
    renderer.drawLine(minP, minXP, Color::magenta());
    renderer.drawLine(minP, minYP, Color::magenta());
    renderer.drawLine(minP, minZP, Color::magenta());

    // Draw 3 lines (coordinate system) from max pos
    renderer.drawLine(maxP, maxXP, Color::magenta());
    renderer.drawLine(maxP, maxYP, Color::magenta());
    renderer.drawLine(maxP, maxZP, Color::magenta());

    // Connect remaining points
    renderer.drawLine(maxXP, minZP, Color::magenta());
    renderer.drawLine(maxXP, minYP, Color::magenta());
    renderer.drawLine(maxYP, minZP, Color::magenta());
    renderer.drawLine(maxYP, minXP, Color::magenta());
    renderer.drawLine(maxZP, minYP, Color::magenta());
    renderer.drawLine(maxZP, minXP, Color::magenta());
}
