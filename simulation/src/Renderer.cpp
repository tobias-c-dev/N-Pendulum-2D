#include "Renderer.hpp"
#include "State.hpp"
#include "Constants.hpp"
#include <raymath.h>
#include <cmath>

constexpr Color ROD_COLOUR = WHITE;
constexpr float SCREEN_ANCHOR_X = Constants::SCREEN_WIDTH / 2.0f;
constexpr float SCREEN_ANCHOR_Y = 50.0f;

Renderer::Renderer() {

    if (Constants::USE_ROD_TEXTURE) {
        rodTexture = LoadTexture("assets/Lewis.png");
    }
}

Renderer::~Renderer() {
    if (Constants::USE_ROD_TEXTURE) {
        UnloadTexture(rodTexture);
    }
}

void Renderer::draw(const State& state) {

    for (int i = 0; i < state.N; ++i) {

        const Rod& rod = state.rods[i];

        const float pixelLength =
            static_cast<float>(state.length[i] * Constants::PPM);

        const float pixelWidth =
            static_cast<float>(state.radius[i] * 2.0 * Constants::PPM);

        // Convert world-space positions to screen-space pixels.
        const Vector2 start = {
            SCREEN_ANCHOR_X +
                static_cast<float>(rod.start.x * Constants::PPM),

            SCREEN_ANCHOR_Y +
                static_cast<float>(rod.start.y * Constants::PPM)
        };

        const float rotationInDegrees =
            static_cast<float>(-rod.currentTheta * (180.0 / PI));

        Rectangle dest = {
            start.x,
            start.y,
            pixelWidth,
            pixelLength
        };

        Vector2 origin = {
            pixelWidth / 2.0f,
            0.0f
        };

        if (Constants::USE_ROD_TEXTURE) {

            Rectangle source = {
                0.0f,
                0.0f,
                static_cast<float>(rodTexture.width),
                static_cast<float>(rodTexture.height)
            };

            DrawTexturePro(
                rodTexture,
                source,
                dest,
                origin,
                rotationInDegrees,
                ROD_COLOUR
            );

        } 
        
        else {

            DrawRectanglePro(
                dest,
                origin,
                rotationInDegrees,
                ROD_COLOUR
            );
        }
    }
}

