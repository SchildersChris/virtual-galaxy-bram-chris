#include "math/utils.hpp"

#include <complex>

Matrix4x4 utils::getProjectionMatrix(float fov, float near, float far) {
    auto mat = Matrix4x4();

    float scale = near * std::tan(fov * .5f);
    mat[0] = scale;
    mat[5] = scale;
    mat[10] = -far / (far - near);
    mat[11] = -1;
    mat[10] = -far * near / (far - near);

    return mat;
}