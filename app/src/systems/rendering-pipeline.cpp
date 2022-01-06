#include <math/utils.hpp>
#include <imgui.h>
#include "rendering-pipeline.hpp"
#include "../components/camera.hpp"
#include "../components/transform.hpp"

#include "graphics/renderer.hpp"

void RenderingPipeline::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _projection = utils::getProjectionMatrix(
            _fov, _near, _far,static_cast<float>(renderer.getWidth()) / static_cast<float>(renderer.getHeight()));

    for (auto& elem : Elements) {
        elem->init(registry, _near, _far);
    }
}

void RenderingPipeline::update(float deltaTime) {
    if (!_registry) { return; }
    ImGui::Begin("Rendering Pipeline");
    for (auto& elem : Elements) {
        elem->update(deltaTime);
    }
    ImGui::End();

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();
    auto vp = _projection * camTrans.getMatrix();
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto m = transform.getMatrix();

        for (auto& elem : Elements) {
            elem->updateObject(entity, vp, m, object);
        }
    }

}

void RenderingPipeline::terminate() {
    for (auto& elem : Elements) {
        elem->terminate();
    }
}