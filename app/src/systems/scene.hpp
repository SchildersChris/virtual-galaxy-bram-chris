#ifndef VIRTUAL_GALAXY_SCENE_HPP
#define VIRTUAL_GALAXY_SCENE_HPP

#include "base.hpp"
#include "core/system.hpp"

/**
 * Scene system handles scene activities such as loading objects and events (e.g. quit)
 */
class Scene : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;

private:
    uint32 _activeFps{};
    uint32 _fps{};
    float _step{};
};

#endif //VIRTUAL_GALAXY_SCENE_HPP
