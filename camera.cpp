/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov

#include <Windows.h>
#include <GL\glut.h>
#include <cmath>

#include "camera.h"


// Camera system have to be controlled like a spaceship :)
// so the keyboard would manipulate roll and direction and move around
// so it will be represented with 4 vectors
// up, forward, and right vector to represent orientation on all axes
// and a position vector to represent the translation


Camera::Camera(void)
{
	_cameraMoveSpeed = 0.005f;
	_cameraTurnSpeed = 0.01f;

	// set default vector values - obtained a nice viewing angle of the planets, got values using the debugger
	/*
	forwardVector	0x00ab354c {-0.398769796, 0.763009906, -0.508720219}	float[3]
	upVector		0x00ab3564 {-0.235630989, 0.450859368, 0.860931039}		float[3]
	rightVector		0x00ab3558 {0.886262059, 0.463184059, 0.000000000}		float[3]
	position		0x00ab3570 {0.764331460, -1.66760659, 0.642456770}		float[3]
	*/
	vectorSet(_position, 0.764331460f, -1.66760659f, 0.642456770f);
	vectorSet(_forwardVector, -0.398769796f, 0.763009906f, -0.508720219f);
	vectorSet(_rightVector, 0.886262059f, 0.463184059f, 0.000000000f);
	vectorSet(_upVector, -0.235630989f, 0.450859368f, 0.860931039f);
}


// Service vector functions for help

// Sets vector to (x,y,z)
void Camera::vectorSet(float* v, float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

// Adds v2 to v1
void Camera::vectorAdd(float* v1, float* v2)
{
	v1[0] += v2[0];
	v1[1] += v2[1];
	v1[2] += v2[2];
}

// Copies v2 into v1
void Camera::vectorCopy(float* v1, float* v2)
{
	v1[0] = v2[0];
	v1[1] = v2[1];
	v1[2] = v2[2];
}

// Multiplies vectors by the scalar
void Camera::vectorMultiple(float* v, float scalar)
{
	v[0] *= scalar;
	v[1] *= scalar;
	v[2] *= scalar;
}

// Finds the magnitude of a vector
float Camera::lengthOfVector(float* v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// Normalizes a vector to magnitude 1
void Camera::normaliseVector(float* v)
{
	vectorMultiple(v, 1 / lengthOfVector(v));
}

// Makes a 3x3 rotation matrix from the given angle and axis and pointer to a 3x3 matrix
void Camera::rotationMatrix(float* matrix, float* axis, float angle)
{
	float cos1 = cos(angle);
	float cos2 = 1 - cos1;
	float sin1 = sin(angle);

	matrix[0] = cos1 + axis[0] * axis[0] * cos2;
	matrix[1] = axis[0] * axis[1] * cos2 - axis[2] * sin1;
	matrix[2] = axis[0] * axis[2] * cos2 + axis[1] * sin1;

	matrix[3] = axis[1] * axis[0] * cos2 + axis[2] * sin1;
	matrix[4] = cos1 + axis[1] * axis[1] * cos2;
	matrix[5] = axis[1] * axis[2] * cos2 - axis[0] * sin1;

	matrix[6] = axis[2] * axis[0] * cos2 - axis[1] * sin1;
	matrix[7] = axis[2] * axis[1] * cos2 + axis[0] * sin1;
	matrix[8] = cos1 + axis[2] * axis[2] * cos2;
}

// Multiplies a vector v1 by a matrix and puts the results into vector v2
void Camera::multipleVectorBy(float* v1, float* matrix, float* v2)
{
	v2[0] = v1[0] * matrix[0] + v1[1] * matrix[1] + v1[2] * matrix[2];
	v2[1] = v1[0] * matrix[3] + v1[1] * matrix[4] + v1[2] * matrix[5];
	v2[2] = v1[0] * matrix[6] + v1[1] * matrix[7] + v1[2] * matrix[8];
}

// Rotate a vector v1 around the axis v2 by angle and put the result into v3
void Camera::rotateAroundVector(float* v1, float* v2, float angle, float* v3)
{
	// Make a rotation matrix for it
	float matrix[16];
	rotationMatrix(matrix, v2, angle);

	// Multiply by the matrix
	multipleVectorBy(v1, matrix, v3);
}

// Service functions ends




// Transform the OpenGL view matrix for the camera
void Camera::transformOrientation(void)
{
	// Look in the direction of the orientation vectors
	gluLookAt(0, 0, 0, _forwardVector[0], _forwardVector[1], _forwardVector[2], _upVector[0], _upVector[1], _upVector[2]);
}

// Transform the OpenGL view matrix for the translation
void Camera::transformTranslation(void)
{
	// Translate to emulate camera position
	glTranslatef(-_position[0], -_position[1], -_position[2]);
}

// Points the camera at the given point in 3d space
void Camera::pointAt(float* targetVector)
{
	float tempVector[3];
	float up[3] = { 0.0f, 0.0f, 1.0f };

	// First work out the new forward vector by subtracting the target position from the camera position
	_forwardVector[0] = targetVector[0] - _position[0];
	_forwardVector[1] = targetVector[1] - _position[1];
	_forwardVector[2] = targetVector[2] - _position[2];

	// Then normalize it to 1 length
	normaliseVector(_forwardVector);

	// Now to find the right vector we rotate the forward vector -pi/2 around the z axis
	rotateAroundVector(_forwardVector, up, -1.57079632679f, tempVector);
	// and remove the y component to make it flat
	tempVector[2] = 0;
	// then normalize it
	normaliseVector(tempVector);
	// and assign it to rightVec
	vectorCopy(_rightVector, tempVector);

	// Now work out the up vector by rotating the forward vector pi/2 around the right vector
	rotateAroundVector(_forwardVector, _rightVector, 1.57079632679f, tempVector);
	vectorCopy(_upVector, tempVector);
}

// Speed up the camera speed
void Camera::speedUp(void)
{
	if (_cameraMoveSpeed < 1.0f)
		_cameraMoveSpeed *= 2;
}

// Slow down the camera speed
void Camera::speedDown(void)
{
	if (_cameraMoveSpeed > 0.000001f)
		_cameraMoveSpeed /= 2;
}

// Move the camera forward
void Camera::moveForward(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the forward direction
	vectorCopy(tempVector, _forwardVector);
	vectorMultiple(tempVector, _cameraMoveSpeed);

	// Add the movement tempVector to the position vector
	vectorAdd(_position, tempVector);
}

// Move the camera backward
void Camera::moveBackward(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the backward direction
	vectorCopy(tempVector, _forwardVector);
	vectorMultiple(tempVector, -_cameraMoveSpeed); // -cameraSpeed for backwards

	// Add the movement vector to the position vector
	vectorAdd(_position, tempVector);
}

// Slide the camera left
void Camera::slideLeft(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the left direction
	vectorCopy(tempVector, _rightVector);
	vectorMultiple(tempVector, -_cameraMoveSpeed); // -cameraSpeed for left

	// Add the movement vector to the position vector
	vectorAdd(_position, tempVector);
}

// Slide the camera right
void Camera::slideRight(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the right direction
	vectorCopy(tempVector, _rightVector);
	vectorMultiple(tempVector, _cameraMoveSpeed);

	// Add the movement vector to the position vector
	vectorAdd(_position, tempVector);
}

// Roll the camera to the right
void Camera::rollRight(void)
{
	float tempVector[3];

	// Rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVector(_upVector, _forwardVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_upVector, tempVector);

	rotateAroundVector(_rightVector, _forwardVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_rightVector, tempVector);
}

// Roll the camera to the left
void Camera::rollLeft(void)
{
	float tempVector[3];

	// Rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVector(_upVector, _forwardVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_upVector, tempVector);

	rotateAroundVector(_rightVector, _forwardVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_rightVector, tempVector);
}

// Pitch the camera up
void Camera::pitchUp(void)
{
	float tempVector[3];

	// Rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVector(_forwardVector, _rightVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_forwardVector, tempVector);

	rotateAroundVector(_upVector, _rightVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_upVector, tempVector);
}

// Pitch the camera down
void Camera::pitchDown(void)
{
	float tempVector[3];

	// Rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVector(_forwardVector, _rightVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_forwardVector, tempVector);

	rotateAroundVector(_upVector, _rightVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_upVector, tempVector);
}

// Yaw the camera left
void Camera::yawLeft(void)
{
	float tempVector[3];

	// Rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVector(_forwardVector, _upVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_forwardVector, tempVector);

	rotateAroundVector(_rightVector, _upVector, _cameraTurnSpeed, tempVector);
	vectorCopy(_rightVector, tempVector);
}

// Yaw the camera right
void Camera::yawRight(void)
{
	float tempVector[3];

	// Rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVector(_forwardVector, _upVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_forwardVector, tempVector);

	rotateAroundVector(_rightVector, _upVector, -_cameraTurnSpeed, tempVector);
	vectorCopy(_rightVector, tempVector);
}