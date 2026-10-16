#pragma once
#include "State.hpp"
#include "Position.hpp"
#include <vector>
#include <string>


class Analysis {
public:
    explicit Analysis(double sampleInterval);

    void update(const State& state, double time);
    void exportCSV(const std::string& filename) const;

private:
    double sampleInterval;
    double nextTimeSample = 0.0;

    std::vector<double> timeHistory;
    std::vector<std::vector<double>> thetaHistory;
    std::vector<std::vector<double>> omegaHistory;
    std::vector<std::vector<Position>> comHistory;

}; 