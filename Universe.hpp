// Copyright 2024 <Anthony Klimas>
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "CelestialBody.hpp"

namespace NB {

class Universe {
private:
    std::vector<CelestialBody> bodies;
    std::map<std::string, sf::Texture> textures;
    double radius;

public:
    Universe();
    ~Universe();
    friend std::istream& operator>>(std::istream& input, Universe& universe);
    friend std::ostream& operator<<(std::ostream& output, const Universe& universe);
    void draw(sf::RenderWindow& window);
    std::vector<CelestialBody>& getCelestialBodies() { return bodies; }
    bool loadTexturesFromFolder(const std::string& folderPath);
    void step(double dt); // Method to update positions based on velocities and accelerations
};

} // namespace NB

#endif



