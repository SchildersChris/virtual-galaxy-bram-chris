#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"
#include "math/vector2.hpp"
#include "graphics/color.hpp"

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
     * @param color Clearing color
     */
    void setClearColor(Color color);

    /**
     * Start a new rendering frame
     */
    void beginFrame(float deltaTime);

    /**
     * Draw a point on the screen
     *
     * @param x X position to draw
     * @param y Y position to draw
     * @param color Color to draw with
     */
    void drawPoint(int32 x, int32 y, Color color);

    /**
     * Draw a points from p1 to p2 with a color
     *
     * @param p1 Starting point
     * @param p2 Ending point
     * @param color Line color
     */
    void drawLine(const Vector2& p1, const Vector2& p2, Color color);

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

    int32 _width {0};
    int32 _height {0};

    Color _clearColor {Color::black()};
};

#endif //VIRTUAL_GALAXY_RENDERER_HPP
