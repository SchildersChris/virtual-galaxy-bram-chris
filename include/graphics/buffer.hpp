#ifndef VIRTUAL_GALAXY_BUFFER_HPP
#define VIRTUAL_GALAXY_BUFFER_HPP

#include "base.hpp"

class Buffer {
public:
    explicit Buffer(uint32* pixels) : _pixels(pixels) {}

    /**
     * Sets a RGBA pixel on the buffer
     *
     * @param i Pixel index in the buffer
     * @param r Pixel red component
     * @param g Pixel green component
     * @param b Pixel blue component
     * @param a Pixel alpha component
     */
    void SetPixel(std::size_t i, uint8 r, uint8 g, uint8 b, uint8 a) {
        _pixels[i] = (a << 24) + (b << 16) + (g << 8) + r;
    }

private:
    uint32* _pixels;
};

#endif //VIRTUAL_GALAXY_BUFFER_HPP
