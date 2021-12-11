#include "graphics/renderer.hpp"
#include "utils/input.hpp"

#include <string>

int main() {
    auto& renderer = Renderer::GetInstance();
    auto& input = Input::GetInstance();

    renderer.Init("Virtual Galaxy", false, 800, 600);
    input.Init();

    while (!input.IsQuit()) {
        auto frame = renderer.BeginFrame();
        // Todo: Write to frame
        frame.EndFrame();

        input.Update();
    }

    input.Terminate();
    renderer.Terminate();
    return 0;
}
