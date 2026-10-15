#pragma once
#include <raylib.h>

class State;

class Renderer{
public:
    Renderer();

    void draw(const State& state);

private:
    Texture2D rodTexture;
};

