#ifndef VIRTUAL_GALAXY_OBJECT_HPP
#define VIRTUAL_GALAXY_OBJECT_HPP

#include "base.hpp"
#include "math/vector3.hpp"

#include <vector>
#include <graphics/color.hpp>

struct Object {
    explicit Object(Color color) : BaseColor(color) { }
    std::vector<Vector3> Vertices;
    std::vector<uint32> Indices;
    Color BaseColor;
};

#endif //VIRTUAL_GALAXY_OBJECT_HPP
