#include "demo.hpp"
#include "../components/transform.hpp"
#include "../components/object.hpp"

void Demo::init(entt::registry& registry) {
    auto entity = registry.create();
    registry.emplace<Transform>(entity, Transform {
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f},
        { 0.f, 0.f, 0.f}
    });

    auto& object = registry.emplace<Object>(entity, Object {});

    // Triangle 1
    object.Vertices.emplace_back(-.2f, -.5f, 1.f); // Left point
    object.Vertices.emplace_back(.5f, -.5f, 1.9f); // Right point
    object.Vertices.emplace_back(0.f, .5f, 1.f); // Top (middle) point

    object.Indices.push_back(0);
    object.Indices.push_back(1);
    object.Indices.push_back(2);

    // Triangle 2
    object.Vertices.emplace_back(-.5f, -.5f, 2.f); // Left point
    object.Vertices.emplace_back(.0f, -.0f, 2.f); // Right point
    object.Vertices.emplace_back(0.f, .5f, 2.f); // Top (middle) point

    object.Indices.push_back(3);
    object.Indices.push_back(4);
    object.Indices.push_back(5);
}

void Demo::update(float deltaTime, Buffer& frame) {}

void Demo::terminate() {}
