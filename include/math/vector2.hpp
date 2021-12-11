#ifndef VIRTUAL_GALAXY_VECTOR2_HPP
#define VIRTUAL_GALAXY_VECTOR2_HPP

class Vector2 {
public:
    Vector2() : X(0.f), Y(0.f) {}
    Vector2(float x, float y) : X(x), Y(y) {}

    constexpr bool operator==(const Vector2& o) const;
    constexpr bool operator!=(const Vector2& o) const;

    Vector2 operator+(const Vector2& o) const;
    Vector2 operator+(float s) const;

    Vector2 operator-(const Vector2& o) const;
    Vector2 operator-(float s) const;

    Vector2 operator*(const Vector2& o) const;
    Vector2 operator*(float s) const;

    Vector2 operator/(const Vector2& o) const;
    Vector2 operator/(float s) const;

    float X;
    float Y;
};

#endif //VIRTUAL_GALAXY_VECTOR2_HPP
