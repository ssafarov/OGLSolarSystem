/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov
//
// Satellite methods and properties

#include "satellite.h"

Satellite::Satellite(float mass, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->mass = mass;
	this->distanceFromPlanet = distanceFromPlanet;
	this->orbitTime = orbitTime;
	this->rotationTime = rotationTime;
	this->radius = radius;
	this->textureHandle = textureHandle;
}

// Calculate its position in 3D space relative to the planet in the orbit using the given time value.
//TODO Add Gravity in the next release
// Only for the first iteration. No Gravity in this version
void Satellite::calculatePosition(float time)
{
	// find the angle of orientation of the orbit around the planet
	float angle = time * PI / orbitTime;

	// use simple trigonometry to find the position in space relative to the planet.
	position[0] = sin(angle) * distanceFromPlanet;	//X
	position[1] = cos(angle) * distanceFromPlanet;	//Y
	position[2] = 0;								//Z // In this version all planets and satellites will be in one plane

	// find the rotation angle of the satellite around its axis
	rotation = time * 360 / rotationTime;
}

// get the radius of this satellite
float Satellite::getRadius(void)
{
	return radius;
}

// get the mass of this satellite
float Satellite::getMass(void)
{
	return mass;
}

// get the velocity of this satellite
float Satellite::getVelocity(void)
{
	return velocity;
}

// get the acceleration of this satellite
float Satellite::getAcceleration(void)
{
	return acceleration;
}


// Render it to the screen
void Satellite::render(void)
{
	glPushMatrix();

	// bind the moons texture
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// translate to the right position and rotate for the moons spinning
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	glRotatef(-rotation, 0.0f, 0.0f, 1.0f);

	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);

	GLfloat matAmbience[] = { 0.1f, 0.1f, 0.1f, 0.1f };
	GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat matEmission[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat matShininess[] = { 7.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	gluSphere(quadric, radius * planetSizeScale, 64, 64);

	glPopMatrix();
}

// render this planets orbit circle
void Satellite::renderOrbit(void)
{
	glColor3f(0.3f, 0.3f, 0.3f);

	// draw a line strip
	glBegin(GL_LINE_STRIP);

	// loop round from 0 to double PI and draw around the radius of the orbit using trigonometry
	for (float angle = 0.0f; angle < doublePI; angle += 0.01f)
	{
		glVertex3f(sin(angle) * distanceFromPlanet * distanceScale, cos(angle) * distanceFromPlanet * distanceScale, 0.0f);
	}

	glVertex3f(0.0f, distanceFromPlanet * distanceScale, 0.0f);

	glEnd();
}