#ifndef VIRTUAL_GALAXY_RASTERIZER2_HPP
#define VIRTUAL_GALAXY_RASTERIZER2_HPP

#include <math/utils.hpp>
#include "core/system.hpp"
#include "math/vector3.hpp"
#include "graphics/texture.hpp"

class Rasterizer2 : public System {
public:
    Rasterizer2(float fov, float near, float far) : _projection(utils::getProjectionMatrix(fov, near, far)) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    void rasterizeTriangle(const Vector3 t[3], const Vector3 r[3], const Vector3& light, Texture::Stream& stream);

    [[nodiscard]] Vector3 toRaster(const Vector3& v) const;

    float getShade(float z, const Vector3 c[3], const float a[3], const Vector3& normal);

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

    std::unique_ptr<Texture> _texture {nullptr};
    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    Matrix4x4 _projection;

    static constexpr float _near = 1.f;
    static constexpr float _far = 100.f;

    float edgeFunction(const Vector3* v1, const Vector3* v2, const Vector3* p);
};


#endif //VIRTUAL_GALAXY_RASTERIZER2_HPP
