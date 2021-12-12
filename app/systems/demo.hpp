#ifndef VIRTUAL_GALAXY_DEMO_HPP
#define VIRTUAL_GALAXY_DEMO_HPP

#include "system.hpp"

class Demo : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
    void terminate() override;
};



#endif //VIRTUAL_GALAXY_DEMO_HPP
