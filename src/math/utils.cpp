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

Vector3 utils::intersection(const Vector3& planePointA, const Vector3& planePointB, const Vector3& planePointC,
                            const Vector3& linePointA, const Vector3& linePointB) {
    Vector3 directionVectorPlaneA = planePointB - planePointA;
    Vector3 directionVectorPlaneB = planePointC - planePointA;

    Vector3 crossProductPlane = directionVectorPlaneA.cross(directionVectorPlaneB);
    if (crossProductPlane == Vector3 {0, 0, 0}) {
        throw std::runtime_error("Two vectors are aligned, crossproduct can't be calculated (Used in Intersection())");
    }

    double planeD = crossProductPlane.X * planePointA.X + crossProductPlane.Y * planePointA.Y +
                    crossProductPlane.Z * planePointA.Z;

    Vector3 directionVectorLine = linePointA - linePointB;

    if (directionVectorLine.dot(crossProductPlane) == 0) {
        throw std::runtime_error("Line and plane have zero or infinite intersections");
    }

    double lambdaTop =
            planeD - (crossProductPlane.X * linePointA.X) - (crossProductPlane.Y * linePointA.Y) -
            (crossProductPlane.Z * linePointA.Z);
    double lambdaBottom =
            (crossProductPlane.X * directionVectorLine.X) + (crossProductPlane.Y * directionVectorLine.Y) +
            (crossProductPlane.Z * directionVectorLine.Z);
    double lambda = lambdaTop / lambdaBottom;

    Vector3 intersection = linePointA + (directionVectorLine * lambda);
    return {intersection.X, intersection.Y, intersection.Z};
}
