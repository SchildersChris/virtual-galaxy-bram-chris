#ifndef VIRTUAL_GALAXY_SCALING_HPP
#define VIRTUAL_GALAXY_SCALING_HPP

#include "core/system.hpp"

class Scaling : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;

private:
    entt::registry* _registry {nullptr};

    float _timer {0};
};


#endif //VIRTUAL_GALAXY_SCALING_HPP
