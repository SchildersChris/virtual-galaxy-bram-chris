#ifndef VIRTUAL_GALAXY_RENDER_HPP
#define VIRTUAL_GALAXY_RENDER_HPP

#include "system.hpp"

class Render : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
    void terminate() override;

private:
    entt::registry* _registry {nullptr};

    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    static constexpr float near = 1.f;
    static constexpr float far = 100.f;
};


#endif //VIRTUAL_GALAXY_RENDER_HPP
