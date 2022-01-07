#ifndef VIRTUAL_GALAXY_SHOOTING_HPP
#define VIRTUAL_GALAXY_SHOOTING_HPP

#include "../components/object.hpp"

#include "core/system.hpp"

class Shooting : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;

private:
    entt::registry* _registry {nullptr};
    Object _bullet {Color::white()};
};

#endif //VIRTUAL_GALAXY_SHOOTING_HPP
