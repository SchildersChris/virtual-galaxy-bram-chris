#include "math/vector3.hpp"
#include "math/matrix4x4.hpp"
#include "graphics/renderer.hpp"

int main() {
    auto& renderer = Renderer::GetInstance();
    renderer.Init();

    while () {

    }

    auto frame = renderer.BeginFrame();

//    frame.SetPixel()



    renderer.Terminate();
    return 0;
}
