#pragma once
#include <vector>
#include <Eigen/Dense>
#include "State.hpp"
#include "Constants.hpp"

struct Derivative {

        Eigen::VectorXd dTheta;
        Eigen::VectorXd dOmega;

};

namespace MathUtils {

    Derivative evaluate(State& state);
    void buildMassMatrix(Eigen::MatrixXd& M, State& state);
    void buildForcingVector(Eigen::VectorXd& f, State& state);
    void integrator(State& state, Eigen::MatrixXd& M, Eigen::VectorXd& f, float dt);
    void posUpdate(State& state);
}