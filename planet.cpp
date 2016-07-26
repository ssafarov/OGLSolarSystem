/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Definitions for the all planet objects class in the system.

//
// Sergey Safarov
// 

#include "planet.h"

Planet::Planet(float mass, float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	this->mass = mass;
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

	// rotate for the planet's spin
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	// bind the planets texture
	glBindTexture(GL_TEXTURE_2D, textureHandle);

	// render as a GLU sphere quadric object
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricTexture(quadric, true);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	float radiusScaled = radius * planetSizeScale;
	if (distanceFromSun == 0.0f) // if this is the sun
	{
		if (radiusScaled > 0.5f) radiusScaled = 0.5f;

		glDisable(GL_LIGHT1);

		GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat lightSpecular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
		GLfloat lightPosition[] = { position[0],position[1],position[2], 1.0f };

		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

		glEnable(GL_LIGHT1);

		GLfloat matAmbience[] = { 0.1f, 0.1f, 0.1f, 0.1f };
		GLfloat matDiffuse[] = { 0.9f, 0.9f, 0.9f, 0.9f };
		GLfloat matEmission[] = { 1.0f, 0.9f, 0.9f, 0.0f };
		GLfloat matShininess[] = { 100.0 };

		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	}
	else
	{
		GLfloat matAmbience[] = { 0.1f, 0.1f, 0.1f, 0.1f };
		GLfloat matDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat matEmission[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		GLfloat matShininess[] = { 100.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
		glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	}


	gluSphere(quadric, radiusScaled, 128, 128);

	glPopMatrix();


}

// render this planets orbit circle
void Planet::renderOrbit(void)
{
	glColor3f(0.7f, 0.7f, 0.7f);
	glDisable(GL_TEXTURE_2D);
	// draw a line strip
	glBegin(GL_LINE_STRIP);

	// loop round from 0 to 2*PI and draw around the radius of the orbit using trigonometry
	for (float angle = 0.0f; angle < doublePI; angle += 0.01f)
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
	glEnable(GL_TEXTURE_2D);
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

// get the mass of this planet
float Planet::getMass(void)
{
	return mass;
}

// get the velocity of this planet
float Planet::getVelocity(void)
{
	return velocity;
}

// get the acceleration of this planet
float Planet::getAcceleration(void)
{
	return acceleration;
}

// add a moon to this planet
void Planet::addSatellite(float mass, float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
	satellites.push_back(Satellite(mass, distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}

// Get satellite object data
Satellite Planet::getSatellite(int index)
{
	//@todo add some checks here
	return satellites[index];
}