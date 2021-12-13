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

bool Vector2::operator<(const Vector2& o) const { return X < o.X && Y < o.Y; }
bool Vector2::operator>(const Vector2& o) const { return X > o.X && Y > o.Y; }

float Vector2::cross(const Vector2& o) const {
    return X * o.Y - Y * o.X;
}

float Vector2::interpX(const Vector2& o, float y) const {
    return X + (o.X - X) / (o.Y - Y) * (y - Y);
}
