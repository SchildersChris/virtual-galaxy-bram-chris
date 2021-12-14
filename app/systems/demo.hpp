#ifndef VIRTUAL_GALAXY_DEMO_HPP
#define VIRTUAL_GALAXY_DEMO_HPP

#include "base.hpp"
#include "system.hpp"

class Demo : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    entt::registry* _registry {nullptr};

    uint32 _activeFps{};
    uint32 _fps{};
    float _step{};
};



#endif //VIRTUAL_GALAXY_DEMO_HPP
