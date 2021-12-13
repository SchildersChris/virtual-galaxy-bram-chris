#ifndef VIRTUAL_GALAXY_DATA_HPP
#define VIRTUAL_GALAXY_DATA_HPP

#include <string>

class Data {
public:
    /**
     * @brief Read the contents of a file as a string
     *
     * @param path of the file
     * @return the string content of a file
     */
    static std::string read(const std::string& path);
};

#endif //VIRTUAL_GALAXY_DATA_HPP
