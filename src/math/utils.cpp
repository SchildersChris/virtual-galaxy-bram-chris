#include "math/utils.hpp"

#include <complex>

Matrix4x4 utils::getProjectionMatrix(float fov, float near, float far, float aspect) {
    auto mat = Matrix4x4();

    float focal = 1 / std::tan(fov * Deg2Rad * .5f);
    mat[0] = focal / aspect;
    mat[5] = -focal;
    mat[10] = -far / (far - near);
    mat[11] = -far * near / (far - near);
    mat[14] = -1;

    return mat;
}

float utils::edgeFunction(const Vector2& start, const Vector2& end, const Vector2& p) {
    return (p.X - start.X) * (end.Y - start.Y) - (p.Y - start.Y) * (end.X - start.X);
}

Vector3 utils::findTriangleIntersection(const Vector3* t, const Vector3& start, const Vector3& end) {
    /*
    * Directional vector of the line that intersects with the plane
    */
    auto directionalVector = end - start;
    auto normal = (t[1] - t[0]).cross(t[2] - t[0]);

    auto distance = t[0].dot(normal);

    auto startNormal = start * normal;
    auto directionalNormal = directionalVector * normal;

    auto firstVal = (distance - startNormal.X - startNormal.Y - startNormal.Z);
    auto secondVal = (directionalNormal.X + directionalNormal.Y + directionalNormal.Z);

    if (firstVal == 0 && secondVal == 0) {
        return Vector3 { 1, 1, 1 };
    }

    if (firstVal != 0 && secondVal == 0) {
        return Vector3 { 1, 1, 1 };
    }

    auto lambda = firstVal / secondVal;

    return start + (directionalVector * lambda);
}