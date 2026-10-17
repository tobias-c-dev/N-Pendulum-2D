#pragma once
#include "Position.hpp"

namespace Constants {

    // Window
    inline constexpr float SCREEN_HEIGHT = 1000.0f;
    inline constexpr float SCREEN_WIDTH = 1800.0f;
    inline constexpr float PPM = 200.0f;

    // Environment
    constexpr double GRAVITY = 9.81;
    constexpr double ATMOSPHERIC_DENSITY = 0.0;
    constexpr int PENDULUM_NUMBER = 6;

    // Rod 
    constexpr Position ANCHOR = {0.0, 0.0}; // world-anchor in m
    constexpr double DRAG_COEFFICIENT = 0.0;
    constexpr bool USE_ROD_TEXTURE = false;

    // Analysis
    constexpr double SAMPLE_INTERVAL = 0.01;

}