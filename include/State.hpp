#pragma once
#include <raylib.h>
#include <vector>

struct Rod {

    Vector2 start;
    Vector2 end;
    float length;
    float radius;
    float mass;
    Color colour;
    float currentTheta;

    Vector2 centreOfMass(int rod_index, const std::vector<double>& theta, const std::vector<float>& length);        // could be put in mathutils
    void draw(Texture2D texture);

};


struct State {

    Vector2 anchor;
    int N;

    std::vector<Vector2> start;
    std::vector<Vector2> end;
    std::vector<float> length;
    std::vector<float> radius; 
    std::vector<float> mass;
    std::vector<double> theta;
    std::vector<double> omega;
    std::vector<Rod> rods;

    void createRods();
    void update(float dt);
    void draw(Texture2D texture);
    
};
