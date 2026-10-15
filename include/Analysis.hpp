#pragma once
#include "State.hpp"
#include "Position.hpp"
#include <vector>


class Analysis {
public:
    Analysis(double sampleInterval);

    void update(const State& state, double time);

private:
    double sampleInterval;
    double nextTimeSample = 0.0;

    std::vector<double> timeHistory;
    std::vector<std::vector<Position>> comHistory;

};