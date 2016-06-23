/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Definitions for the all planet objects class in the system.

//
// Sergey Safarov
// 

#include "globals.h"
#include "planet.h"

#include <cmath>
#include <Windows.h>
#include <GL\glut.h>

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->distanceFromSun = distanceFromSun;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

// Calculate its position in 3D space in the orbit using the given time value
//TODO Add Gravity in the next release
// Only for the first iteration. No Gravity in this version
void Planet::calculatePosition(float time)
{
	// find the angle of orientation of the orbit around the sun
	float angle = time * PI / orbitTime;

	// use trigonometry to find the position in space
	position[0] = sin(angle) * distanceFromSun;	//X
	position[1] = cos(angle) * distanceFromSun;	//Y
	position[2] = 0;							//Z // In this version all planets and satellites will be in one plane

	// find the rotation of the planet around its axis
	rotation = time * 360 / rotationTime;

	// calculate positions of satellites
	int count = satellites.size();
	for (int i = 0; i < count; i++)
	{
		satellites[i].calculatePosition(time);
	}
}

// Render it to the screen
void Planet::render(void)
{
	glPushMatrix();

	// translate to the right position
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

	// Draw the satellites
	int count = satellites.size();
	for (int i = 0; i < count; i++)
	{
		satellites[i].render();
	}

	/// rotate for the planet's spin
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	// bind the planets texture
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	float radiusScaled = radius * planetSizeScale;
	if (distanceFromSun == 0.0f) // if this is the sun, don't render it too big, and disable lighting
	{
		if (radiusScaled > 0.5f) radiusScaled = 0.5f;

		glDisable(GL_LIGHTING);
		gluSphere(quadric, radiusScaled, 128, 128);
		glEnable(GL_LIGHTING);
	}
	else
	{
		gluSphere(quadric, radiusScaled, 128, 128);
	}

	glPopMatrix();
}

// render this planets orbit circle
void Planet::renderOrbit(void)
{
	// draw a line strip
	glBegin(GL_LINE_STRIP);

	// loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
	for (float angle = 0.0f; angle < doublePI; angle += 0.05f)
	{
		glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale, 0.0f);
	}
	glVertex3f(0.0f, distanceFromSun * distanceScale, 0.0f);

	glEnd();

	// render the satellites' orbit
	glPushMatrix();
	// translate to the center of this planet to draw the moon orbit around it
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	// draw all moon orbits
	int count = satellites.size();
	for (int i = 0; i < count; i++)
	{
		satellites[i].renderOrbit();
	}
	glPopMatrix();

}


// Get its position in 3d world space units (after scaling) and put it into the 3d vector
void Planet::getPosition(float* vec)
{
	vec[0] = position[0] * distanceScale;
	vec[1] = position[1] * distanceScale;
	vec[2] = position[2] * distanceScale;
}

// get the radius of this planet
float Planet::getRadius(void)
{
	return radius;
}

// add a moon to this planet
void Planet::addSatellite(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	satellites.push_back(Satellite(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}