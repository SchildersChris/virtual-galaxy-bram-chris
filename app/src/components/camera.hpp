#ifndef VIRTUAL_GALAXY_CAMERA_HPP
#define VIRTUAL_GALAXY_CAMERA_HPP

#include "math/vector3.hpp"

struct Camera {
    /**
     * The position of the camera
     */
    Vector3 Eye;
    /**
     * the point the camera is looking towards
     */
    Vector3 LookAt;
};

#endif //VIRTUAL_GALAXY_CAMERA_HPP
