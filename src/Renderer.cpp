#include "Renderer.hpp"
#include "State.hpp"
#include "Constants.hpp"
#include <raymath.h>
#include <cmath>

constexpr Color ROD_COLOUR = WHITE;

Renderer::Renderer() {

    if (Constants::USE_ROD_TEXTURE) {
        rodTexture = LoadTexture("../assets/Lewis.png");
    }
}

Renderer::~Renderer() {
    if (Constants::USE_ROD_TEXTURE) {
        UnloadTexture(rodTexture);
    }
}

void Renderer::draw(const State& state) {

    for (const Rod& rod: state.rods) {

        float pixelLength = rod.length * Constants::PPM;
        float pixelWidth = rod.radius * 2.0f * Constants::PPM;

        float rotationInDegrees =
            -rod.currentTheta * (180.0f / PI);

        Rectangle dest = {
            rod.start.x,
            rod.start.y,
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

