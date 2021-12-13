#include "utils/data.hpp"

#include <fstream>
#include <sstream>

std::string Data::read(const std::string& path) {
    std::ifstream fileReadStream;
    fileReadStream.exceptions(fileReadStream.exceptions() | std::ios::failbit);
    fileReadStream.open(path);

    std::stringstream buffer;
    buffer << fileReadStream.rdbuf();

    return buffer.str();
}