#include "Analysis.hpp"
#include "Constants.hpp"

void Analysis::update(const State& state, double time){

    if (time >= nextTimeSample) {
        timeHistory.push_back(time);

        std::vector<Position> coms;
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