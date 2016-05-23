#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Definitions for the planet class and for the Sun also. We will use planet class for the Sun.

//
// Sergey Safarov
// 

#include "satellite.h"

#include <Windows.h>
#include <vector>
#include <GL\glut.h>

class Planet
{
private:
	// Distance from the Sun
	float distanceFromSun;

	// Time it takes to complete full orbit path
	float orbitTime;

	// Time it takes to spin 360 degrees
	float rotationTime;

	// Radius of the planet itself
	float radius;

	// The texture used for rendering
	GLuint textureHandle;

	// Its position in 3D space
	float position[3];

	// Its rotation angle around its axis
	float rotation;

	// List of satellites attached to this planet
	std::vector<Satellite> satellites;

public:
	// Distance is in units of km (kilometers) and time is in units of earth days (365.25 orbit time for earth)
	Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Calculate its position in 3D space in the orbit using the given time value
	void calculatePosition(float time);

	// Render it to the screen
	void render(void);

	// Render this planets orbit circle
	void renderOrbit(void);

	// Get its position in 3D world space units (after scaling) and put it into the 3D vector
	void getPosition(float* vec);

	// Get the radius of the current planet
	float getRadius(void);

	// Add a satellite to the current planet
	void addSatellite(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
};