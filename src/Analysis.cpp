#include <stdexcept>
#include "Analysis.hpp"
#include "Constants.hpp"

Analysis::Analysis(double sampleInterval)
    : sampleInterval(sampleInterval) 
    {
        if (sampleInterval <= 0.0) {
            throw std::invalid_argument("Analysis sample interval must be positive");
        }
    }


void Analysis::update(const State& state, double time){

    if (time >= nextTimeSample) {
        timeHistory.push_back(time);

        std::vector<Position> coms;
        coms.reserve(state.rods.size());
        for (const Rod& rod : state.rods){
            coms.push_back({
                rod.centreOfMass.x,
                rod.centreOfMass.y
            });
        }

        comHistory.push_back(coms);

        nextTimeSample += sampleInterval;
    }
}