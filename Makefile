CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Werror -g
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TEST_LIBS = -pthread

all: NBody NBody.a lint test

NBody: main.cpp Universe.o CelestialBody.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CXX) $(CXXFLAGS) -c $<

NBody.a: Universe.o CelestialBody.o
	ar rcs $@ $^

lint:
	
test: test.cpp Universe.o CelestialBody.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS) $(TEST_LIBS)

clean:
	rm -f NBody NBody.a *.o test

