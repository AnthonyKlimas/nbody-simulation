// Copyright 2024 <Anthony Klimas>
#include "CelestialBody.hpp"

namespace NB {

    CelestialBody::CelestialBody() {}

    CelestialBody::~CelestialBody() {}

    std::istream& operator>>(std::istream& input, CelestialBody& body) {
        input >> body.xpos >> body.ypos >> body.xvel >> body.yvel >> body.mass;
        std::string filename;
        input >> filename;
        body.texture.loadFromFile("nbody/" + filename);
        body.sprite.setTexture(body.texture);
        return input;
    }

    std::ostream& operator<<(std::ostream& output, const CelestialBody& body) {
        output << body.xpos << " " << body.ypos << " " <<
        body.xvel << " " << body.yvel << " " << body.mass;
        return output;
    }

    void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }

    void CelestialBody::updateVelocity(double ax, double ay, double dt) {
        // Update velocity based on acceleration and time step
        xvel += ax * dt;
        yvel += ay * dt;
    }

    void CelestialBody::updatePosition(double dt) {
        // Update position based on velocity and time step
        xpos += xvel * dt;
        ypos += yvel * dt;
        sprite.setPosition(xpos, ypos);
    }

}  // namespace NB

