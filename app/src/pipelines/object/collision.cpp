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
        else if (v.X > maxX) { maxX = v.X; }

        if (v.Y < minY) { minY = v.Y; }
        else if (v.Y > maxY) { maxY = v.Y; }

        if (v.Z < minZ) { minZ = v.Z; }
        else if (v.Z > maxZ) { maxZ = v.Z; }
    }

    for (auto&& [e, transform, collider] : _registry->view<Transform, Collider>().each()) {
        if (entity == e) { continue; }

        auto colliderMvp = vp * transform.getMatrix();
        auto colliderCenter = Vector4 { 0, 0, 0, 1} * colliderMvp;

        if (colliderCenter.X > minX && colliderCenter.X < maxX &&
            colliderCenter.Y > minY && colliderCenter.Y < maxY &&
            colliderCenter.Z > minZ && colliderCenter.Z < maxZ) {
            collider.OnCollide(entity);
        }
    }

}


