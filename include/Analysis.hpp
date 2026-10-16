#pragma once
#include "State.hpp"
#include "Position.hpp"
#include <vector>


class Analysis {
public:
    explicit Analysis(double sampleInterval);

    void update(const State& state, double time);

private:
    double sampleInterval;
    double nextTimeSample = 0.0;

    std::vector<double> timeHistory;
    std::vector<std::vector<double>> thetaHistory;
    std::vector<std::vector<double>> omegaHistory;
    std::vector<std::vector<Position>> comHistory;

}; 