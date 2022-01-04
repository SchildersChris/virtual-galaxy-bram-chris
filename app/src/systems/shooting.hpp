#ifndef VIRTUAL_GALAXY_SHOOTING_HPP
#define VIRTUAL_GALAXY_SHOOTING_HPP

#include "core/system.hpp"
#include "../components/object.hpp"

class Shooting : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    entt::registry* _registry {nullptr};
    Object _bullet {Color::white()};
};

#endif //VIRTUAL_GALAXY_SHOOTING_HPP
