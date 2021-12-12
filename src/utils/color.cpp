#include "utils/color.hpp"

uint32 color::rgbaToInteger(uint8 r, uint8 g, uint8 b, uint8 a) {
    return (a << 24) + (b << 16) + (g << 8) + r;
}

uint32 color::rgbToInteger(uint8 r, uint8 g, uint8 b) {
    return (r << 24) + (g << 16) + (b << 8);
}
