#include "math/utils.hpp"
#include "math/matrix4x4.hpp"

#include <complex>

Matrix4x4::Matrix4x4() {
    for (float& _col : _cols) {
        _col = 0;
    }
}

Matrix4x4 Matrix4x4::identity() {
    auto m = Matrix4x4();

    m[0] = 1.f;
    m[5]= 1.f;
    m[10] = 1.f;
    m[15] = 1.f;

    return m;
}

Matrix4x4 Matrix4x4::translation(float x, float y, float z) {
    auto m = identity();

    m[3] = x;
    m[7]= y;
    m[11] = z;

    return m;
}

Matrix4x4 Matrix4x4::rotation(float x, float y, float z) {
    auto mX = identity();

    if (x != 0) {
        auto cosX = std::cos(x * utils::Deg2Rad);
        auto sinX = std::sin(x * utils::Deg2Rad);

        mX(1, 1) = cosX; // cos
        mX(2, 1) = -sinX; // -sin
        mX(1, 2) = sinX; // sin
        mX(2, 2) = cosX; // cos
    }

    auto mY = identity();
    if (y != 0) {
        auto cosY = std::cos(y * utils::Deg2Rad);
        auto sinY = std::sin(y * utils::Deg2Rad);

        mY(0, 0) = cosY; // cos
        mY(2, 0) = sinY; // sin
        mY(0, 2) = -sinY; // -sin
        mY(2, 2) = cosY; // cos
    }

    auto mZ = identity();
    if (z != 0) {
        auto cosZ = std::cos(z * utils::Deg2Rad);
        auto sinZ = std::sin(z * utils::Deg2Rad);

        mZ(0, 0) = cosZ; // cos
        mZ(1, 0) = sinZ; // -sin
        mZ(0, 1) = -sinZ; // sin
        mZ(1, 1) = cosZ; // cos
    }

    return mZ * mY * mX;
}

Matrix4x4 Matrix4x4::scale(float x, float y, float z) {
    auto m = Matrix4x4();

    m[0] = x;
    m[5]= y;
    m[10] = z;
    m[15] = 1.f;

    return m;
}

bool Matrix4x4::operator==(const Matrix4x4& o) const {
    for (int32 i = 0; i < 16; ++i) {
        if (_cols[i] != o[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& o) const {
    for (int32 i = 0; i < 16; ++i) {
        if (_cols[i] != o[i]) {
            return true;
        }
    }
    return false;
}

float& Matrix4x4::operator[](int32 i) {
    return _cols[i];
}

float Matrix4x4::operator[](int32 i) const {
    return _cols[i];
}

float& Matrix4x4::operator()(int32 x, int32 y) {
    return _cols[x + y * Cols];
}

float Matrix4x4::operator()(int32 x, int32 y) const {
    return _cols[x + y * Cols];
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& o) const {
    auto res = Matrix4x4();

    for (int32 row = 0; row < Rows; ++row) {
        for (int32 col = 0; col < Cols; ++col) {
            for (int32 i = 0; i < Cols ; ++i) {
                res(col, row) += (*this)(i, row) * o(col, i);
            }
        }
    }

    return res;
}