#ifndef VIRTUAL_GALAXY_APPLICATION_HPP
#define VIRTUAL_GALAXY_APPLICATION_HPP

#include "base.hpp"
#include "core/system.hpp"

#include <vector>
#include <memory>

class Application : public NoCopyNoMove {
public:
    /**
     * Start the application main loop
     * This function will exit once the window exit command is called
     */
    void run();

protected:
    explicit Application(std::string title);

    /*
     * Systems
     */
    std::vector<std::unique_ptr<System>> Systems;

private:
    std::string _title;
};

#endif //VIRTUAL_GALAXY_APPLICATION_HPP
