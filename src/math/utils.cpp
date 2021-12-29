#include "math/utils.hpp"

#include <complex>

Matrix4x4 utils::getProjectionMatrix(float fov, float near, float far, float aspect) {
    auto mat = Matrix4x4();

    float focal = 1 / std::tan(fov * Rad2Deg * .5f);
    mat[0] = focal / aspect;
    mat[5] = -focal;
    mat[10] = near / (far - near);
    mat[11] = far * near / (far - near);
    mat[14] = -1;

    return mat;
}