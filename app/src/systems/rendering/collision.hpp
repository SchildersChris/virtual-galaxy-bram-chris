#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "../rendering-pipeline.hpp"

class Collision : public RenderingPipeline::Element {
public:
    void init(entt::registry& registry, float nearClipping, float farClipping) override;
    void update(float deltaTime) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;

private:
    entt::registry* _registry {nullptr};

    static void drawBox(const Vector3& min, const Vector3& max);

    bool _drawCollision {true};

    float _near {0};
    float _far {0};
};

#endif //VIRTUAL_GALAXY_COLLISION_HPP
