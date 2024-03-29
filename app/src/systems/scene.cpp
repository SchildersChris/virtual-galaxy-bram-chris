#include "scene.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"
#include "../utils/wavefront-object.hpp"
#include "../components/actor.hpp"
#include "../components/camera.hpp"
#include "../components/collider.hpp"
#include "../components/destroy.hpp"
#include "../components/bullet.hpp"
#include "../components/scale.hpp"

#include "core/input.hpp"
#include "core/application.hpp"

#include <imgui.h>

void Scene::init(entt::registry& registry) {
    _registry = &registry;
    _step = 0;
    _fps = 0;
    _activeFps = 0;

    auto camera = registry.create();
    registry.emplace<Camera>(camera, Camera {
        Vector3 {0, 0, 0},
        Vector3 {0, 0, -1}
    });
    registry.emplace<Transform>(camera,
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f});

    auto spaceship = registry.create();
    registry.emplace<Transform>(spaceship,
        Vector3 { 0.f, 0.f, 10.f},
        Vector3 { 0.f, 0.f, 0.f},
        Vector3 { 1.f, 1.f, 1.f});
    registry.emplace<Collider>(spaceship, [&, spaceship](entt::entity other) {
        if (!registry.all_of<Bullet>(other)) {
            registry.emplace<Destroy>(spaceship);
        }
    });
    registry.emplace<Actor>(spaceship);
    {
        auto& object = registry.emplace<Object>(spaceship, Color(27, 161, 226, 255));
        WavefrontObject::load("assets/spaceship2.obj", object.Vertices, object.Indices);
    }

    auto planet = registry.create();
    auto& trans = registry.emplace<Transform>(planet,
      Vector3 { 7.f, 0.f, 10.f},
      Vector3 { 0.f, -60.f, 0.f},
      Vector3 { 1.f, 1.f, 1.f});
    registry.emplace<Scale>(planet);
    {
        auto& object = registry.emplace<Object>(planet, Color::green());
        WavefrontObject::load("assets/planet.obj", object.Vertices, object.Indices);
    }
}

void Scene::update(float deltaTime) {
    if (!_registry) { return; }

    if (Input::getInstance().getKeyDown(Input::KeyCode::ESCAPE)) {
        Application::quit();
    }

    auto view = _registry->view<Destroy>();
    _registry->destroy(view.begin(), view.end());

    ++_fps;
    _step += deltaTime;

    if (_step >= 1000) {
        _activeFps = _fps;
        _fps = 0;
        _step = 0;
    }

    ImGui::Begin("Scene");
    ImGui::Text("FPS: %.d", _activeFps);
    ImGui::Text("Press 'Esc' to quit");
    if (ImGui::CollapsingHeader("Spaceship Controls", false)) {
        ImGui::Text("Roll: Q/E");
        ImGui::Text("Pitch: W/S");
        ImGui::Text("Yaw: A/D");
        ImGui::Text("Accelerate: Shift");
        ImGui::Text("Shoot: Space");
    }
    if (ImGui::CollapsingHeader("Camera Controls", false)) {
        ImGui::Text("Forward/Back: Up/Down arrow");
        ImGui::Text("Left/Right: Left/Right arrow");
        ImGui::Text("Up/Down: Page Up/Down");
    }
    ImGui::End();
}