#include "math/matrix4x4.hpp"

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

    for (int32 row = 0; row < 4; ++row) {
        for (int32 col = 0; col < 4; ++col) {
            for (int i = 0; i < 4; ++i) {
                res(col, row) = (*this)(i, row) * o(col, i);
            }
        }
    }
    return res;
}

void Matrix4x4::operator*=(const Matrix4x4& o) {
    for (int32 row = 0; row < 4; ++row) {
        for (int32 col = 0; col < 4; ++col) {
            for (int i = 0; i < 4; ++i) {
                (*this)(i, row) = (*this)(i, row) * o(col, i);
            }
        }
    }
}