#include "rendering.hpp"

#include <imgui.h>

Rendering::Rendering() :
        _wireframe(std::make_unique<Wireframe>()),
        _rasterizer(std::make_unique<Rasterizer>()) {}

void Rendering::init(entt::registry& registry, float near, float far) {
    _wireframe->init(registry, near, far);
    _rasterizer->init(registry, near, far);
}

void Rendering::update(float deltaTime) {
    ImGui::BeginChild("Rendering");
    ImGui::Checkbox("Draw Wireframe", &_drawWireframe);
    ImGui::EndChild();

    if (_drawWireframe) {
        _wireframe->update(deltaTime);
    } else {
        _rasterizer->update(deltaTime);
    }
}

void Rendering::updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) {
    if (_drawWireframe) {
        _wireframe->updateObject(entity, vp, m, object);
    } else {
        _rasterizer->updateObject(entity, vp, m, object);
    }
}

void Rendering::terminate() {
    _wireframe->terminate();
    _rasterizer->terminate();
}