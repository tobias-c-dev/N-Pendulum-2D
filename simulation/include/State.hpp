#pragma once
#include "Position.hpp"
#include <vector>


struct Rod {

    Position start;
    Position centreOfMass;
    Position end;
    float currentTheta;

};


struct State {

    Position anchor;
    int N;

    // 
    std::vector<double> length;
    std::vector<double> radius; 
    std::vector<double> mass;
    
    std::vector<double> theta;
    std::vector<double> omega;
    
    std::vector<Rod> rods;

    void createRods();
    void update(float dt);
    
};
