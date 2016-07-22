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

class Camera
{
private:

	// A default vector pointing in the direction you are facing
	float forwardDefaultVector[3];

	// A default vector pointing to the right of where your facing (to describe orientation)
	float rightDefaultVector[3];

	// A default vector pointing upwards from where you are facing
	float upDefaultVector[3];

	// The default camera position point
	float positionDefault[3];

	// Service functions begin 
	void vectorSet(float* v, float x, float y, float z);
	void vectorAdd(float* v1, float* v2);
	void vectorCopy(float* v1, float* v2);
	void vectorMultiple(float* v, float scalar);
	float lengthOfVector(float* v);
	void normaliseVector(float* v);
	void rotationMatrix(float* matrix, float* axis, float angle);
	void multipleVectorBy(float* v1, float* matrix, float* v2);
	void rotateAroundVector(float* v1, float* v2, float angle, float* v3);
	// Service functions end
public:
	Camera(void);

	// A vector pointing in the direction you are facing
	float forwardVector[3];

	// A vector pointing to the right of where your facing (to describe orientation)
	float rightVector[3];

	// A vector pointing upwards from where you are facing
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
