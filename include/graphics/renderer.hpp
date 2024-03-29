#ifndef VIRTUAL_GALAXY_RENDERER_HPP
#define VIRTUAL_GALAXY_RENDERER_HPP

#include "base.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"
#include "math/vector4.hpp"
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
    void init(const std::string& title, bool fullscreen);

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
    void setColor(Color color);

    /**
     * Start a new rendering frame
     */
    void beginFrame(float deltaTime);

    /**
     * Draw a point on the screen
     *
     * @param x X position to draw
     * @param y Y position to draw
     */
    void drawPoint(int32 x, int32 y);

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
     * Convert a vector4 to its respective raster coordinate by using perspective divide.
     * While reserving the z coordinate for later use.
     *
     * @param v Vector to convert to raster coordinate
     * @return Raster coordinate
     */
    [[nodiscard]] Vector3 toRaster(const Vector4& v) const;

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

    Color _color {Color::black()};
};

#endif //VIRTUAL_GALAXY_RENDERER_HPP
