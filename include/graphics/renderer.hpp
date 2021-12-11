#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"
#include "frame.hpp"

#include "SDL.h"

class Renderer : public NoCopyNoMove {
public:
    /**
     * Single point of access to the renderer
     *
     * @return Singleton renderer instance
     */
    static Renderer& GetInstance();

    /**
     * Initialize a window and the active renderer
     */
    void Init(const std::string& title, bool fullscreen, int32 width, int32 height);

    /**
     * Start a new rendering frame;
     *
     * @return Current frame
     */
    Frame BeginFrame();

    /**
     * Terminate window and active renderer
     */
    void Terminate();

private:
    static Renderer _instance;

    Renderer() = default;
    ~Renderer() override = default;

    SDL_Window* _window {nullptr};
    SDL_Renderer* _renderer {nullptr};

    /*
     * Frame is a friend of the renderer, todo
     */
    friend class Frame;
};



#endif //VIRTUAL_GALAXY_RENDERER_HPP
