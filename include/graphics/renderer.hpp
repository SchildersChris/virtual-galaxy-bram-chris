#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"
#include "buffer.hpp"

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
     * Get width of the window
     *
     * @return Window width
     */
    [[nodiscard]] int32 GetWidth() const;

    /**
     * Get height of the window
     *
     * @return Window height
     */
    [[nodiscard]] int32 GetHeight()const;

    /**
     * Start a new rendering frame;
     *
     * @return Active frame buffer
     */
    Buffer BeginFrame();

    /**
     * End a rendering frame
     *
     * @param frame Frame to end
     */
    void EndFrame();

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

    SDL_Texture* _surface {nullptr};

    int32 _width {0};
    int32 _height {0};
};

#endif //VIRTUAL_GALAXY_RENDERER_HPP
