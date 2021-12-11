#include "graphics/renderer.hpp"

#include <stdexcept>

Renderer Renderer::_instance;
Renderer& Renderer::GetInstance() {
    return _instance;
}

void Renderer::Init(const std::string& title, bool fullscreen, int32 width, int32 height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    if (!(_window = SDL_CreateWindow(
            title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, static_cast<SDL_WindowFlags>(fullscreen) | SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN))) {
        throw std::runtime_error(SDL_GetError());
    }

    if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED))) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Renderer::Terminate() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    _renderer = nullptr;
    _window = nullptr;
}

Frame Renderer::BeginFrame() {
    if (!_renderer || !_window) {
        throw std::runtime_error("Renderer is not property initialized!");
    }

    return Frame(*this);
}
