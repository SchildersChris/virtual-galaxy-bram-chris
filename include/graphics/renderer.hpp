#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"

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
     * Start a new rendering frame
     */
    void beginFrame(float deltaTime);

    /**
     * Sets a RGBA pixel on the buffer
     *
     * @param x X component in the buffer index
     * @param y Y component in the buffer index
     * @param r Pixel red component
     * @param g Pixel green component
     * @param b Pixel blue component
     * @param a Pixel alpha component
     */
    void setPixel(int32 x, int32 y, uint8 r, uint8 g, uint8 b, uint8 a);

    /**
     * Sets a RGBA pixel on the buffer
     *
     * @param i Pixel index in the buffer
     * @param r Pixel red component
     * @param g Pixel green component
     * @param b Pixel blue component
     * @param a Pixel alpha component
     */
    void setPixel(int32 i, uint8 r, uint8 g, uint8 b, uint8 a);

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
    uint32* _activeBuffer {nullptr};

    int32 _width {0};
    int32 _height {0};

    uint32 _clearColor {0};
};

#endif //VIRTUAL_GALAXY_RENDERER_HPP
