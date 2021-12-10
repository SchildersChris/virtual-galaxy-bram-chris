#include "math/matrix4x4.hpp"

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

constexpr bool Matrix4x4::operator==(const Matrix4x4& o) const {
    for (auto i = 0; i < 16; ++i) {
        if (_cols[i] != o[i]) {
            return false;
        }
    }
    return true;
}

constexpr bool Matrix4x4::operator!=(const Matrix4x4& o) const {
    for (auto i = 0; i < 16; ++i) {
        if (_cols[i] != o[i]) {
            return true;
        }
    }
    return false;
}

constexpr float& Matrix4x4::operator[](int i) {
    return i < 0 || i > 16 ? throw std::out_of_range("Index out of range") : _cols[i];
}

constexpr float Matrix4x4::operator[](int i) const {
    return i < 0 || i > 16 ? throw std::out_of_range("Index out of range") : _cols[i];
}

constexpr float& Matrix4x4::operator()(int x, int y) {
    return x < 0 || y < 0 || x > 4 || y > 4 ?
           throw std::out_of_range("Index out of range") :
           _cols[x + y * 4];
}

constexpr float Matrix4x4::operator()(int x, int y) const {
    return x < 0 || y < 0 || x > 4 || y > 4 ?
           throw std::out_of_range("Index out of range") :
           _cols[x + y * 4];
}
