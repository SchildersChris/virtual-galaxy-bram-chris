#ifndef VIRTUAL_GALAXY_OBJECT_PIPELINE_HPP
#define VIRTUAL_GALAXY_OBJECT_PIPELINE_HPP

#include "../components/object.hpp"

#include "math/matrix4x4.hpp"
#include "core/system.hpp"

class ObjectPipeline : public System {
public:
    class Element : public System {
    public:
        [[maybe_unused]] void init(entt::registry& registry) override {};
        [[maybe_unused]] void update(float deltaTime) override {};

        /**
         * Update object based on the mvp matrix
         *
         * @param mvp Model view projection matrix of the object
         * @param object Object to update
         */
        [[maybe_unused]] virtual void updateObject(const Matrix4x4& mvp, const Object& object) {};
    };

    ObjectPipeline(float fov, float near, float far) : _fov(fov), _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

    std::vector<std::unique_ptr<Element>> Elements {};

private:
    entt::registry* _registry {nullptr};

    float _near;
    float _far;
    float _fov;
    Matrix4x4 _projection;
};

#endif //VIRTUAL_GALAXY_OBJECT_PIPELINE_HPP
