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
    void rasterizeTriangle(Buffer& frame, const Vector3 t[3], const Vector3& light);

    [[nodiscard]] Vector2 toRaster(const Vector2& v) const;

    static float getShade(const Vector3& light, const Vector3& normal);

    /*
     * Algorithm is taken from
     * https://cgl.ethz.ch/teaching/former/vc_master_06/Downloads/9a_scan-conversion_Z-buffering_6.pdf
     */
    static float interpAtoB(float fromA, float fromB, float toA, float toB, float atB);

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    static constexpr float _near = 1.f;
    static constexpr float _far = 100.f;
};


#endif //VIRTUAL_GALAXY_RENDER_HPP
