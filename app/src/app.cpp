#include "app.hpp"
#include "systems/scene.hpp"
#include "systems/movement.hpp"
#include "systems/shooting.hpp"
#include "systems/rendering-pipeline.hpp"
#include "systems/rendering/collision.hpp"
#include "systems/rendering/axis.hpp"
#include "systems/scaling.hpp"
#include "systems/rendering/rendering.hpp"

App::App() : Application("Virtual Galaxy") {
    const float nearClip = 2.f;
    const float farClip = 100.f;
    const float fov = 60.f;

    /*
     * Object update pipeline
     */
    auto pipeline = new RenderingPipeline(fov, nearClip, farClip);
    pipeline->Elements.emplace_back(std::make_unique<Collision>());
    pipeline->Elements.emplace_back(std::make_unique<Rendering>());
    pipeline->Elements.emplace_back(std::make_unique<Axis>());

    /*
     * Application update systems
     */
    Systems.emplace_back(std::make_unique<Scene>());
    Systems.emplace_back(std::make_unique<Movement>());
    Systems.emplace_back(std::make_unique<Shooting>());
    Systems.emplace_back(std::make_unique<Scaling>());
    Systems.emplace_back(std::unique_ptr<RenderingPipeline>(pipeline));
}

