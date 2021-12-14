#include "demo.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"
#include "../utils/reader.hpp"
#include "../components/camera.hpp"

#include "math/matrix4x4.hpp"
#include <imgui.h>
#include <valarray>

void Demo::init(entt::registry& registry) {
    _step = 0;
    _fps = 0;
    _activeFps = 0;
    _registry = &registry;

    auto camera = registry.create();
    registry.emplace<Camera>(camera);
    registry.emplace<Transform>(camera, Transform {
            { 0.f, 0.f, 1.f},
            { 0.f, 0.f, 0.f},
            { 1.f, 1.f, 1.f}
    });

    auto entity = registry.create();
    registry.emplace<Transform>(entity, Transform {
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f}
    });

    auto& object = registry.emplace<Object>(entity, Object {});

    Reader::load("assets/cube.obj", object.Vertices, object.Indices);

    float angle = .3f;
    float mat[16] = {
        std::cos(angle), 0, std::sin(angle), 0,
        0, 1, 0, 0,
        -std::sin(angle), 0, std::cos(angle), 0,
        0, 0, 5, 1
    };

    auto matrix = Matrix4x4(mat);
    auto scale = Matrix4x4::scale(0.7, 1, 1);

    for (auto& v : object.Vertices) {
        v *= matrix;
        v *= scale;
    }

//    object.Vertices.emplace_back(-.5f, -.5f, 1.f); // Left point
//    object.Vertices.emplace_back(.5f, -.5f, 1.f); // Right point
//    object.Vertices.emplace_back(0.f, .5f, 1.f); // Top (middle) point


//    // Triangle 1
//    object.Vertices.emplace_back(-.2f, -.5f, 1.f); // Left point
//    object.Vertices.emplace_back(.5f, -.5f, 1.9f); // Right point
//    object.Vertices.emplace_back(0.f, .5f, 1.f); // Top (middle) point
//
//    object.Indices.push_back(1);
//    object.Indices.push_back(2);
//    object.Indices.push_back(3);
//
//     Triangle 2
//    object.Vertices.emplace_back(-.5f, -.5f, 2.f); // Left point
//    object.Vertices.emplace_back(.0f, -.5f, 2.f); // Right point
//    object.Vertices.emplace_back(0.f, .5f, 2.f); // Top (middle) point
//
//    object.Indices.push_back(4);
//    object.Indices.push_back(5);
//    object.Indices.push_back(6);
}

void Demo::update(float deltaTime) {
    if (!_registry) { return; }

    ++_fps;
    _step += deltaTime;

    if (_step >= 1000) {
        _activeFps = _fps;
        _fps = 0;
        _step = 0;
    }

    ImGui::Begin("Statistics");
    ImGui::Text("FPS: %.d", _activeFps);
    ImGui::End();
}

void Demo::terminate() {}
