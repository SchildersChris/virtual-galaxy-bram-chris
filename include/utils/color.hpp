#ifndef VIRTUAL_GALAXY_COLOR_HPP
#define VIRTUAL_GALAXY_COLOR_HPP

#include "base.hpp"

class Color {
public:
    Color(uint8 red, uint8 green, uint8 blue, uint8 alpha) noexcept
        : R(red), G(green), B(blue), A(alpha) {}

    static const Color& white() { return _white; }
    static const Color& red() { return _red; }
    static const Color& green() { return _green; }
    static const Color& blue() { return _blue; }
    static const Color& black() { return _black; }

    static uint32 rgbaToInteger(uint8 r, uint8 g, uint8 b, uint8 a);
    static uint32 rgbToInteger(uint8 r, uint8 g, uint8 b);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    explicit operator uint32() const;

    uint8 R;
    uint8 G;
    uint8 B;
    uint8 A;

private:
    static Color _white;
    static Color _red;
    static Color _green;
    static Color _blue;
    static Color _black;
};

#endif //VIRTUAL_GALAXY_COLOR_HPP
