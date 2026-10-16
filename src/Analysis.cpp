#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "Analysis.hpp"
#include "Constants.hpp"

Analysis::Analysis(double sampleInterval)
    : sampleInterval(sampleInterval) 
    {
        if (sampleInterval <= 0.0) {
            throw std::invalid_argument("Analysis sample interval must be positive");
        }
    }

void Analysis::exportCSV(const std::string& filename) const{

    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not open CSV file: " + filename
        );
    }

    if (timeHistory.empty()) {return;}

    const std::size_t N = thetaHistory[0].size();

    // Header
    file << "time";

    for (std::size_t i = 0; i < N; ++i) {file << ",theta_" << i;}

    for (std::size_t i = 0; i < N; ++i) {file << ",omega_" << i;}

    for (std::size_t i = 0; i < N; ++i) {
        file << ",com_x_" << i;
        file << ",com_y_" << i;
    }

    file << '\n';

    // Data
    file << std::setprecision(15);

    for (std::size_t t = 0; t < timeHistory.size(); ++t) {

        file << timeHistory[t];

        // Theta
        for (std::size_t i = 0; i < N; ++i) {file << "," << thetaHistory[t][i];}

        // Omega
        for (std::size_t i = 0; i < N; ++i) {file << "," << omegaHistory[t][i];}

        // Centre of mass
        for (std::size_t i = 0; i < N; ++i) {
            file << "," << comHistory[t][i].x;
            file << "," << comHistory[t][i].y;
        }

        file << '\n';
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