#ifndef VIRTUAL_GALAXY_MOVEMENT_HPP
#define VIRTUAL_GALAXY_MOVEMENT_HPP

#include "core/system.hpp"

class Movement : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    entt::registry* _registry {nullptr};
};


#endif //VIRTUAL_GALAXY_MOVEMENT_HPP
