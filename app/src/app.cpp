#include "app.hpp"
#include "systems/scene.hpp"
#include "systems/movement.hpp"
#include "systems/shooting.hpp"
#include "systems/object-pipeline.hpp"
#include "pipelines/object/rasterizer.hpp"
#include "pipelines/object/collision.hpp"
#include "pipelines/object/axis.hpp"

App::App() : Application("Virtual Galaxy") {
    /*
     * Object update pipeline
     */
    auto pipeline = new ObjectPipeline(60, 2.f, 100.f);
    pipeline->Elements.emplace_back(std::make_unique<Rasterizer>(2.f, 100.f));
    pipeline->Elements.emplace_back(std::make_unique<Axis>(2.f, 100.f));
    pipeline->Elements.emplace_back(std::make_unique<Collision>());

    /*
     * Application update systems
     */
    Systems.emplace_back(std::make_unique<Scene>());
    Systems.emplace_back(std::make_unique<Movement>());
    Systems.emplace_back(std::make_unique<Shooting>());
    Systems.emplace_back(std::unique_ptr<ObjectPipeline>(pipeline));
}

