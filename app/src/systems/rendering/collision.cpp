#include "collision.hpp"
#include "../../components/transform.hpp"

#include "math/vector4.hpp"
#include "../../components/collider.hpp"

void Collision::init(entt::registry& registry) {
    _registry = &registry;
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

    for (auto&& [e, transform, collider] : _registry->view<Transform, Collider>().each()) {
        if (entity == e) { continue; }

        auto otherMvp = vp * transform.getMatrix();
        auto otherCenter = Vector4 { 0, 0, 0, 1} * otherMvp;

        float otherMinX = otherCenter.X;
        float otherMaxX = otherCenter.X;
        float otherMinY = otherCenter.Y;
        float otherMaxY = otherCenter.Y;
        float otherMinZ = otherCenter.Z;
        float otherMaxZ = otherCenter.Z;

        for (int i = 0; i < object.Indices.size(); ++i) {
            auto v = object.Vertices[object.Indices[i] - 1] * otherMvp;

            if (v.X < otherMinX) { otherMinX = v.X; }
            if (v.X > otherMaxX) { otherMaxX = v.X; }

            if (v.Y < otherMinY) { otherMinY = v.Y; }
            if (v.Y > otherMaxY) { otherMaxY = v.Y; }

            if (v.Z < otherMinZ) { otherMinZ = v.Z; }
            if (v.Z > otherMaxZ) { otherMaxZ = v.Z; }
        }

        if ( (minX <= otherMaxX && maxX >= otherMinX) &&
             (minY <= otherMaxY && maxY >= otherMinY) &&
             (minZ <= otherMaxZ && maxZ >= otherMinZ)) {
            collider.OnCollide(entity);
        }
    }

}


