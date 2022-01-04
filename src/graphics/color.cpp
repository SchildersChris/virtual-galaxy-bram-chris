#include "graphics/color.hpp"

Color Color::_white {255, 255, 255, 255};
Color Color::_red {255, 0, 0, 255};
Color Color::_green {0, 255, 0, 255};
Color Color::_blue {0, 0, 255, 255};
Color Color::_black {0, 0, 0, 255};

uint32 Color::rgbaToInteger(uint8 r, uint8 g, uint8 b, uint8 a) {
    return (r << 24) + (g << 16) + (b << 8) + a;
}

uint32 Color::rgbToInteger(uint8 r, uint8 g, uint8 b) {
    return (r << 24) + (g << 16) + (b << 8);
}

Color::operator uint32() const {
    return Color::rgbaToInteger(R, G, B, A);
}

bool Color::operator==(const Color& other) const {
    return A == other.A && G == other.G && B == other.B && A == other.A;
}

bool Color::operator!=(const Color& other) const {
    return A != other.A || G != other.G || B != other.B || A != other.A;
}

Color Color::operator*(float intensity) const {
    return Color {
        static_cast<uint8>(std::abs(static_cast<float>(R) * intensity)),
        static_cast<uint8>(std::abs(static_cast<float>(G) * intensity)),
        static_cast<uint8>(std::abs(static_cast<float>(B) * intensity)),
        static_cast<uint8>(std::abs(static_cast<float>(A) * intensity))
    };
}