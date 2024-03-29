#include "wavefront-object.hpp"
#include "core/data.hpp"

#include "objpar.h"
#include <iostream>

void WavefrontObject::load(const std::string& path, std::vector<Vector3>& vertices, std::vector<uint32>& indices) {
    auto data = data::read(path);

    objpar_data_t objData;
    auto buffer = new char[objpar_get_size(data.c_str(), data.size())];
    objpar(data.c_str(), data.size(), buffer, &objData);

    for (int i = 0, j = 0; j < objData.face_count * 3 * 3; i++, j+=3) {
        indices.push_back(objData.p_faces[j]);
    }

    for (int i = 0; i < objData.position_count; ++i) {
        vertices.push_back((reinterpret_cast<Vector3*>(objData.p_positions))[i]);
    }

    std::cout << "Loaded object: " <<  path << std::endl;
    std::cout << "Vertices Count: " <<  objData.position_count << std::endl;
    std::cout << "Face Count: " <<  objData.face_count << std::endl;

    delete[] buffer;
}
