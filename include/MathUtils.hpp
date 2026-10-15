#pragma once
#include <vector>
#include <Eigen/Dense>
#include "State.hpp"

struct Derivative {

        Eigen::VectorXd dTheta;
        Eigen::VectorXd dOmega;

};

namespace MathUtils {

    Derivative evaluate(const State& state);

    void buildMassMatrix(
        Eigen::MatrixXd& M, 
        const State& state
    );

    void buildForcingVector(
        Eigen::VectorXd& f, 
        const State& state
    );

    void integrator(
        State& state, 
        float dt
    );

    void posUpdate(State& state);
    
    void grapher(State& state);
}