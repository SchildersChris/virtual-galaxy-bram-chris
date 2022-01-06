#include <imgui.h>
#include "movement.hpp"
#include "../components/transform.hpp"
#include "../components/actor.hpp"
#include "../components/camera.hpp"

#include "core/input.hpp"
#include "math/vector4.hpp"

void Movement::init(entt::registry& registry) {
    _registry = &registry;
}

void Movement::update(float deltaTime) {
    ImGui::Begin("Movement");
    ImGui::SliderFloat("Rotation Speed", &_rotationSpeed, 0, 1);
    ImGui::SliderFloat("Movement Speed", &_movementSpeed, 0, 0.2);
    ImGui::End();

    playerMovement(deltaTime);
    cameraMovement(deltaTime);
}

void Movement::playerMovement(float deltaTime) const {
    auto actualRotation = _rotationSpeed * deltaTime;

    Vector3 rot;
    auto& input = Input::getInstance();
    if (input.getKeyDown(Input::KeyCode::A)) {
        rot.Y += actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::D)) {
        rot.Y -= actualRotation;
    }

    if (input.getKeyDown(Input::KeyCode::W)) {
        rot.X += actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::S)) {
        rot.X -= actualRotation;
    }

    if (input.getKeyDown(Input::KeyCode::Q)) {
        rot.Z += actualRotation;
    } else if (input.getKeyDown(Input::KeyCode::E)) {
        rot.Z -= actualRotation;
    }

    auto shouldMove = input.getKeyDown(Input::KeyCode::LEFT_SHIFT);
    for (auto&& [entity, transform] : _registry->view<Transform, Actor>().each()) {
        transform.Rotation += rot;

        if (shouldMove) {
            auto rotation = Matrix4x4::rotation(transform.Rotation.X, transform.Rotation.Y, transform.Rotation.Z);
            auto heading = Vector4 { 0, 0, 1, 1 } * rotation; // Move in positive Z direction * current rotation

            transform.Translation += Vector3 { heading.X, heading.Y, heading.Z } * _movementSpeed * deltaTime;
        }
    }
}

void Movement::cameraMovement(float deltaTime) const {
    auto actualSpeed = _movementSpeed * deltaTime;

    Vector3 trans;
    auto& input = Input::getInstance();
    if (input.getKeyDown(Input::KeyCode::PAGE_UP)) {
        trans.Y -= actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::PAGE_DOWN)) {
        trans.Y += actualSpeed;
    }

    if (input.getKeyDown(Input::KeyCode::RIGHT_ARROW)) {
        trans.X += actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::LEFT_ARROW)) {
        trans.X -= actualSpeed;
    }

    if (input.getKeyDown(Input::KeyCode::UP_ARROW)) {
        trans.Z -= actualSpeed;
    } else if (input.getKeyDown(Input::KeyCode::DOWN_ARROW)) {
        trans.Z += actualSpeed;
    }

    for (auto&& [entity, transform] : _registry->view<Transform, Camera>().each()) {
        transform.Translation += trans;
    }
}
