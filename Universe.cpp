// Copyright 2024 <Anthony Klimas>
#include "Universe.hpp"
#include <cmath>
#include <iostream>
#include <dirent.h>

const double G = 6.67430e-11;

namespace NB {

    Universe::Universe() {}

    Universe::~Universe() {}

    std::istream& operator>>(std::istream& input, Universe& universe) {
        int numBodies;
        input >> numBodies >> universe.radius;
        universe.bodies.resize(numBodies);
        for (int i = 0; i < numBodies; ++i) {
            input >> universe.bodies[i];
        }
        return input;
    }

    std::ostream& operator<<(std::ostream& output, const Universe& universe) {
        output << universe.bodies.size() << " " << universe.radius << std::endl;
        for (const auto& body : universe.bodies) {
            output << body << std::endl;
        }
        return output;
    }

    void Universe::draw(sf::RenderWindow& window) {
        sf::Vector2f windowCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
        double scaleFactor = window.getSize().y / (2.0 * radius);

        for (auto& body : bodies) {
            double screenX = windowCenter.x + scaleFactor * body.getXPos();
            double screenY = windowCenter.y - scaleFactor * body.getYPos();
            body.getSprite().setPosition(screenX, screenY);
            window.draw(body);
        }
    }

    bool Universe::loadTexturesFromFolder(const std::string& folderPath) {
    // Open the directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folderPath.c_str())) != nullptr) {
        // Iterate over each file in the directory
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            // Check if the file ends with .png
            if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".png") {
                // Load texture from file and store it in a map with filename as key
                sf::Texture texture;
                if (!texture.loadFromFile("nbody/" + filename)) {
                    std::cerr << "Error: Failed to load texture from file " << folderPath + filename << std::endl;
                    closedir(dir);
                    return false;
                }
                textures[filename] = texture;
            }
        }
        closedir(dir);
        return true;
    } else {
        // Unable to open directory
        std::cerr << "Error: Unable to open directory " << folderPath << std::endl;
        return false;
    }
}


    void Universe::step(double dt) {
        // Update positions of celestial bodies based on their velocities and accelerations
        for (size_t i = 0; i < bodies.size(); ++i) {
            double ax = 0.0;
            double ay = 0.0;

            // Calculate gravitational forces acting on the current body
            for (size_t j = 0; j < bodies.size(); ++j) {
                if (i != j) {
                    // Calculate distance between bodies
                    double dx = bodies[j].getXPos() - bodies[i].getXPos();
                    double dy = bodies[j].getYPos() - bodies[i].getYPos();
                    double distanceSquared = dx * dx + dy * dy;
                    double distance = std::sqrt(distanceSquared);

                    // Calculate gravitational force magnitude
                    double forceMagnitude = G * bodies[i].getMass() * bodies[j].getMass() / distanceSquared;

                    // Calculate gravitational force components
                    double forceX = forceMagnitude * dx / distance;
                    double forceY = forceMagnitude * dy / distance;

                    // Accumulate forces acting on the current body
                    ax += forceX / bodies[i].getMass();
                    ay += forceY / bodies[i].getMass();
                }
            }

            // Update velocity based on acceleration
            bodies[i].updateVelocity(ax, ay, dt);

            // Update position based on velocity
            bodies[i].updatePosition(dt);
        }
    }

} // namespace NB



