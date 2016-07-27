#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov
// 
// Definitions for the satellite class in the system.

#include "globals.h"
#include <Windows.h>
#include "Libraries\glew\GL\glew.h"
#include "Libraries\freeglut\GL\freeglut.h"

#include <vector>
#include <cmath>


class Satellite
{
private:
	// Distance from its planet
	float distanceFromPlanet;

	// Time it takes to complete full orbit path
	float orbitTime;

	// Time it takes to spin 360 degrees
	float rotationTime;

	// Radius of the satellite itself
	float radius;

	// Mass of the satellite itself
	float mass;

	// Velocity of the satellite itself
	float velocity;

	// Acceleration of the satellite itself
	float acceleration;

	// The texture used for rendering
	GLuint textureHandle;

	// Its position in 3D space relative to the planet
	float position[3];

	// Its rotation angle around its axis
	float rotation;

public:
	// Mass in kilograms, distance is in units of km (kilometers) and time is in units of earth days
	Satellite(float mass, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

	// Calculate its position in 3D space relative to the planet in the orbit using the given time value
	void calculatePosition(float time);

	// Get the radius of the current satellite
	float getRadius(void);

	// get the mass of this satellite
	float getMass(void);

	// get the velocity of this satellite
	float getVelocity(void);

	// get the acceleration of this satellite
	float getAcceleration(void);

	// Render it to the screen
	void render(void);

	// Render this satellite orbit path
	void renderOrbit(void);
};