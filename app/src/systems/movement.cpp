#include "movement.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"

#include "core/input.hpp"

void Movement::init(entt::registry& registry) {
    _registry = &registry;
}

void Movement::update(float deltaTime) {
    constexpr float speed = 0.001f;
    Vector3 rot;

    auto& input = Input::getInstance();
    if (input.getKeyDown(Input::KeyCode::A)) {
        rot.Y += speed;
    } else if (input.getKeyDown(Input::KeyCode::D)) {
        rot.Y -= speed;
    }

    if (input.getKeyDown(Input::KeyCode::W)) {
        rot.X += speed;
    } else if (input.getKeyDown(Input::KeyCode::S)) {
        rot.X -= speed;
    }

    if (input.getKeyDown(Input::KeyCode::Q)) {
        rot.Z += speed;
    } else if (input.getKeyDown(Input::KeyCode::E)) {
        rot.Z -= speed;
    }

//    if (input.getKeyDown(Input::KeyCode::LEFT_SHIFT)) {
//
//    }
//

    for (auto&& [entity, transform] : _registry->view<Transform, Player>().each()) {
//        transform.Translation += trans;
        transform.Rotation += rot;
    }
}

void Movement::terminate() {

}
