#pragma once
#include <raylib.h>

namespace Constants {

    // Window
    inline constexpr float SCREEN_HEIGHT = 1000.0f;
    inline constexpr float SCREEN_WIDTH = 1800.0f;
    inline constexpr float PPM = 200.0f;

    // Environment
    constexpr double GRAVITY = 3.71;
    constexpr double ATMOSPHERIC_DENSITY = 0.02;
    constexpr int PENDULUM_NUMBER = 6;

    // Rod 
    constexpr Vector2 ANCHOR = {SCREEN_WIDTH / 2, 50.0f};
    constexpr Color COLOUR = RAYWHITE;
    constexpr double DRAG_COEFFICIENT = 1.2;

}