#pragma once
#include <raylib.h>
#include <vector>

struct Rod {

    Vector2 start;
    Vector2 centreOfMass;
    Vector2 end;
    float currentTheta;

};


struct State {

    Vector2 anchor;
    int N;

    // 
    std::vector<float> length;
    std::vector<float> radius; 
    std::vector<float> mass;
    
    std::vector<double> theta;
    std::vector<double> omega;
    
    std::vector<Rod> rods;

    void createRods();
    void update(float dt);
    
};
