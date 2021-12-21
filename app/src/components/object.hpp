#ifndef VIRTUAL_GALAXY_OBJECT_HPP
#define VIRTUAL_GALAXY_OBJECT_HPP

#include "base.hpp"
#include "math/vector3.hpp"

#include <vector>

struct Object {
    std::vector<Vector3> Vertices;
    std::vector<uint32> Indices;
};

#endif //VIRTUAL_GALAXY_OBJECT_HPP
