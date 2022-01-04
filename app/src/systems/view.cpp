#include "view.hpp"
#include "../components/transform.hpp"
#include "../components/camera.hpp"
#include "../components/player.hpp"

#include <imgui.h>
#include <core/input.hpp>

void View::init(entt::registry& registry) {
    _registry = &registry;
    _isFpsCamera = false;

    _worldCamera = registry.create();
    registry.emplace<Camera>(_worldCamera);
    registry.emplace<Transform>(_worldCamera, Transform {
            Vector3 { 0.f, 0.f, 0.f},
            Vector3 { 0.f, 0.f, 0.f},
            Vector3 { 1.f, 1.f, 1.f}
    });

    _fpsCamera = registry.create();
    registry.emplace<Transform>(_fpsCamera, Transform {
            Vector3 { 0.f, 0.f, 0.f},
            Vector3 { 0.f, 0.f, 0.f},
            Vector3 { 1.f, 1.f, 1.f}
    });
}

void View::update(float deltaTime) {
    if (!_registry) { return; }

    if (Input::getInstance().getKeyUp(Input::KeyCode::C)) {
        _isFpsCamera = !_isFpsCamera;
        if (_isFpsCamera) {
            _registry->remove<Camera>(_worldCamera);
            _registry->emplace<Camera>(_fpsCamera);
        } else {
            _registry->remove<Camera>(_fpsCamera);
            _registry->emplace<Camera>(_worldCamera);
        }
    }
    ImGui::Begin("View");
    ImGui::Text("Switch Camera (FPS/World): C");
    ImGui::Text(_isFpsCamera ? "Camera: First Person" : "Camera: World");
    ImGui::End();


    auto&& [_, playerTrans] = *_registry->view<Transform, Player>().each().begin();
    auto& trans = _registry->get<Transform>(_fpsCamera);
    trans.Translation = playerTrans.Translation * 1;
    trans.Rotation = playerTrans.Rotation;
}

void View::terminate() {

}
