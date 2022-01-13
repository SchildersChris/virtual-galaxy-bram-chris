#ifndef VIRTUAL_GALAXY_RENDERING_PIPELINE_HPP
#define VIRTUAL_GALAXY_RENDERING_PIPELINE_HPP

#include "../components/object.hpp"

#include "math/matrix4x4.hpp"
#include "core/system.hpp"
#include "../components/camera.hpp"

class RenderingPipeline : public System {
public:
    class Element {
    public:
        [[maybe_unused]] virtual void init(entt::registry& registry, float nearClipping, float farClipping) {};
        [[maybe_unused]] virtual void update(float deltaTime) {};
        /**
         * Update object based on the mvp matrix
         *
         * @param entity Entity id
         * @param vp View projection matrix of the object
         * @param mvp Model matrix of the object
         * @param object Object data
         */
        [[maybe_unused]] virtual void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) {};

        [[maybe_unused]] virtual void terminate() {};
    };

    RenderingPipeline(float fov, float nearClipping, float farClipping) : _fov(fov), _near(nearClipping), _far(farClipping) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void terminate() override;

    std::vector<std::unique_ptr<Element>> Elements {};

private:
    static Matrix4x4 calculateCamera(const Camera& camera);

    entt::registry* _registry {nullptr};

    float _near;
    float _far;
    float _fov;
    Matrix4x4 _projection;
};

#endif //VIRTUAL_GALAXY_RENDERING_PIPELINE_HPP
