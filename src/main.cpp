#include <raylib.h>
#include <raymath.h>
#include "State.hpp"
#include "Constants.hpp"
#include "MathUtils.hpp"

int main() {

    // Initialisation
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Game Window");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D rodTexture = {};

    if (Constants::USE_ROD_TEXTURE) {
        rodTexture = LoadTexture("../assets/Scrun.png");
    }

    State state;
        state.anchor = Constants::ANCHOR;
        state.N = Constants::PENDULUM_NUMBER;
        state.length =  {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        state.radius =  {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
        state.mass =    {55.0f, 55.0f, 55.0f, 55.0f, 55.0f, 55.0f};
        state.theta =   {1.2f, 1.5f, 1.1f, 1.1f, 1.2f, 1.5f};
        state.omega =   {1.0f, 2.0f, 0.3f, 1.0f, 1.0f, 2.0f};
        state.rods = {};

        state.createRods();


    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        state.update(dt);

        BeginDrawing();
            ClearBackground(BLACK);
            state.draw(rodTexture);
        EndDrawing();
    }

    if (Constants::USE_ROD_TEXTURE) {
        UnloadTexture(rodTexture);
    }

    CloseWindow();
    return 0;
}