#ifndef VIRTUAL_GALAXY_FRAME_HPP
#define VIRTUAL_GALAXY_FRAME_HPP

#include "base.hpp"
#include "renderer.hpp"

class Renderer;

/**
 * Frame representation
 */
class Frame : public NoCopyNoMove {
public:
    /**
     * Sets a pixel on the current frame
     *
     * @param p Index to render on the screen
     * @param r
     * @param g
     * @param b
     */
    void SetPixel(int32 p, uint8 r, uint8 g, uint8 b);

    void EndFrame();

private:
    // Todo: Take texture to render
    explicit Frame(Renderer& renderer) : _renderer(renderer) {};

    Renderer& _renderer;

    /*
     * Renderer is a friend of the frame, todo
     */
    friend class Renderer;
};


#endif //VIRTUAL_GALAXY_FRAME_HPP
