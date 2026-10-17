#include <raylib.h>
#include <raymath.h>
#include <string>
#include <algorithm>        

#include "Position.hpp"
#include "State.hpp"
#include "Constants.hpp"
#include "MathUtils.hpp"
#include "Renderer.hpp"
#include "Analysis.hpp"

const std::string& raw_data_file = "../data/raw/pendulum.csv";

int main() {

    // Initialisation
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Game Window");
    InitAudioDevice();
    SetTargetFPS(60);

    State state;
        state.anchor = Constants::ANCHOR;
        state.N = Constants::PENDULUM_NUMBER;
        state.length =  {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        state.radius =  {0.05f, 0.05f, 0.05f, 0.05f, 0.05f, 0.05f};
        state.mass =    {55.0f, 55.0f, 55.0f, 55.0f, 55.0f, 55.0f};
        state.theta =   {1.2f, 1.5f, 1.1f, 1.1f, 1.2f, 1.5f};
        state.omega =   {1.0f, 2.0f, 0.3f, 1.0f, 1.0f, 2.0f};
        state.rods = {};

        state.createRods();

    Renderer renderer;
    Analysis analysis(Constants::SAMPLE_INTERVAL); 

    double simulationTime = 0.0;
    double accumulator = 0.0;
    const double fixedDt = 0.001;


    while (!WindowShouldClose()) {
        float frameDt = GetFrameTime();
        frameDt = std::min(frameDt, 0.1f);
        accumulator += frameDt;

        while (accumulator >= fixedDt) {
            state.update(static_cast<float>(fixedDt));

            simulationTime += fixedDt;
            analysis.update(state, simulationTime);

            accumulator -= fixedDt;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            renderer.draw(state);
        EndDrawing();
    }

    analysis.exportCSV(raw_data_file);

    CloseWindow();
    return 0;
}