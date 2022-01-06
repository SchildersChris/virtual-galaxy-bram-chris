#ifndef VIRTUAL_GALAXY_AXIS_HPP
#define VIRTUAL_GALAXY_AXIS_HPP

#include "../rendering-pipeline.hpp"

class Axis : public RenderingPipeline::Element {
public:
    Axis(float near, float far) : _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void updateObject(entt::entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;

private:
    bool _drawAxis {true};

    float _near{0};
    float _far{0};
};

#endif //VIRTUAL_GALAXY_AXIS_HPP
