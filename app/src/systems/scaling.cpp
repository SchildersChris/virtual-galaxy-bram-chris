#include <complex>
#include "scaling.hpp"

#include "../components/scale.hpp"
#include "../components/transform.hpp"

void Scaling::init(entt::registry& registry) {
    _registry = &registry;
}

void Scaling::update(float deltaTime) {
    _timer += deltaTime;

    for (auto&& [entity, transform, scale] : _registry->view<Transform, Scale>().each()) {
        if (scale.Size < 0) {
            _timer = 0;
        }
        scale.Size = std::sin(scale.Speed * _timer);

        transform.Scale.X = scale.Size;
        transform.Scale.Y = scale.Size;
        transform.Scale.Z = scale.Size;
    }
}
