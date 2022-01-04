#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "base.hpp"
#include "core/system.hpp"
#include "math/vector2.hpp"
#include "math/vector4.hpp"
#include "math/matrix4x4.hpp"

class Wireframe : public System {
public:
    Wireframe(float fov, float near, float far) : _fov(fov), _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    [[nodiscard]] Vector2 toRaster(const Vector4& v) const;

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

    float _near;
    float _far;
    float _fov;
    Matrix4x4 _projection;
};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
