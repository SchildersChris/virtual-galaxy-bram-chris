#ifndef VIRTUAL_GALAXY_OBJECT_HPP
#define VIRTUAL_GALAXY_OBJECT_HPP

#include "base.hpp"
#include "math/vector3.hpp"

#include <vector>

struct Object {
    std::vector<Vector3> vertices;
    std::vector<uint32> indices;
};

#endif //VIRTUAL_GALAXY_OBJECT_HPP
