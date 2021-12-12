#ifndef VIRTUAL_GALAXY_BUFFER_HPP
#define VIRTUAL_GALAXY_BUFFER_HPP

#include "base.hpp"

class Buffer {
public:
    Buffer(uint32* pixels, int32 width, int32 height) : _pixels(pixels), _width(width), _height(height) {}

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

private:
    uint32* _pixels;

    int32 _width;
    int32 _height;
};

#endif //VIRTUAL_GALAXY_BUFFER_HPP
