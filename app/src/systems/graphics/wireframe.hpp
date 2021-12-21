#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "base.hpp"
#include "core/system.hpp"
#include "graphics/texture.hpp"
#include "math/vector2.hpp"

class Wireframe : public System {
public:
    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

private:
    [[nodiscard]] Vector2 toRaster(const Vector2& v) const;

    entt::registry* _registry {nullptr};

    int32 _width {0};
    int32 _height {0};

};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
