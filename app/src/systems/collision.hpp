#ifndef VIRTUAL_GALAXY_COLLISION_HPP
#define VIRTUAL_GALAXY_COLLISION_HPP

#include "core/system.hpp"

class Collision : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;
};


#endif //VIRTUAL_GALAXY_COLLISION_HPP