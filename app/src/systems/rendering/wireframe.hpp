#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "../rendering-pipeline.hpp"

#include "math/vector2.hpp"
#include "math/vector4.hpp"
#include "math/matrix4x4.hpp"

class Wireframe : public RenderingPipeline::Element {
public:
    void init(entt::registry& registry, float nearClipping, float farClipping) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;

private:
    float _near {0};
    float _far {0};
};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
