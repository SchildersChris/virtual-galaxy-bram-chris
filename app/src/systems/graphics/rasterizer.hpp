#ifndef VIRTUAL_GALAXY_RASTERIZER_HPP
#define VIRTUAL_GALAXY_RASTERIZER_HPP

#include <math/utils.hpp>
#include "core/system.hpp"
#include "math/vector3.hpp"

class Rasterizer : public System {
public:
    Rasterizer(float fov, float near, float far) : _fov(fov), _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    void rasterizeTriangle(const Vector3 t[3], const Vector3 r[3]);

    [[nodiscard]] Vector3 toRaster(const Vector4& v) const;

    /**
     * Get shading value of the normal vector
     *
     * @param normal Normal of the face
     * @return Grayscale shade value
     */
    static uint8 getShade(const Vector3& normal)  ;

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};
    float _near;
    float _far;
    float _fov;

    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    Matrix4x4 _projection;
};


#endif //VIRTUAL_GALAXY_RASTERIZER_HPP
