#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "../../systems/object-pipeline.hpp"

class Collision : public ObjectPipeline::Element {
public:
    void init(entt::registry& registry) override;

private:
    entt::registry* _registry {nullptr};
};

#endif //VIRTUAL_GALAXY_COLLISION_HPP
