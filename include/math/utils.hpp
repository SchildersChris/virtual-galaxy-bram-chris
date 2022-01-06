#ifndef VIRTUAL_GALAXY_UTILS_HPP
#define VIRTUAL_GALAXY_UTILS_HPP

#include "math/matrix4x4.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"

#include <valarray>

namespace utils {
    /**
     * Returns a projection matrix that encodes the near and far clipping
     * while projection to the correct fov
     *
     * @param fov Field of view
     * @param near Near clipping plane
     * @param far Far clipping plane
     * @param aspect Aspect ratio
     * @return Projection matrix to translate points
     */
    Matrix4x4 getProjectionMatrix(float fov, float near, float far, float aspect);

    /**
     * Determines whether a 2d vector falls on the right of left size of a edge
     *
     * @param start Edge start
     * @param end Edge end
     * @param p Point to test
     * @return A positive value if the point falls on the left of the edge
     */
    float edgeFunction(const Vector2& start, const Vector2& end, const Vector2& p);

    /**
     * Find edge point of intersection in a triangle
     *
     * @param t Triangle plane
     * @param start Edge start
     * @param end Edge end
     * @return Point of intersection
     */
    Vector3 intersection(const Vector3& planePointA, const Vector3& planePointB, const Vector3& planePointC,
                                const Vector3& linePointA, const Vector3& linePointB);
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
