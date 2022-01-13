#ifndef VIRTUAL_GALAXY_MATRIX4X4_HPP
#define VIRTUAL_GALAXY_MATRIX4X4_HPP

#include "base.hpp"
#include <stdexcept>

class Vector3;

class Matrix4x4 {
public:
    Matrix4x4();

    Matrix4x4(const std::initializer_list<float>& matrix);

    static Matrix4x4 identity();

    static Matrix4x4 translation(float x, float y, float z);

    static Matrix4x4 rotation(float x, float y, float z);

    static Matrix4x4 scale(float x, float y, float z);

    static Matrix4x4 lookAt(const Vector3& right, const Vector3& up, const Vector3& direction);


    bool operator==(const Matrix4x4& other) const;
    bool operator!=(const Matrix4x4& other) const;

    float& operator[](int32 i);
    float operator[](int32 i) const;

    float& operator()(int32 x, int32 y);
    float operator()(int32 x, int32 y) const;

    Matrix4x4 operator*(const Matrix4x4& other) const;

private:
    static constexpr int32 Rows = 4;
    static constexpr int32 Cols = 4;

    float _cols[16]{};
};

#endif //VIRTUAL_GALAXY_MATRIX4X4_HPP
