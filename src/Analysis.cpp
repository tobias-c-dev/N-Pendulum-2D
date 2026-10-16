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
        std::vector<double> thetas;
        std::vector<double> omegas;

        int N = state.N;
        
        coms.reserve(state.rods.size());
        thetas.reserve(state.rods.size());
        omegas.reserve(state.rods.size());

        for (const Rod& rod : state.rods){
            coms.push_back({
                rod.centreOfMass.x,
                rod.centreOfMass.y
            });
        }

        for (int i; i=0; i<N){
            thetas.push_back(state.theta[i]);
            omegas.push_back(state.omega[i]);
        }

        comHistory.push_back(coms);
        thetaHistory.push_back(thetas);
        omegaHistory.push_back(omegas);

        nextTimeSample += sampleInterval;
    }
}