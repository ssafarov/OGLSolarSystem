#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

// v.1 Solar system
// This is the first version of the system.
// Simple circle orbits, no gravity forces.



#include <Windows.h>
#include <vector>

#include "Libraries\glew\GL\glew.h"
#include "Libraries\freeglut\GL\freeglut.h"

#include "planet.h"

// Class for Solar system logic 
class SolarSystem
{
private:
	std::vector<Planet> planets;

public:
	SolarSystem();

	// Add a planet with the given data
	void addPlanet(float mass, float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Add a satellite to the specified planet
	void addSatellite(int planetIndex, float mass, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Get the position in 3D space units of the given planet (specified by its index in the list) and put it into the 3D vector
	void getPlanetPosition(int index, float *vector);

	Planet getPlanet(int index);

	// Calculate the positions according the accepted logic for all planets
	void calculatePositions(float time);

	// Render the orbits of the planets and satellites
	void renderOrbits();

	// Render the solar system using OpenGL
	void render();

};