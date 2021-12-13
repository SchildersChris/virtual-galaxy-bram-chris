#ifndef VIRTUAL_GALAXY_READER_HPP
#define VIRTUAL_GALAXY_READER_HPP

#include <string>
#include <vector>
#include <base.hpp>
#include <math/vector3.hpp>

class Reader {
public:
    static void load(const std::string& path, std::vector<Vector3>& vertices, std::vector<uint32>& indices);
};


#endif //VIRTUAL_GALAXY_READER_HPP
