#include <iostream>
#include <sstream>
#include <cassert>
#include "Universe.hpp"
#include "CelestialBody.hpp"

void testLoadingCelestialBodies() {
    NB::Universe universe;
    std::stringstream input("2 10.0\n1.0 2.0 3.0 4.0 5.0 earth.gif\n6.0 7.0 8.0 9.0 10.0 mars.gif");
    input >> universe;

    const std::vector<NB::CelestialBody>& bodies = universe.getCelestialBodies();
    assert(bodies.size() == 2);

    assert(bodies[0].getXPos() == 1.0);
    assert(bodies[0].getYPos() == 2.0);
}

void testLoadingTextures() {
    NB::Universe universe;
    universe.loadTexturesFromFolder("nbody/");

    for (const NB::CelestialBody& body : universe.getCelestialBodies()) {
        assert(body.getSprite().getTexture() != nullptr);
    }
}

void testStepMethod() {
    // Create a Universe with a single CelestialBody
    NB::Universe universe;
    NB::CelestialBody body;
    body.setPosition(0.0, 0.0); // Initial position
    body.setVelocity(1.0, 1.0); // Initial velocity
    body.setMass(10.0); // Set mass
    universe.getCelestialBodies().push_back(body);

    // Perform one time step with dt = 1.0
    universe.step(1.0);

    // Check if the position of the CelestialBody has been updated correctly
    const NB::CelestialBody& updatedBody = universe.getCelestialBodies()[0];
    assert(updatedBody.getXPos() == 1.0);
    assert(updatedBody.getYPos() == 1.0);
}

void testVelocityUpdate() {
    // Create a Universe with a single CelestialBody
    NB::Universe universe;
    NB::CelestialBody body;
    body.setPosition(0.0, 0.0); // Initial position
    body.setVelocity(1.0, 1.0); // Initial velocity
    body.setMass(10.0); // Set mass
    universe.getCelestialBodies().push_back(body);

    // Perform one time step with dt = 1.0
    universe.step(1.0);

    // Check if the velocity of the CelestialBody has been updated correctly
    const NB::CelestialBody& updatedBody = universe.getCelestialBodies()[0];
    assert(updatedBody.getXVel() == 1.0); // Velocity should remain the same if no external forces act
    assert(updatedBody.getYVel() == 1.0);
}

int main() {
    std::cout << "Running tests...\n";
    testLoadingCelestialBodies();
    testLoadingTextures();
    testStepMethod();
    testVelocityUpdate();
    std::cout << "All tests passed!\n";
    return 0;
}



