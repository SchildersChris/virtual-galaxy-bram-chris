#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "base.hpp"
#include "core/system.hpp"
#include "graphics/texture.hpp"
#include "math/vector2.hpp"
#include "math/matrix4x4.hpp"

class Wireframe : public System {
public:
    /**
     * Construct wireframe renderer
     *
     * @param fov Field of view
     * @param near Near clipping
     * @param far Far clipping
     */
    Wireframe(float fov, float near, float far);

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    [[nodiscard]] Vector2 toRaster(const Vector2& v) const;

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

    Matrix4x4 _projection;
};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
