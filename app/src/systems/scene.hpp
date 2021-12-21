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
    void terminate() override;

private:
    entt::registry* _registry {nullptr};

    entt::entity _fpsCamera {entt::null};
    entt::entity _worldCamera {entt::null};
    bool _isFpsCamera {false};

    uint32 _activeFps{};
    uint32 _fps{};
    float _step{};
};

#endif //VIRTUAL_GALAXY_SCENE_HPP
