#ifndef VIRTUAL_GALAXY_VECTOR3_HPP
#define VIRTUAL_GALAXY_VECTOR3_HPP

#include "vector2.hpp"
#include "matrix4x4.hpp"

class Vector4;

class Vector3 {
public:
    Vector3() : X(0.f), Y(0.f), Z(0.f) {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    constexpr bool operator==(const Vector3& o) const { return X == o.X && Y == o.Y && Z == o.Z; };
    constexpr bool operator!=(const Vector3& o) const { return X != o.X || Y != o.Y || Z != o.Z; };

    Vector3 operator+(const Vector3& o) const;
    void operator+=(const Vector3& o);
    Vector3 operator+(float s) const;

    Vector3 operator-(const Vector3& o) const;
    Vector3 operator-(float s) const;
    Vector3 operator-() const;

    Vector3 operator*(const Vector3& o) const;
    Vector3 operator*(float s) const;
    Vector4 operator*(const Matrix4x4& o) const;

    Vector3 operator/(const Vector3& o) const;
    Vector3 operator/(float s) const;

    [[nodiscard]] float dot(const Vector3& o) const;

    [[nodiscard]] Vector3 cross(const Vector3& o) const;

    [[nodiscard]] float cos(const Vector3& o) const;

    [[nodiscard]] float length() const;

    [[nodiscard]] Vector3 normalize() const;

    [[nodiscard]] Vector2 toVector2() const;

    float X;
    float Y;
    float Z;
};

#endif //VIRTUAL_GALAXY_VECTOR3_HPP
