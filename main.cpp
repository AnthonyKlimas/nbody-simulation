// Copyright 2024 <Anthony Klimas>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <T> <dt>" << std::endl;
        return 1;
    }

    // Parse command-line arguments for T and dt
    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation");

    // Create Universe object
    NB::Universe universe;

    // Load textures for celestial bodies
    if (!universe.loadTexturesFromFolder("./nbody/")) {
        std::cerr << "Error: Failed to load textures." << std::endl;
        return 1;
    }

    // Read universe data from standard input
    if (!(std::cin >> universe)) {
        std::cerr << "Error: Failed to read data from input." << std::endl;
        return 1;
    }

    // Simulation loop
    double t = 0.0;
    while (t < T && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Simulate the universe for time step dt
        universe.step(dt);
        t += dt;

        // Clear the window, draw celestial bodies, and display
        window.clear();
        universe.draw(window);
        window.display();
    }

    // Output the final state of the universe in the same format as input
    std::cout << universe;

    return 0;
}






