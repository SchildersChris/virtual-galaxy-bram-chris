#ifndef VIRTUAL_GALAXY_RENDER_HPP
#define VIRTUAL_GALAXY_RENDER_HPP

#include "system.hpp"

class Render : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
};


#endif //VIRTUAL_GALAXY_RENDER_HPP
