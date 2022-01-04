#include <math/utils.hpp>
#include "object-pipeline.hpp"
#include "../pipelines/object/rasterizer.hpp"
#include "../components/camera.hpp"
#include "../components/transform.hpp"

#include "graphics/renderer.hpp"

void ObjectPipeline::init(entt::registry& registry) {
    _registry = &registry;

    auto& renderer = Renderer::getInstance();
    _projection = utils::getProjectionMatrix(
            _fov, _near, _far,static_cast<float>(renderer.getWidth()) / static_cast<float>(renderer.getHeight()));

    for (auto& elem : Elements) {
        elem->init(registry);
    }
}

void ObjectPipeline::update(float deltaTime) {
    if (!_registry) { return; }

    for (auto& elem : Elements) {
        elem->update(deltaTime);
    }

    auto&& [_, camTrans] = *_registry->view<Transform, Camera>().each().begin();
    auto vp = _projection * camTrans.getMatrix();
    for (auto&& [entity, transform, object] : _registry->group<Transform, Object>().each()) {
        auto m = transform.getMatrix();

        for (auto& elem : Elements) {
            elem->updateObject(entity, vp, m, object);
        }
    }
}

void ObjectPipeline::terminate() {
    for (auto& elem : Elements) {
        elem->terminate();
    }
}