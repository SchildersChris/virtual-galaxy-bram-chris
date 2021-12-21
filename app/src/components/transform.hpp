#ifndef VIRTUAL_GALAXY_TRANSFORM_HPP
#define VIRTUAL_GALAXY_TRANSFORM_HPP

#include "math/vector3.hpp"

struct Transform {
    Vector3 Translation;
    Vector3 Rotation;
    Vector3 Scale;

    Matrix4x4 GetMatrix() {
        return Matrix4x4::translation(Translation.X, Translation.Y, Translation.Z);
    }
};

#endif //VIRTUAL_GALAXY_TRANSFORM_HPP
