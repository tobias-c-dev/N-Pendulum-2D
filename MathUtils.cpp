#include <cmath>
#include "MathUtils.hpp"

// Derivative evaluator to help with RK4
Derivative MathUtils::evaluate(State& state) {
    Eigen::MatrixXd M(state.N, state.N);
    Eigen::VectorXd f(state.N);
    buildMassMatrix(M, state);
    buildForcingVector(f, state);

    Derivative d;
    d.dTheta = Eigen::VectorXd::Map(state.omega.data(), state.N);
    d.dOmega = M.colPivHouseholderQr().solve(f);
    return d;
}


// Creates mass matrix from euler-lagrange equations
void MathUtils::buildMassMatrix(Eigen::MatrixXd& M, State& state) {
    
    int N = state.N;
    M.setZero();

    for (int j=0; j<N; j++) {
        for (int k=0; k<N; k++) {
            double sum = 0.0;
            for (int i=std::max(j,k); i<N; i++) {
                double c_ij = (j < i) ? state.length[j] : 0.5 * state.length[i];
                double c_ik = (k < i) ? state.length[k] : 0.5 * state.length[i];
                sum += state.mass[i] * c_ij * c_ik * cos(state.theta[j] - state.theta[k]);
            }
            if (j == k) {
                double I_i = (1.0/12.0) * state.mass[j] * state.length[j] * state.length[j];
                sum += I_i;
            }
            M(j,k) = sum;
        }
    }
}


// Creates forcing vector from euler-lagrange equations
void MathUtils::buildForcingVector(Eigen::VectorXd& f, State& state) {
    
    int N = state.N;
    f.setZero();

    for (int j=0; j<N; j++) {
        // Gravity Calculation
        double gravity = 0.0;
        for (int i=j; i<N; i++) {
            double c_ij = (j < i) ? state.length[j] : 0.5 * state.length[i];
            gravity -= state.mass[i] * Constants::GRAVITY * c_ij * sin(state.theta[j]);
        }
        // Coriolis Calculation
        double dynamic = 0.0;
        for (int k=0; k<N; k++) {
            if (k == j) continue;
            double sum = 0.0;
            for (int i = std::max(j,k); i<N; i++) {
                double c_ij = (j < i) ? state.length[j] : 0.5 * state.length[i];
                double c_ik = (k < i) ? state.length[k] : 0.5 * state.length[i];
                sum += state.mass[i] * c_ij * c_ik * sin(state.theta[j] - state.theta[k]);
            }
            dynamic -= sum * state.omega[k] * state.omega[k];
        }
        // Aerodynamic Drag Torque Calculation
        double L = state.length[j];
        double omega_j = state.omega[j];
        double radius_j = state.radius[j];
        double drag_torque = (-0.125 * Constants::ATMOSPHERIC_DENSITY * 
                                Constants::DRAG_COEFFICIENT * state.radius[j] * (L * L * L * L) *
                                omega_j * std::abs(omega_j));
        f(j) = gravity + dynamic + drag_torque;
    }
}


// RK4 integration, will return angle values

void MathUtils::integrator(State& state, Eigen::MatrixXd& M, Eigen::VectorXd& f, float dt) {

    int N = state.N;

    // original state
    std::vector<double> theta0 = state.theta;
    std::vector<double> omega0 = state.omega;

    // k1 - derivative at start
    Derivative k1 = evaluate(state);

    // k2 - derivative at midpoint using k1
    for (int i=0; i<N; i++) {
        state.theta[i] = theta0[i] + 0.5*dt*k1.dTheta(i);
        state.omega[i] = omega0[i] + 0.5*dt*k1.dOmega(i);
    }
    Derivative k2 = evaluate(state);

    // k3 - derivative at midpoint using k2
    for (int i=0; i<N; i++) {
        state.theta[i] = theta0[i] + 0.5*dt*k2.dTheta(i);
        state.omega[i] = omega0[i] + 0.5*dt*k2.dOmega(i);
    }
    Derivative k3 = evaluate(state);

    // k4 - derivative at end using k3
    for (int i=0; i<N; i++) {
        state.theta[i] = theta0[i] + dt*k3.dTheta(i);
        state.omega[i] = omega0[i] + dt*k3.dOmega(i);
    }
    Derivative k4 = evaluate(state);

    // weighted average
    for (int i=0; i<N; i++) {
        state.theta[i] = theta0[i] + (dt/6.0) * (k1.dTheta(i) + 2*k2.dTheta(i) + 2*k3.dTheta(i) + k4.dTheta(i));
        state.omega[i] = omega0[i] + (dt/6.0) * (k1.dOmega(i) + 2*k2.dOmega(i) + 2*k3.dOmega(i) + k4.dOmega(i));
    }
}


// Updates position of each rod

void MathUtils::posUpdate(State& state) {
    Vector2 prev = state.anchor;

    for (int i=0; i < state.N; i++) {
        state.rods[i].start = prev;

        Vector2 end = {
            prev.x + state.length[i] * Constants::PPM * sinf(state.theta[i]),
            prev.y + state.length[i] * Constants::PPM * cosf(state.theta[i])
        };
    
        state.rods[i].end = end;
        state.rods[i].currentTheta = state.theta[i];
        prev = end;
    }
}
