#include "shooting.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"
#include "../components/bullet.hpp"
#include "../utils/wavefront-object.hpp"

#include "core/input.hpp"
#include "math/vector4.hpp"
#include "../components/collider.hpp"

void Shooting::init(entt::registry& registry) {
    _registry = &registry;
    WavefrontObject::load("assets/cube.obj", _bullet.Vertices, _bullet.Indices);
}

void Shooting::update(float deltaTime) {
    static float movementSpeed = 0.02;

    for (auto&& [entity, transform, bullet] : _registry->view<Transform, Bullet>().each()) {
        bullet.AliveMs += deltaTime;

        if (bullet.AliveMs > bullet.MaxAliveMs) {
            _registry->destroy(entity);
            continue;
        }

        transform.Translation += bullet.Heading * movementSpeed * deltaTime;
    }

    if (!Input::getInstance().getKeyUp(Input::KeyCode::SPACE)) {
        return;
    }

    for (auto&& [entity, transform] : _registry->view<Transform, Player>().each()) {
        auto bullet = _registry->create();

        auto rotation = Matrix4x4::rotation(transform.Rotation.X, transform.Rotation.Y, transform.Rotation.Z);
        auto heading = Vector4 { 0, 0, 1, 1 } * rotation;

        _registry->emplace<Bullet>(bullet, Vector3 { heading.X, heading.Y, heading.Z });
        _registry->emplace<Transform>(bullet, Transform {
            transform.Translation,
            transform.Rotation,
            Vector3 { 0.2f, 0.2f, 0.2f}
        });
        _registry->emplace<Object>(bullet, _bullet);
        _registry->emplace<Collider>(bullet, [&](entt::entity other){
            if (!_registry->any_of<Player>(other)) {
                _registry->destroy(other);
            }
        });
    }
}

