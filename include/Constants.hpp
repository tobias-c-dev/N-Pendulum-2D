#pragma once
#include "Position.hpp"

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
    constexpr Position ANCHOR = {SCREEN_WIDTH / 2, 50.0f};
    constexpr double DRAG_COEFFICIENT = 1.2;
    constexpr bool USE_ROD_TEXTURE = true;


}