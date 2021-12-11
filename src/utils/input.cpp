#include "utils/input.hpp"

#include "SDL.h"

Input Input::_instance;
Input& Input::GetInstance() {
    return _instance;
}

void Input::Init() {
    _keysUp = new uint8[AmountOfKeys];
    _keysDown = new uint8[AmountOfKeys];

    for (int i = 0; i < AmountOfKeys; ++i) {
        _keysUp[i] = 0;
        _keysDown[i] = 0;
    }

    _mouseButtonsDown = new uint8[AmountOfMouseButtons] { 0, 0, 0 };
    _mouseButtonsUp = new uint8[AmountOfMouseButtons] { 0, 0, 0 };

    _isQuit = false;
}

void Input::Terminate() {
    delete[] _keysDown;
    delete[] _keysUp;

    delete[] _mouseButtonsDown;
    delete[] _mouseButtonsUp;
}

void Input::Update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYUP: {
                _keysUp[event.key.keysym.scancode] = 1;
                _keysDown[event.key.keysym.scancode] = 0;
                break;
            }
            case SDL_KEYDOWN: {
                _keysDown[event.key.keysym.scancode] = 1;
                _keysUp[event.key.keysym.scancode] = 0;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                _mouseButtonsUp[event.button.button] = 0;
                _mouseButtonsDown[event.button.button] = 1;
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                _mouseButtonsUp[event.button.button] = 1;
                _mouseButtonsDown[event.button.button] = 0;
                break;
            }
            case SDL_QUIT: {
                _isQuit = true;
            }
        }
    }
}

Vector2 Input::MouseScreenPosition() const {
    int32 x, y;
    SDL_GetMouseState(&x, &y);

    return Vector2 { static_cast<float>(x), static_cast<float>(y) };
}

bool Input::GetKeyDown(KeyCode key) const {
    auto b = static_cast<uint8>(key);
    return _keysDown[b] && !_keysUp[b];
}

bool Input::GetKeyUp(KeyCode key) const {
    auto b = static_cast<uint8>(key);
    return _keysUp[b] && !_keysDown[b];
}

bool Input::GetMouseButtonDown(MouseButton button) const {
    auto b = static_cast<uint8>(button);
    return _mouseButtonsDown[b] && !_mouseButtonsUp[b];
}

bool Input::GetMouseButtonUp(MouseButton button) const {
    auto b = static_cast<uint8>(button);
    return _mouseButtonsUp[b] && !_mouseButtonsDown[b];
}

bool Input::IsQuit() const {
    return _isQuit;
}
