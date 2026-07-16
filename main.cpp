// Copyright 2024 <Anthony Klimas>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Universe.hpp"

using namespace std;
using namespace sf;

int main() {

    //Set the gravity to a specific number
    const double dt = 25000;
	
    // Create SFML window
    RenderWindow window(VideoMode(800, 600), "N-Body Simulation");

    // Create Universe object
    NB::Universe universe;

    // Load textures for celestial bodies
    if (!universe.loadTexturesFromFolder("./nbody/")) {
        cerr << "Error: Failed to load textures." << endl;
        return 1;
    }

    // Read universe data from standard input
    if (!(cin >> universe)) {
        cerr << "Error: Failed to read data from input." << endl;
        return 1;
    }

    // Simulation loop
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Simulate the universe for time step dt
        universe.step(dt);

        // Clear the window, draw celestial bodies, and display
        window.clear();
        universe.draw(window);
        window.display();
	sf::sleep(sf::milliseconds(16));
    }

    // Output the final state of the universe in the same format as input
    std::cout << universe;

    return 0;
}






