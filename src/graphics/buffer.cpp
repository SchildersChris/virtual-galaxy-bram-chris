#include "graphics/buffer.hpp"
#include "utils/color.hpp"

void Buffer::setPixel(int32 x, int32 y, uint8 r, uint8 g, uint8 b, uint8 a) {
    _pixels[x + y * _width] = color::rgbaToInteger(r, g, b, a);
}

void Buffer::setPixel(int32 i, uint8 r, uint8 g, uint8 b, uint8 a) {
    _pixels[i] = color::rgbaToInteger(r, g, b, a);
}