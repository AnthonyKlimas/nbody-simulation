// Copyright 2024 <Anthony Klimas>
#include "Universe.hpp"
#include <cmath>
#include <iostream>
#include <dirent.h>

//Create a constant for gravity
const double G = 6.67430e-11;

//Located in namespace NB
namespace NB {

    //Operator overloader to read the txt files and assign the data to variables
    std::istream& operator>>(std::istream& input, Universe& universe) 
    {
    	//Create variable named numBodies
        int numBodies;
        
        //Stores the input in the text files into the numBodies and universe.radius variables
        input >> numBodies;
        input >> universe.radius;
        
        //Resize the vector bodies of the number of planets needed for the simulation
        universe.bodies.resize(numBodies);
        
        //iterate through the bodies vector to find data for each body
        for (int i = 0; i < numBodies; ++i) 
        {
            input >> universe.bodies[i];
        }
        
        //returns the stream object
        return input;
    }

    //Function defintion for draw in the Universe class that returns a void
    void Universe::draw(sf::RenderWindow& window) 
    {
    	//Store a point that points to the middle of the window (400, 400)
        sf::Vector2f windowCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
        
        //Scale the coordinates for the simulation
        double scaleFactor = window.getSize().y / (2.0 * radius);

	//loop through every planet
        for (auto& body : bodies) 
        {
            //Where the earth should be drawn on the window (X position)
            double screenX = windowCenter.x + scaleFactor * body.getXPos();
            
            //Where the earth should be drawn on the window (Y position)
            double screenY = windowCenter.y - scaleFactor * body.getYPos();
            
            //Set the sprite postion on the screen to the coordiante positons we just caluclated
            body.getSprite().setPosition(screenX, screenY);
            
            //Draw the current planet
            window.draw(body);
        }
    }

    //Loads all planet images into memory
    bool Universe::loadTexturesFromFolder(const std::string& folderPath) 
    {
    //Create a pointer to a directory
    DIR *dir;
    
    //Create a dirent that represents one file in the directory
    struct dirent *ent;
    
    //Trys to open folder if it doesnt equal to null run the if statement if not run the else block
    if ((dir = opendir(folderPath.c_str())) != nullptr) 
    {
    
        // Iterate over each file in the directory
        while ((ent = readdir(dir)) != nullptr) 
        {
            //Create a string then equal it to the file name ent is pointing too
            std::string filename = ent->d_name;
            
            // Check if the file ends with .png
            if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".png") 
            {
                // Load texture from file and store it in a map with filename as key
                sf::Texture texture;
                
                //Read the file name and store it in memory
                if (!texture.loadFromFile("nbody/" + filename)) 
                {
                    //If file returns false return error message
                    std::cerr << "Error: Failed to load texture from file " << folderPath + filename << std::endl;
                    //Close the directory
                    closedir(dir);
                    
                    //return false
                    return false;
                    
                }
                
                textures[filename] = texture;
            }
        }
        
        //Close the directory
        closedir(dir);
        
        //Return true
        return true;
        
    } else 
    {
        // Unable to open directory
        std::cerr << "Error: Unable to open directory " << folderPath << std::endl;
        
        //Return false
        return false;
    }
}

   //Function that gives every planent a new velocity and new position based on gravity
    void Universe::step(double dt) 
    {
    
        // Update positions of celestial bodies based on their velocities and accelerations
        for (size_t i = 0; i < bodies.size(); ++i) 
        {
            double ax = 0.0;
            double ay = 0.0;

            // Calculate gravitational forces acting on the current body
            for (size_t j = 0; j < bodies.size(); ++j) 
            {
                if (i != j) 
                {
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



