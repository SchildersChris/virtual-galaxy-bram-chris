#ifndef VIRTUAL_GALAXY_MOVEMENT_HPP
#define VIRTUAL_GALAXY_MOVEMENT_HPP

#include "core/system.hpp"

class Movement : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;

private:
    void playerMovement(float deltaTime) const;
    void cameraMovement(float deltaTime) const;

    float _rotationSpeed {0.1f};
    float _movementSpeed {0.02f};
    entt::registry* _registry {nullptr};
};


#endif //VIRTUAL_GALAXY_MOVEMENT_HPP
