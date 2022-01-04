#include <imgui.h>
#include "axis.hpp"

#include "graphics/renderer.hpp"
#include "math/utils.hpp"

void Axis::init(entt::registry& registry) {}

void Axis::update(float deltaTime) {
    ImGui::Begin("Object-Axis");
    ImGui::Checkbox("Draw Axis", &_drawAxis);
    ImGui::End();
}

void Axis::updateObject(entt::entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) {
    auto mvp = vp * m;
    auto& renderer = Renderer::getInstance();

    if (_drawAxis) {
        auto c = Vector3 { 0, 0, 0 } * mvp;
        auto x = Vector3 { 1, 0, 0 } * mvp;
        auto y = Vector3 { 0, 1, 0 } * mvp;
        auto z = Vector3 { 0, 0, 1 } * mvp;

        if (c.W > -_near || c.W < -_far) { return; }

        auto rC = renderer.toRaster(c);
        auto rX = renderer.toRaster(x);
        auto rY = renderer.toRaster(y);
        auto rZ = renderer.toRaster(z);

        renderer.drawLine({rC.X, rC.Y}, {rX.X, rX.Y}, Color::green());
        renderer.drawLine({rC.X, rC.Y}, {rY.X, rY.Y}, Color::red());
        renderer.drawLine({rC.X, rC.Y}, {rZ.X, rZ.Y}, Color::blue());
    }
}
