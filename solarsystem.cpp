/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

// v.1 Solar system
// This is the first version of the system.
// Simple circle orbits, no gravity forces.

#include "solarsystem.h"

//Class constructor
SolarSystem::SolarSystem()
{

}

// Add a planet with the given data
void SolarSystem::addPlanet(float mass, float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets.push_back(Planet(mass, distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

// Add a satellite to the specified planet
void SolarSystem::addSatellite(int planetIndex, float mass, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	planets[planetIndex].addSatellite(mass, distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

// Get the position in 3D space units of the given planet (specified by its index in the list) and put it into the 3D vector
void SolarSystem::getPlanetPosition(int index, float *vector)
{
	planets[index].getPosition(vector);
}

// Get planet object data. 
Planet SolarSystem::getPlanet(int index)
{
	//@todo Need to add presence checks here
	return planets[index];
}


// Calculate the positions according the accepted logic for all planets
void SolarSystem::calculatePositions(float time)
{
	int count = planets.size();
	for (int i = 0; i < count; i++)
	{
		planets[i].calculatePosition(time);
	}
}

// Render the orbits of the planets and satellites
void SolarSystem::renderOrbits()
{
	int count = planets.size();
	for (int i = 0; i < count; i++)
	{
		planets[i].renderOrbit();
	}
}

// Render the solar system using OpenGL
void SolarSystem::render()
{
	int count = planets.size();
	for (int i = 0; i < count; i++)
	{
		planets[i].render();
	}
}

