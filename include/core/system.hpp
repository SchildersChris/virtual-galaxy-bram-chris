#ifndef VIRTUAL_GALAXY_SYSTEM_HPP
#define VIRTUAL_GALAXY_SYSTEM_HPP

#include "entity/registry.hpp"

class System {
public:
    /**
     * Init is called to initialize the system, providing
     * the active component registry
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
    virtual void update(float deltaTime) = 0;

    /**
     * Terminate is called to shutdown the system and cleanup all the resources.
     */
    virtual void terminate() = 0;
};

#endif //VIRTUAL_GALAXY_SYSTEM_HPP
