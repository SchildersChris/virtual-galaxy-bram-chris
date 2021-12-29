#include <imgui.h>
#include "movement.hpp"
#include "../components/transform.hpp"
#include "../components/player.hpp"

#include "core/input.hpp"

void Movement::init(entt::registry& registry) {
    _registry = &registry;
}

void Movement::update(float deltaTime) {
    static float rotationSpeed = 0.1;
    static float movementSpeed = 0.02;

    ImGui::Begin("Movement");
    ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0, 1);
    ImGui::SliderFloat("Movement Speed", &movementSpeed, 0, 0.2);
    ImGui::End();

    auto actualRotation = rotationSpeed * deltaTime;

    Vector3 rot, trans;
    auto& input = Input::getInstance();
    if (input.getKeyDown(Input::KeyCode::A)) {
        rot.Y -= actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::D)) {
        rot.Y += actualRotation;
    }

    if (input.getKeyDown(Input::KeyCode::W)) {
        rot.X += actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::S)) {
        rot.X -= actualRotation;
    }

    if (input.getKeyDown(Input::KeyCode::Q)) {
        rot.Z -= actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::E)) {
        rot.Z += actualRotation;
    }

    for (auto&& [entity, transform] : _registry->view<Transform, Player>().each()) {
        transform.Rotation += rot;

        if (input.getKeyDown(Input::KeyCode::LEFT_SHIFT)) {
            auto rotation = Matrix4x4::rotation(transform.Rotation.X, transform.Rotation.Y, transform.Rotation.Z);
            auto heading = Vector4 { 0, 0, 1, 1 } * rotation;

            transform.Translation += Vector3 { heading.X, heading.Y, heading.Z } * movementSpeed * deltaTime;
        }
    }
}

void Movement::terminate() {}
