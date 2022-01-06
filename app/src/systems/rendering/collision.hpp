#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "../rendering-pipeline.hpp"

class Collision : public RenderingPipeline::Element {
public:
    void init(entt::registry& registry) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;

private:
    entt::registry* _registry {nullptr};
};

#endif //VIRTUAL_GALAXY_COLLISION_HPP
