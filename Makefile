CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Werror -g
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: NBody

NBody: main.cpp Universe.o CelestialBody.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f NBody *.o
