#pragma once
#include <raylib.h>

class State;

class Renderer{
public:
    Renderer();
    ~Renderer();

    void draw(const State& state);

private:
    Texture2D rodTexture{};
};

