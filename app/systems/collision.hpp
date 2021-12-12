#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "system.hpp"

class Collision : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
};


#endif //VIRTUAL_GALAXY_COLLISION_HPP
