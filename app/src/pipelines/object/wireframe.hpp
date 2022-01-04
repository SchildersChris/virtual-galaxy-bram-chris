#ifndef VIRTUAL_GALAXY_WIREFRAME_HPP
#define VIRTUAL_GALAXY_WIREFRAME_HPP

#include "../../systems/object-pipeline.hpp"

#include "math/vector2.hpp"
#include "math/vector4.hpp"
#include "math/matrix4x4.hpp"

class Wireframe : public ObjectPipeline::Element {
public:
    Wireframe(float near, float far) : _near(near), _far(far) {}

    void updateObject(const Matrix4x4& mvp, const Object& object) override;

private:
    float _near;
    float _far;
};

#endif //VIRTUAL_GALAXY_WIREFRAME_HPP
