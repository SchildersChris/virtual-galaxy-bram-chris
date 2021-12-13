#ifndef VIRTUAL_GALAXY_VECTOR3_HPP
#define VIRTUAL_GALAXY_VECTOR3_HPP

#include "vector2.hpp"
#include "matrix4x4.hpp"

class Vector3 {
public:
    Vector3() : X(0.f), Y(0.f), Z(0.f) {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    constexpr bool operator==(const Vector3& o) const;
    constexpr bool operator!=(const Vector3& o) const;

    Vector3 operator+(const Vector3& o) const;
    Vector3 operator+(float s) const;

    Vector3 operator-(const Vector3& o) const;
    Vector3 operator-(float s) const;
    Vector3 operator-() const;

    Vector3 operator*(const Vector3& o) const;
    Vector3 operator*(float s) const;

    Vector3 operator/(const Vector3& o) const;
    Vector3 operator/(float s) const;

    void operator*=(const Matrix4x4& o);

    [[nodiscard]] float dot(const Vector3& o) const;

    [[nodiscard]] Vector3 cross(const Vector3& o) const;

    [[nodiscard]] float cos(const Vector3& o) const;

    [[nodiscard]] float length() const;

    [[nodiscard]] Vector3 normalize() const;

    [[nodiscard]] Vector2 proj() const;

    float X;
    float Y;
    float Z;
};

#endif //VIRTUAL_GALAXY_VECTOR3_HPP
