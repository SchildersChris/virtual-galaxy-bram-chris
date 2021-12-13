#include "utils/color.hpp"

uint32 color::rgbaToInteger(uint8 r, uint8 g, uint8 b, uint8 a) {
    return (r << 24) + (g << 16) + (b << 8) + a;
}

uint32 color::rgbToInteger(uint8 r, uint8 g, uint8 b) {
    return (r << 24) + (g << 16) + (b << 8);
}
