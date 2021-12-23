#ifndef VIRTUAL_GALAXY_UTILS_HPP
#define VIRTUAL_GALAXY_UTILS_HPP

#include "math/matrix4x4.hpp"

namespace utils {
    /**
     * Provides a projection matrix based on the given parameters
     *
     * @param fov Field of view
     * @param near Near clipping plane
     * @param far Far clipping plane
     * @return Projection matrix to translate points
     */
    Matrix4x4 getProjectionMatrix(float near, float far, float fov);
}


#endif //VIRTUAL_GALAXY_UTILS_HPP
