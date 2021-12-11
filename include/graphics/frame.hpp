#ifndef VIRTUAL_GALAXY_FRAME_HPP
#define VIRTUAL_GALAXY_FRAME_HPP

#include "base.hpp"
class Renderer;

/**
 * Frame representation
 */
class Frame : public NoCopyNoMove {
public:
    void SetPixel(int32 p, uint8 r, uint8 g, uint8 b);

    void EndFrame();

private:
    explicit Frame(Renderer& renderer) : _renderer(renderer) {};

    Renderer& _renderer;

    /*
     * Renderer is a friend of the frame, todo
     */
    friend class Renderer;
};


#endif //VIRTUAL_GALAXY_FRAME_HPP
