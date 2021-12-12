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
    static Renderer& getInstance();

    /**
     * Initialize a window and the active renderer
     */
    void init(const std::string& title, bool fullscreen, int32 width, int32 height);

    /**
     * Get renderer window width
     *
     * @return Window width
     */
    [[nodiscard]] int32 getWidth() const;

    /**
     * Get renderer window height
     *
     * @return Window height
     */
    [[nodiscard]] int32 getHeight() const;

    /**
     * Set renderer clear color after each frame
     *
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     */
    void setClearColor(uint8 r, uint8 g, uint8 b);

    /**
     * Start a new rendering frame;
     *
     * @return Active frame buffer
     */
    Buffer beginFrame();

    /**
     * End a rendering frame
     *
     * @param frame Frame to end
     */
    void endFrame();

    /**
     * Terminate window and active renderer
     */
    void terminate();

private:
    static Renderer _instance;

    Renderer() = default;
    ~Renderer() override = default;

    SDL_Window* _window {nullptr};
    SDL_Renderer* _renderer {nullptr};

    SDL_Texture* _texture {nullptr};

    int32 _width {0};
    int32 _height {0};

    uint32 _clearColor {0};
};

#endif //VIRTUAL_GALAXY_RENDERER_HPP
