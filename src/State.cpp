#include "State.hpp"
#include "Constants.hpp"
#include "MathUtils.hpp"
#include <cmath>

// Rod functions
Vector2 Rod::centreOfMass(int rod_index, const std::vector<double>& theta, const std::vector<float>& length) {
    
    float x = 0.0f;
    float y = 0.0f;
    
    for (int i=0; i<rod_index; i++) {

        x += length[i] * sinf(theta[i]);
        y += length[i] * cosf(theta[i]);

    };

    x += 0.5 * length[rod_index] * sinf(theta[rod_index]);
    y += 0.5 * length[rod_index] * cosf(theta[rod_index]);

    return {x, -y};
}



// State functions
void State::createRods() {

    rods.clear();
    rods.reserve(N);

    for (int i=0; i<N; i++) {

        Rod rod;
        rod.length = length[i];
        rod.radius = radius[i];
        rod.mass = mass[i];
        rod.colour = Constants::COLOUR;

        rods.push_back(rod);
    }
}

void State::update(float dt) {

    Eigen::MatrixXd M(N, N);
    Eigen::VectorXd f(N);

    MathUtils::buildMassMatrix(M, *this);
    MathUtils::buildForcingVector(f, *this);
    MathUtils::integrator(*this, M, f, dt);
    MathUtils::posUpdate(*this);

}
