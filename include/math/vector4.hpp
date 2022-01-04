#ifndef VIRTUAL_GALAXY_VECTOR4_HPP
#define VIRTUAL_GALAXY_VECTOR4_HPP

#include "matrix4x4.hpp"
#include "vector3.hpp"

class Vector4 {
public:
    Vector4() : X(0.f), Y(0.f), Z(0.f), W(0.f) {}
    Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

    constexpr bool operator==(const Vector4& o) const;
    constexpr bool operator!=(const Vector4& o) const;

    [[nodiscard]] Vector4 operator*(const Matrix4x4& o) const;

    [[nodiscard]] Vector3 toVector3() const;

    float X;
    float Y;
    float Z;
    float W;
};

#endif //VIRTUAL_GALAXY_VECTOR4_HPP
