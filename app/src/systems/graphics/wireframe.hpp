#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "core/system.hpp"

class Wireframe : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;
};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
