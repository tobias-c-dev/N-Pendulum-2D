#pragma once
#include "State.hpp"


struct Position {
    double x;
    double y;
};


class Analysis {
public:
    Analysis(double sampleInterval);

    void update(const State& state, double time);

private:
    double sampleInterval;
    double timeSinceLastSample = 0.0;

    std::vector<double> timeHistory;
    std::vector<std::vector<Position>> comHistory;

};