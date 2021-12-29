#include "scene.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"
#include "../utils/wavefront-object.hpp"
#include "../components/camera.hpp"

#include <imgui.h>
#include <core/input.hpp>

void Scene::init(entt::registry& registry) {
    _step = 0;
    _fps = 0;
    _activeFps = 0;
    _registry = &registry;
    _isFpsCamera = false;

    _worldCamera = registry.create();
    registry.emplace<Camera>(_worldCamera);
    registry.emplace<Transform>(_worldCamera, Transform {
        Vector3 { 0.f, 0.f, -40.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f}
    });

    _fpsCamera = registry.create();
    registry.emplace<Transform>(_fpsCamera, Transform {
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f}
    });

    auto o = registry.create();
    registry.emplace<Transform>(o, Transform {
            Vector3 { 0.f, 0.f, -20.f},
            Vector3 { 0.f, 0.f, 0.f},
            Vector3 { 1.f, 1.f, 1.f}
    });
    auto& object = registry.emplace<Object>(o, Object {});
    WavefrontObject::load("assets/spaceship.obj", object.Vertices, object.Indices);

//    object.Vertices.emplace_back(-.5f, -.5f, 1.f); // Left point
//    object.Vertices.emplace_back(.5f, -.5f, 1.f); // Right point
//    object.Vertices.emplace_back(0.f, .5f, 1.f); // Top (middle) point
//
//    object.Indices.push_back(1);
//    object.Indices.push_back(2);
//    object.Indices.push_back(3);
}

void Scene::update(float deltaTime) {
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

    ++_fps;
    _step += deltaTime;

    if (_step >= 1000) {
        _activeFps = _fps;
        _fps = 0;
        _step = 0;
    }

    ImGui::Begin("Scene");
    ImGui::Text("FPS: %.d", _activeFps);
    if (ImGui::CollapsingHeader("Info", false)) {
        ImGui::Text(_isFpsCamera ? "Camera: First Person" : "Camera: World");
    }

    if (ImGui::CollapsingHeader("Controls", false)) {
        ImGui::Text("Switch Camera (FPS/World): C");
        ImGui::Text("Roll: Q/E");
        ImGui::Text("Pitch: W/S");
        ImGui::Text("Yaw: A/D");
        ImGui::Text("Shoot: Space");
    }
    ImGui::End();
}

void Scene::terminate() {}
