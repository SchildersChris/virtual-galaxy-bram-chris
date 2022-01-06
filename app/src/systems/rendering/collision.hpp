#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "../rendering-pipeline.hpp"

class Collision : public RenderingPipeline::Element {
public:
    Collision(float near, float far) : _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;

private:
    entt::registry* _registry {nullptr};

    static void drawBox(const Vector3& min, const Vector3& max);

    bool _drawCollision {true};

    float _near;
    float _far;
};

#endif //VIRTUAL_GALAXY_COLLISION_HPP
