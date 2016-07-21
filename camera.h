#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Definitions of the Camera/View port class methods and properties

//
// Sergey Safarov
//
#include <Windows.h>
#include "Libraries\glew\GL\glew.h"
#include "Libraries\freeglut\GL\freeglut.h"
#include "globals.h"
#include <cmath>
#include <string>

class Camera
{
private:

	// A default vector pointing in the direction you are facing (Z Axis)
	float forwardDefaultVector[3];

	// A default vector pointing to the right of where your facing (to describe orientation) (X axis)
	float rightDefaultVector[3];

	// A default vector pointing upwards from where you are facing (Y axis)
	float upDefaultVector[3];

	// The default camera position point
	float positionDefault[3];


	// Service vector functions for help
	void vectorSet(float* v, float x, float y, float z);		// Sets vector to (x,y,z)
	void vectorAdd(float* v1, float* v2);						// Adds v2 to v1
	void vectorCopy(float* v1, float* v2);						// Copies v2 into v1
	void vectorMultiple(float* v, float scalar);				// Multiplies vectors by the scalar
	float lengthOfVector(float* v);								// Finds the magnitude of a vector
	void normaliseVector(float* v);								// Normalizes a vector to magnitude 1
	void rotationMatrix(float* matrix, float* axis, float angle);	// Makes a 3x3 rotation matrix from the given angle and axis and pointer to a 3x3 matrix
	void multipleVectorBy(float* v1, float* matrix, float* v2);		// Multiplies a vector v1 by a matrix and puts the results into vector v2
	void rotateAroundVector(float* v1, float* v2, float angle, float* v3);	// Rotate a vector v1 around the axis v2 by angle and put the result into v3

public:
	Camera(void);

	// A vector pointing in the direction you are facing (Z Axis)
	float forwardVector[3];

	// A vector pointing to the right of where your facing (to describe orientation) (X axis)
	float rightVector[3];

	// A vector pointing upwards from where you are facing (Y axis)
	float upVector[3];

	// The camera position point
	float position[3];

	// The camera speeds
	float cameraMoveSpeed;
	float cameraTurnSpeed;

	// Reset position and orientation to default
	void reset(void);

	// Transform the OpenGL view matrix for the orientation
	void transformOrientation(void);

	// Transform the OpenGL view matrix for the translation
	void transformTranslation(void);

	// Points the camera at the given point in 3d space
	void pointAt(float *targetVector);

	// Speed up the camera
	void speedUp(void);

	// Speed down the camera
	void speedDown(void);

	// Move the camera forward
	void moveForward(void);

	// Strafe the camera left
	void slideLeft(void);

	// Strafe the camera right
	void slideRight(void);

	// Move the camera backward
	void moveBackward(void);

	// Roll the camera to the right
	void rollRight(void);

	// Roll the camera to the left
	void rollLeft(void);

	// Pitch the camera up
	void pitchUp(void);

	// Pitch the camera down
	void pitchDown(void);

	// Yaw the camera left
	void yawLeft(void);

	// Yaw the camera right
	void yawRight(void);

};
