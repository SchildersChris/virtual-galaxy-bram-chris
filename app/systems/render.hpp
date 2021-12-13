#ifndef VIRTUAL_GALAXY_RENDER_HPP
#define VIRTUAL_GALAXY_RENDER_HPP

#include "system.hpp"
#include "math/vector3.hpp"

class Render : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime, Buffer& frame) override;
    void terminate() override;

private:
    void rasterizeTriangle(Buffer& frame, Vector3 triangle[3]);

    [[nodiscard]] Vector2 toRaster(const Vector2& v) const;
    
    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    static constexpr float _near = 1.f;
    static constexpr float _far = 100.f;
};


#endif //VIRTUAL_GALAXY_RENDER_HPP
