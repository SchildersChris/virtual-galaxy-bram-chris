#include "math/vector2.hpp"

constexpr bool Vector2::operator==(const Vector2& o) const { return X == o.X && Y == o.Y; }
constexpr bool Vector2::operator!=(const Vector2& o) const { return X != o.X || Y != o.Y; }

Vector2 Vector2::operator+(const Vector2& o) const { return { X + o.X, Y + o.Y }; }
Vector2 Vector2::operator+(float s) const { return { X + s, Y + s }; }

Vector2 Vector2::operator-(const Vector2& o) const { return { X - o.X, Y - o.Y }; }
Vector2 Vector2::operator-(float s) const { return { X - s, Y - s }; }

Vector2 Vector2::operator*(const Vector2& o) const { return { X * o.X, Y * o.Y }; }
Vector2 Vector2::operator*(float s) const { return { X * s, Y * s }; }

Vector2 Vector2::operator/(const Vector2& o) const { return { X / o.X, Y / o.Y }; }
Vector2 Vector2::operator/(float s) const { return { X / s, Y / s }; }
