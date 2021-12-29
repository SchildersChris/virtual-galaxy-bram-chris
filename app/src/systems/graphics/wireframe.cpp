#include "wireframe.hpp"
#include "../../components/transform.hpp"
#include "../../components/object.hpp"
#include "../../components/camera.hpp"

#include "math/vector3.hpp"
#include "graphics/renderer.hpp"
#include "math/utils.hpp"

#include <imgui.h>

Wireframe::Wireframe(float fov, float near, float far) : _projection(utils::getProjectionMatrix(fov, near, far)) {}

void Wireframe::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _width = renderer.getWidth();
    _height = renderer.getHeight();
}

void Wireframe::update(float deltaTime) {
    auto& renderer = Renderer::getInstance();

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();

    static bool drawAxis = true;

    ImGui::Begin("Renderer");
    ImGui::Checkbox("Test", &drawAxis);
    if (ImGui::CollapsingHeader("Camera Transform")) {
        ImGui::Text("Translation");
        ImGui::SliderFloat("Tx", &camTrans.Translation.X, -40, 40);
        ImGui::SliderFloat("Ty", &camTrans.Translation.Y, -40, 40);
        ImGui::SliderFloat("Tz", &camTrans.Translation.Z, -40, 40);
        ImGui::Text("Rotation");
        ImGui::SliderFloat("Rx", &camTrans.Rotation.X, -40, 40);
        ImGui::SliderFloat("Ry", &camTrans.Rotation.Y, -40, 40);
        ImGui::SliderFloat("Rz", &camTrans.Rotation.Z, -40, 40);
        ImGui::Text("Scale");
        ImGui::SliderFloat("Sx", &camTrans.Scale.X, -40, 40);
        ImGui::SliderFloat("Sy", &camTrans.Scale.Y, -40, 40);
        ImGui::SliderFloat("Sz", &camTrans.Scale.Z, -40, 40);
    }
    ImGui::End();

    auto vp = _projection * camTrans.getMatrix();
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto mvp = vp * transform.getMatrix();

        for (int i = 0; i < object.Indices.size(); i += 3) {
            auto v0 = object.Vertices[object.Indices[i] - 1] * mvp;
            auto v1 = object.Vertices[object.Indices[i+1] - 1] * mvp;
            auto v2 = object.Vertices[object.Indices[i+2] - 1] * mvp;

            if (v0.W > 0 || v1.W > 0 || v2.W > 0) {
                continue;
            }

            auto r0 = toRaster(v0);
            auto r1 = toRaster(v1);
            auto r2 = toRaster(v2);

            renderer.drawLine(r0, r1, Color::white());
            renderer.drawLine(r1, r2, Color::white());
            renderer.drawLine(r2, r0, Color::white());
        }
    }
}

void Wireframe::terminate() {}

Vector2 Wireframe::toRaster(const Vector4& v) const {
    return {
        (1 + v.X / v.Z) * 0.5f * static_cast<float>(_width),
        (1 - v.Y / v.Z) * 0.5f * static_cast<float>(_height)
    };
}