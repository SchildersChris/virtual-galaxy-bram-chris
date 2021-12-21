#ifndef VIRTUAL_GALAXY_RASTERIZER_HPP
#define VIRTUAL_GALAXY_RASTERIZER_HPP

#include "core/system.hpp"
#include "math/vector3.hpp"

class Rasterizer : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    void rasterizeTriangle(const Vector3 t[3], const Vector3& light);

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


#endif //VIRTUAL_GALAXY_RASTERIZER_HPP
