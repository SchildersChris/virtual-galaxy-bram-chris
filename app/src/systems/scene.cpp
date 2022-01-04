#include "scene.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"
#include "../utils/wavefront-object.hpp"
#include "../components/player.hpp"
#include "../components/camera.hpp"

#include <imgui.h>

void Scene::init(entt::registry& registry) {
    _step = 0;
    _fps = 0;
    _activeFps = 0;

    auto camera = registry.create();
    registry.emplace<Camera>(camera);
    registry.emplace<Transform>(camera,
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f});

    auto spaceship = registry.create();
    registry.emplace<Transform>(spaceship,
        Vector3 { 0.f, 0.f, 10.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f});

    registry.emplace<Player>(spaceship);
    {
        auto& object = registry.emplace<Object>(spaceship, Color(27, 161, 226, 255));
        WavefrontObject::load("assets/spaceship.obj", object.Vertices, object.Indices);
    }

    auto planets = registry.create();
    auto planetsTrans = registry.emplace<Transform>(planets,
        Vector3 { 10.f, 0.f, 10.f},
        Vector3 { 0.f, -60.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f});

    {
        auto planet = registry.create();
        auto trans = registry.emplace<Transform>(planet,
            Vector3 { 2.f, 0.f, 10.f},
            Vector3 { 0.f, -60.f, 0.f},
            Vector3 { 1.f, 1.f, 1.f});
        trans.Parent = &planetsTrans;
        auto& object = registry.emplace<Object>(planet, Color::green());
        WavefrontObject::load("assets/cube.obj", object.Vertices, object.Indices);
    }

    {
        auto planet = registry.create();
        auto trans = registry.emplace<Transform>(planet,
            Vector3 { 2.f, 0.f, 10.f},
            Vector3 { 0.f, -60.f, 0.f},
            Vector3 { 1.f, 1.f, 1.f});
        trans.Parent = &planetsTrans;
        auto& object = registry.emplace<Object>(planet, Color::red());
        WavefrontObject::load("assets/cube.obj", object.Vertices, object.Indices);
    }
}

void Scene::update(float deltaTime) {
    ++_fps;
    _step += deltaTime;

    if (_step >= 1000) {
        _activeFps = _fps;
        _fps = 0;
        _step = 0;
    }

    ImGui::Begin("Scene");
    ImGui::Text("FPS: %.d", _activeFps);
    if (ImGui::CollapsingHeader("Controls", false)) {
        ImGui::Text("Roll: Q/E");
        ImGui::Text("Pitch: W/S");
        ImGui::Text("Yaw: A/D");
        ImGui::Text("Shoot: Space");
    }

    if (ImGui::CollapsingHeader("Graph", false)) {
        ImGui::Text("Roll: Q/E");
        ImGui::Text("Pitch: W/S");
        ImGui::Text("Yaw: A/D");
        ImGui::Text("Shoot: Space");
    }
    ImGui::End();
}