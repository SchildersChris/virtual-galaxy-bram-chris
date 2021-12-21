#ifndef VIRTUAL_GALAXY_WAVEFRONT_OBJECT_HPP
#define VIRTUAL_GALAXY_WAVEFRONT_OBJECT_HPP

#include "base.hpp"
#include "math/vector3.hpp"

#include <string>
#include <vector>

class WavefrontObject {
public:
    static void load(const std::string& path, std::vector<Vector3>& vertices, std::vector<uint32>& indices);
};

#endif //VIRTUAL_GALAXY_WAVEFRONT_OBJECT_HPP
