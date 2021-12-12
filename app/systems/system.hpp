#ifndef VIRTUAL_GALAXY_SYSTEM_HPP
#define VIRTUAL_GALAXY_SYSTEM_HPP

#include "graphics/buffer.hpp"

#include "entity/registry.hpp"

class System {
public:
    /**
     * Init is called to initialize the system with the component registry
     *
     * @param registry Component registry
     */
    virtual void init(entt::registry& registry) = 0;

    /**
     * Update is called every frame
     *
     * @param deltaTime Frame delta time
     * @param frame Active frame buffer
     */
    virtual void update(float deltaTime, Buffer& frame) = 0;
};

#endif //VIRTUAL_GALAXY_SYSTEM_HPP
