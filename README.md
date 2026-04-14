# N-Body Simulation

A physics-based simulation that models the motion of celestial bodies under gravitational forces using Newtonian mechanics. The program visualizes planetary motion in real-time using SFML.

---

## Overview

This project simulates a system of celestial bodies interacting through gravity. Each body’s position and velocity are updated over time based on the net gravitational forces from all other bodies.

The simulation reads initial conditions from an input file and renders the system dynamically.

---

## Features

- Object-oriented design using `Universe` and `CelestialBody` classes  
- Real-time graphical rendering with SFML  
- Physics-based simulation using Newton’s Law of Gravitation  
- File I/O for loading simulation data  
- Smooth animation with controlled frame timing  

---

## 🛠️ Technologies

- C++  
- SFML 
- Object-Oriented Programming (OOP)  
- File I/O and data parsing  

---

## How to Run
make

./NBody 157788000.0 25000.0 < nbody/(text_file_name)
