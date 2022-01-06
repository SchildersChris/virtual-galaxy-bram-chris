#include "app.hpp"
#include "systems/scene.hpp"
#include "systems/movement.hpp"
#include "systems/shooting.hpp"
#include "systems/rendering-pipeline.hpp"
#include "systems/rendering/rasterizer.hpp"
#include "systems/rendering/collision.hpp"
#include "systems/rendering/axis.hpp"
#include "systems/scaling.hpp"

App::App() : Application("Virtual Galaxy") {
    /*
     * Object update pipeline
     */
    auto pipeline = new RenderingPipeline(60, 2.f, 100.f);
    pipeline->Elements.emplace_back(std::make_unique<Rasterizer>(2.f, 100.f));
    pipeline->Elements.emplace_back(std::make_unique<Axis>(2.f, 100.f));
    pipeline->Elements.emplace_back(std::make_unique<Collision>());

    /*
     * Application update systems
     */
    Systems.emplace_back(std::make_unique<Scene>());
    Systems.emplace_back(std::make_unique<Movement>());
    Systems.emplace_back(std::make_unique<Shooting>());
    Systems.emplace_back(std::make_unique<Scaling>());
    Systems.emplace_back(std::unique_ptr<RenderingPipeline>(pipeline));
}

