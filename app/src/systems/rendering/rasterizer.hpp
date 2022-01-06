#ifndef VIRTUAL_GALAXY_RASTERIZER_HPP
#define VIRTUAL_GALAXY_RASTERIZER_HPP

#include "../rendering-pipeline.hpp"

#include "core/system.hpp"
#include "math/vector3.hpp"

class Rasterizer : public RenderingPipeline::Element {
public:
    Rasterizer(float near, float far) : _near(near), _far(far) {}

    void init(entt::registry& registry) override;
    void update(float deltaTime) override;
    void updateObject(entt::entity entity, const Matrix4x4& vp, const Matrix4x4& m, const Object& object) override;
    void terminate() override;

private:
    /**
     * Rasterize a triangle to the screen
     *
     * @param r Raster points
     */
    void rasterizeTriangle(const Vector3 r[3]);

    /**
     * Get flat shade value of the triangle normal
     *
     * @param normal Normal of the triangle
     * @return Grayscale shade value between 0 and 1
     */
    static float getShade(const Vector3& normal);

    int32 _width {0};
    int32 _height {0};

    float* _zBuffer {nullptr};
    std::size_t _zBufferSize {0};

    float _near;
    float _far;
};

#endif //VIRTUAL_GALAXY_RASTERIZER_HPP
