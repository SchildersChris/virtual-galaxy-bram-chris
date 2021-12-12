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

    _width = width;
    _height = height;

    if (!(_surface = SDL_CreateTexture(
            _renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            _width, _height))) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Renderer::Terminate() {
    SDL_DestroyTexture(_surface);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    _renderer = nullptr;
    _window = nullptr;
}

Buffer Renderer::BeginFrame() {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);

    uint32* pixels;
    int32 stride;

    if (SDL_LockTexture(_surface, nullptr, (void**)&pixels, &stride)) {
        throw std::runtime_error(SDL_GetError());
    }

    return Buffer { pixels };
}

void Renderer::EndFrame() {
    SDL_UnlockTexture(_surface);
    SDL_RenderCopy(_renderer, _surface, nullptr, nullptr);

    SDL_RenderPresent(_renderer);
}

int32 Renderer::GetWidth() const {
    return _width;
}

int32 Renderer::GetHeight() const {
    return _height;
}