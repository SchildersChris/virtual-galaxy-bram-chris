#ifndef VIRTUAL_GALAXY_TRANSFORM_HPP
#define VIRTUAL_GALAXY_TRANSFORM_HPP

#include "math/vector3.hpp"

struct Transform {
    Transform(Vector3 translation, Vector3 rotation, Vector3 scale)
        : Translation(translation), Rotation(rotation), Scale(scale) {}

    Vector3 Translation;
    Vector3 Rotation;
    Vector3 Scale;

    [[nodiscard]] Matrix4x4 getMatrix() const {
        return
            Matrix4x4::translation(Translation.X, Translation.Y, Translation.Z) *
            Matrix4x4::rotation(Rotation.X, Rotation.Y, Rotation.Z) *
            Matrix4x4::scale(Scale.X, Scale.Y, Scale.Z);
    }
};

#endif //VIRTUAL_GALAXY_TRANSFORM_HPP
