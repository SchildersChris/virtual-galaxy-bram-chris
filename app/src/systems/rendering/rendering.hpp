#ifndef VIRTUAL_GALAXY_RENDERING_HPP
#define VIRTUAL_GALAXY_RENDERING_HPP

#include "../rendering-pipeline.hpp"
#include "wireframe.hpp"
#include "rasterizer.hpp"

class Rendering : public RenderingPipeline::Element {
public:
    Rendering();

    void init(entt::registry& registry, float near, float far) override;
    void update(float deltaTime) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;
    void terminate() override;
private:
    bool _drawWireframe {false};

    std::unique_ptr<Rasterizer> _rasterizer;
    std::unique_ptr<Wireframe> _wireframe;
};


#endif //VIRTUAL_GALAXY_RENDERING_HPP
