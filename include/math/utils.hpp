#ifndef VIRTUAL_GALAXY_UTILS_HPP
#define VIRTUAL_GALAXY_UTILS_HPP

#include "math/matrix4x4.hpp"
#include <valarray>

namespace utils {
    /**
     * Returns a projection matrix that encodes the near and far clipping
     * while projection to the correct fov
     *
     * @param fov Field of view
     * @param near Near clipping plane
     * @param far Far clipping plane
     * @return Projection matrix to translate points
     */
    Matrix4x4 getProjectionMatrix(float fov, float near, float far);

    /**
     * Degrees to radians constant
     */
    constexpr float Deg2Rad = M_PI / 180;

    /**
     * Radians to degrees constant
     */
    constexpr float Rad2Deg = 1 / Deg2Rad;
}


#endif //VIRTUAL_GALAXY_UTILS_HPP
