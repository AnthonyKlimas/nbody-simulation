// Copyright 2024 <Anthony Klimas>
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <map>
#include "CelestialBody.hpp"


//Create a Namespace named NB for naming conflicts with other classes
namespace NB {

//Declares a class called Universe so you can create objects
class Universe {
	//Define private specifier, everything below it can only be accessed within the class
	private:
		//Initalize a vector that holds the elements of celestial bodies
    		std::vector<CelestialBody> bodies;
    		
    		//Initalize a map named textures that holds a filename with a texture
    		std::map<std::string, sf::Texture> textures;
    		
    		//Create a double named radius
    		double radius;

	//Define a public specifier, everything below it can be accessed by other classes and functions
	public:
  
  		//Declares an input overload operator, so you can write with >>.
  		//Since its declared as a friend it can access the class's private members
    		friend std::istream& operator>>(std::istream& input, Universe& universe);
    
    		//Declates an output overload operator, so you can write with <<
    		//Since its declated as a friend it can access the class's private members
    		friend std::ostream& operator<<(std::ostream& output, const Universe& universe);
    
    		//Declares a member function named draw
    		void draw(sf::RenderWindow& window);
    
    		std::vector<CelestialBody>& getCelestialBodies() 
    		{ 
    		
    		return bodies; 
    		
    		}
    
    		bool loadTexturesFromFolder(const std::string& folderPath);
    
    		void step(double dt); // Method to update positions based on velocities and accelerations
		};

	} // namespace NB

#endif



