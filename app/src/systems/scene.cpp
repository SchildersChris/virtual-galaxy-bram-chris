#include "scene.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"
#include "../utils/wavefront-object.hpp"
#include "../components/camera.hpp"

#include <imgui.h>
#include <utils/input.hpp>

void Scene::init(entt::registry& registry) {
    _step = 0;
    _fps = 0;
    _activeFps = 0;
    _registry = &registry;
    _isFpsCamera = false;

    _worldCamera = registry.create();
    registry.emplace<Camera>(_fpsCamera);
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
    auto& object = registry.emplace<Object>(_fpsCamera, Object {});
    WavefrontObject::load("assets/spaceship.obj", object.Vertices, object.Indices);
}

void Scene::update(float deltaTime) {
    if (!_registry) { return; }

    if (Input::getInstance().getKeyUp(Input::KeyCode::C)) {
        if (_isFpsCamera) {
            _registry->remove<Camera>(_worldCamera);
            _registry->emplace<Camera>(_fpsCamera);
        } else {
            _registry->remove<Camera>(_fpsCamera);
            _registry->emplace<Camera>(_worldCamera);
        }
        _isFpsCamera = !_isFpsCamera;
    }

    ++_fps;
    _step += deltaTime;

    if (_step >= 1000) {
        _activeFps = _fps;
        _fps = 0;
        _step = 0;
    }

    ImGui::Begin("Scene");
    ImGui::Text("FPS: %.d", _activeFps);
    ImGui::Text(_isFpsCamera ? "Camera: First Person" : "Camera: World");
    ImGui::End();
}

void Scene::terminate() {}
