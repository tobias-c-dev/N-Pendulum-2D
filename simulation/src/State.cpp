#include "State.hpp"
#include "Constants.hpp"
#include "MathUtils.hpp"
#include <cmath>


// State functions
void State::createRods() {

    rods.clear();
    rods.resize(N);

}

void State::update(double dt) {

    MathUtils::integrator(*this, dt);
    MathUtils::posUpdate(*this);
    
    MathUtils::energyCalculator(*this);

}
