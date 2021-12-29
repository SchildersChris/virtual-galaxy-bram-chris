#include "math/vector4.hpp"

constexpr bool Vector4::operator==(const Vector4& o) const { return X == o.X && Y == o.Y && Z == o.Z && W == o.W; }
constexpr bool Vector4::operator!=(const Vector4& o) const { return X != o.X || Y != o.Y || Z != o.Z || W != o.W; }

Vector4 Vector4::operator*(const Matrix4x4& o) const {
    Vector4 v {0,0,0,0};

    v.X = o(0, 0) * X + o(1, 0) * Y + o(2, 0) * Z + o(3, 0) * W;
    v.Y = o(0, 1) * X + o(1, 1) * Y + o(2, 1) * Z + o(3, 1) * W;
    v.Z = o(0, 2) * X + o(1, 2) * Y + o(2, 2) * Z + o(3, 2) * W;
    v.W = o(0, 3) * X + o(1, 3) * Y + o(2, 3) * Z + o(3, 3) * W;

    return v;
}