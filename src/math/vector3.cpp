#include <valarray>
#include "math/vector3.hpp"

constexpr bool Vector3::operator==(const Vector3& o) const { return X == o.X && Y == o.Y && Z == o.Z; }
constexpr bool Vector3::operator!=(const Vector3& o) const { return X != o.X || Y != o.Y || Z != o.Z; }

Vector3 Vector3::operator+(const Vector3& o) const { return { X + o.X, Y + o.Y, Z + o.Z }; }
Vector3 Vector3::operator+(float s) const { return { X + s, Y + s, Z + s }; }

Vector3 Vector3::operator-(const Vector3& o) const { return { X - o.X, Y - o.Y, Z - o.Z }; }
Vector3 Vector3::operator-(float s) const { return { X - s, Y - s, Z - s }; }
Vector3 Vector3::operator-() const { return { -X, -Y, -Z }; }

Vector3 Vector3::operator*(const Vector3& o) const { return { X * o.X, Y * o.Y, Z * o.Z }; }
Vector3 Vector3::operator*(float s) const { return { X * s, Y * s, Z * s }; }

Vector3 Vector3::operator/(const Vector3& o) const { return { X / o.X, Y / o.Y, Z / o.Z }; }
Vector3 Vector3::operator/(float s) const { return { X / s, Y / s, Z / s }; }

float Vector3::dot(const Vector3& o) const { return X * o.X + Y * o.Y + Z * o.Z; }

Vector3 Vector3::cross(const Vector3& o) const {
    return {
        Y * Z - Z * o.Y,
        Z * o.X - X * o.Z,
        X * o.Y - Y * o.X
    };
}

float Vector3::length() const { return std::sqrt(std::abs(X * X + Y * Y + Z * Z)); }

Vector3 Vector3::normalize() const {
    auto l = length();
    return { X / l, Y / l, Z / l };
}

float Vector3::cos(const Vector3& o) const { return dot(o) / length() * o.length(); }

Vector2 Vector3::proj() const { return { X / Z, Y / Z }; }

