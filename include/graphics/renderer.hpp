#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"
#include "frame.hpp"

class Renderer : public NoCopyNoMove {
public:
    /**
     * Single point of access to the Renderer
     *
     * @return Singleton Renderer instance
     */
    static Renderer& GetInstance();

    /**
     * Start a new rendering frame;
     *
     * @return Current frame
     */
    Frame BeginFrame();

private:
    static Renderer _instance;

    /*
     * Frame is a friend of the renderer, todo
     */
    friend class Frame;
};



#endif //VIRTUAL_GALAXY_RENDERER_HPP
