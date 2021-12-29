#include <imgui.h>
#include "movement.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"

#include "core/input.hpp"

void Movement::init(entt::registry& registry) {
    _registry = &registry;
}

void Movement::update(float deltaTime) {
    static float speed = 0.001;
    ImGui::Begin("Movement");
    ImGui::SliderFloat("Speed", &speed, 0, 0.02);
    ImGui::End();

    auto actualSpeed = speed * deltaTime;

    Vector3 rot, trans;
    auto& input = Input::getInstance();
    if (input.getKeyDown(Input::KeyCode::A)) {
        rot.Y -= actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::D)) {
        rot.Y += actualSpeed;
    }

    if (input.getKeyDown(Input::KeyCode::W)) {
        rot.X -= actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::S)) {
        rot.X += actualSpeed;
    }

    if (input.getKeyDown(Input::KeyCode::Q)) {
        rot.Z += actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::E)) {
        rot.Z -= actualSpeed;
    }

    if (input.getKeyDown(Input::KeyCode::LEFT_SHIFT)) {
        trans = { 0, 0, actualSpeed };
    }

    for (auto&& [entity, transform] : _registry->view<Transform, Player>().each()) {
        transform.Translation += trans;
        transform.Rotation += rot;
    }
}

void Movement::terminate() {

}
