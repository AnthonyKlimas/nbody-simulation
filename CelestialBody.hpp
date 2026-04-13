#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
private:
    double xpos, ypos, xvel, yvel, mass;
    std::string imageName;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    CelestialBody();
    ~CelestialBody();
    double getXPos() const { return xpos; }
    double getYPos() const { return ypos; }
    double getXVel() const { return xvel; }
    double getYVel() const { return yvel; }
    double getMass() const { return mass; }
    sf::Sprite& getSprite() { return sprite; }
    const sf::Sprite& getSprite() const { return sprite; }
    const std::string& getImageName() const { return imageName; }
    void setTexture(const sf::Texture& tex) { texture = tex; sprite.setTexture(texture); }
    void setVelocity(double vx, double vy) { xvel = vx; yvel = vy; }
    void setMass(double m) { mass = m; }
    void setPosition(double x, double y) { xpos = x; ypos = y; } // Added setPosition function
    void updateVelocity(double ax, double ay, double dt);
    void updatePosition(double dt);
    friend std::istream& operator>>(std::istream& input, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& output, const CelestialBody& body);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} // namespace NB

#endif // CELESTIALBODY_HPP



