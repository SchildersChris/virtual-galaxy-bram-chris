#include "math/vector4.hpp"

constexpr bool Vector4::operator==(const Vector4& o) const { return X == o.X && Y == o.Y && Z == o.Z && W == o.W; }
constexpr bool Vector4::operator!=(const Vector4& o) const { return X != o.X || Y != o.Y || Z != o.Z || W != o.W; }