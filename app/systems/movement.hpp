#ifndef VIRTUAL_GALAXY_MOVEMENT_HPP
#define VIRTUAL_GALAXY_MOVEMENT_HPP

#include "system.hpp"

class Movement : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
};


#endif //VIRTUAL_GALAXY_MOVEMENT_HPP
