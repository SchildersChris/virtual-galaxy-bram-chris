#ifndef VIRTUAL_GALAXY_MATRIX4X4_HPP
#define VIRTUAL_GALAXY_MATRIX4X4_HPP

#include "base.hpp"
#include "math/axis.hpp"

#include <stdexcept>

class Matrix4x4 {
public:
    Matrix4x4() = default;

    explicit Matrix4x4(const float cols[16]) {
        for (int32 i = 0; i < 16; ++i) {
            _cols[i] = cols[i];
        }
    };

    static Matrix4x4 identity();

    static Matrix4x4 translation(float x, float y, float z);

    static Matrix4x4 scale(float x, float y, float z);

    bool operator==(const Matrix4x4& o) const;
    bool operator!=(const Matrix4x4& o) const;

    float& operator[](int32 i);
    float operator[](int32 i) const;

    float& operator()(int32 x, int32 y);
    float operator()(int32 x, int32 y) const;

    Matrix4x4 operator*(const Matrix4x4& o) const;
    void operator*=(const Matrix4x4& o);

private:
    static constexpr int32 Rows = 4;
    static constexpr int32 Cols = 4;

    float _cols[16]{};
};

#endif //VIRTUAL_GALAXY_MATRIX4X4_HPP
