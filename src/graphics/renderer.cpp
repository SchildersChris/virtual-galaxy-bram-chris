#include "graphics/renderer.hpp"
#include "utils/color.hpp"

#include <imgui.h>
#include <imgui_sdl.h>
#include <stdexcept>

Renderer Renderer::_instance;
Renderer& Renderer::getInstance() {
    return _instance;
}

void Renderer::init(const std::string& title, bool fullscreen, int32 width, int32 height) {
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

    if (!(_texture = SDL_CreateTexture(
            _renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STREAMING,
            _width, _height))) {
        throw std::runtime_error(SDL_GetError());
    }

    ImGui::CreateContext();
    ImGuiSDL::Initialize(_renderer, _width, _height);
}


int32 Renderer::getWidth() const {
    return _width;
}

int32 Renderer::getHeight() const {
    return _height;
}

void Renderer::setClearColor(uint8 r, uint8 g, uint8 b) {
    _clearColor = color::rgbToInteger(r, g, b);
}

void Renderer::beginFrame(float deltaTime) {
    ImGuiIO& io = ImGui::GetIO();

    int32 mouseX, mouseY;
    uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

    io.DeltaTime = deltaTime;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

    ImGui::NewFrame();

    SDL_Surface* surface;
    if (SDL_LockTextureToSurface(_texture, nullptr, &surface)) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_FillRect(surface, nullptr, _clearColor);

    _activeBuffer = static_cast<uint32*>(surface->pixels);
}

void Renderer::setPixel(int32 x, int32 y, uint8 r, uint8 g, uint8 b, uint8 a) {
    _activeBuffer[x + y * _width] = color::rgbaToInteger(r, g, b, a);
}

void Renderer::setPixel(int32 i, uint8 r, uint8 g, uint8 b, uint8 a) {
    _activeBuffer[i] = color::rgbaToInteger(r, g, b, a);
}

void Renderer::endFrame() {
    SDL_UnlockTexture(_texture);
    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);

    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(_renderer);
}

void Renderer::terminate() {
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();

    SDL_DestroyTexture(_texture);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    _texture = nullptr;
    _renderer = nullptr;
    _window = nullptr;
}