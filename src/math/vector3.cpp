#include <valarray>
#include "math/vector3.hpp"

constexpr bool Vector3::operator==(const Vector3& o) const { return X == o.X && Y == o.Y && Z == o.Z; }
constexpr bool Vector3::operator!=(const Vector3& o) const { return X != o.X || Y != o.Y || Z != o.Z; }

Vector3 Vector3::operator+(const Vector3& o) const { return { X + o.X, Y + o.Y, Z + o.Z }; }
void Vector3::operator+=(const Vector3& o) { X += o.X; Y += o.Y; Z += o.Z; }
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

Vector4 Vector3::operator*(const Matrix4x4& o) const {
    auto v = Vector4 {X,Y,Z,1};
    return v * o;
}

//Vector2 Vector3::proj() const { return { X / Z, Y / Z }; }

//void Vector3::operator*=(const Matrix4x4& o) {
//    X = o(0, 0) * X + o(1, 0) * Y + o( 2, 0) * Z + o(3, 0);
//    Y = o(0, 1) * X + o(1, 1) * Y + o( 2, 1) * Z + o(3, 1);
//    Z = o(0, 2) * X + o(1, 2) * Y + o( 2, 2) * Z + o(3, 2);
//}

