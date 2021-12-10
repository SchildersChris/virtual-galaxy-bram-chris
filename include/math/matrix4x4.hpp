#ifndef VIRTUAL_GALAXY_MATRIX4X4_HPP
#define VIRTUAL_GALAXY_MATRIX4X4_HPP

#include "math/axis.hpp"

#include <stdexcept>

class Matrix4x4 {
public:
    Matrix4x4() = default;

    static Matrix4x4 identity();

    static Matrix4x4 translation(float x, float y, float z);

    static Matrix4x4 scale(float x, float y, float z);

    constexpr bool operator==(const Matrix4x4& o) const;
    constexpr bool operator!=(const Matrix4x4& o) const;

    constexpr float& operator[](int i);
    constexpr float operator[](int i) const;

    constexpr float& operator()(int x, int y);
    constexpr float operator()(int x, int y) const;

private:
    float _cols[16]{};
};

#endif //VIRTUAL_GALAXY_MATRIX4X4_HPP
