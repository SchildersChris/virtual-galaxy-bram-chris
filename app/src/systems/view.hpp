#ifndef VIRTUAL_GALAXY_VIEW_HPP
#define VIRTUAL_GALAXY_VIEW_HPP

#include "core/system.hpp"

class View : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    entt::registry* _registry {nullptr};

    entt::entity _fpsCamera {entt::null};
    entt::entity _worldCamera {entt::null};
    bool _isFpsCamera {false};
};


#endif //VIRTUAL_GALAXY_VIEW_HPP
