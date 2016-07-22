/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Sergey Safarov


#include "camera.h"


// Camera system have to be controlled like a spaceship :)
// so the keyboard would manipulate roll and direction and move around
// so it will be represented with 4 vectors
// up, forward, and right vector to represent orientation on all axes
// and a position vector to represent the translation


Camera::Camera(void)
{
	cameraMoveSpeed = CMS;
	cameraTurnSpeed = CTS;

	// set default vector values - obtained a nice viewing angle of the planets, got values using the debugger
	vectorSet(positionDefault, -0.398769796f, -3.86760659f, 7.642456770f);
	vectorSet(forwardDefaultVector, -1.398769796f, 2.763009906f, -0.508720219f);
	vectorSet(rightDefaultVector, 0.886262059f, 0.463184059f, 0.000000000f);
	vectorSet(upDefaultVector, -0.235630989f, 0.450859368f, 0.860931039f);

	reset();

}


// Transform the OpenGL view matrix for the camera
void Camera::transformOrientation(void)
{
	// Look in the direction of the orientation vectors
	gluLookAt(0, 0, 0, forwardVector[0], forwardVector[1], forwardVector[2], upVector[0], upVector[1], upVector[2]);
}

// Transform the OpenGL view matrix for the translation
void Camera::transformTranslation(void)
{
	// Translate to emulate camera position
	glTranslatef(position[0], position[1], position[2]);
}

// Points the camera at the given point in 3d space
void Camera::pointAt(float* targetVector)
{
	float tempVector[3];
	float up[3] = { 0.0f, 0.0f, 1.0f };

	// First work out the new forward vector by subtracting the target position from the camera position
	forwardVector[0] = targetVector[0] - position[0];
	forwardVector[1] = targetVector[1] - position[1];
	forwardVector[2] = targetVector[2] - position[2];

	// Then normalize it to 1 length
	normaliseVector(forwardVector);

	// Now to find the right vector we rotate the forward vector -pi/2 around the z axis
	rotateAroundVector(forwardVector, up, -halfPI, tempVector);
	// and remove the y component to make it flat
	tempVector[2] = 0;
	// then normalize it
	normaliseVector(tempVector);
	// and assign it to rightVec
	vectorCopy(rightVector, tempVector);

	// Now work out the up vector by rotating the forward vector pi/2 around the right vector
	rotateAroundVector(forwardVector, rightVector, halfPI, tempVector);
	vectorCopy(upVector, tempVector);
}

// Speed up the camera speed
void Camera::speedUp(void)
{
	if (cameraMoveSpeed < 1.0f)
		cameraMoveSpeed *= 2;
}

// Slow down the camera speed
void Camera::speedDown(void)
{
	if (cameraMoveSpeed > 0.000001f)
		cameraMoveSpeed /= 2;
}

// Move the camera forward
void Camera::moveForward(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the forward direction
	vectorCopy(tempVector, forwardVector);
	vectorMultiple(tempVector, cameraMoveSpeed);

	// Add the movement tempVector to the position vector
	vectorAdd(position, tempVector);
}

// Move the camera backward
void Camera::moveBackward(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the backward direction
	vectorCopy(tempVector, forwardVector);
	vectorMultiple(tempVector, -cameraMoveSpeed); // -cameraSpeed for backwards

	// Add the movement vector to the position vector
	vectorAdd(position, tempVector);
}

// Slide the camera left
void Camera::slideLeft(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the left direction
	vectorCopy(tempVector, rightVector);
	vectorMultiple(tempVector, -cameraMoveSpeed); // -cameraSpeed for left

	// Add the movement vector to the position vector
	vectorAdd(position, tempVector);
}

// Slide the camera right
void Camera::slideRight(void)
{
	float tempVector[3];

	// Make a movement vector the right speed facing the right direction
	vectorCopy(tempVector, rightVector);
	vectorMultiple(tempVector, cameraMoveSpeed);

	// Add the movement vector to the position vector
	vectorAdd(position, tempVector);
}

// Roll the camera to the right
void Camera::rollRight(void)
{
	float tempVector[3];

	// Rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVector(upVector, forwardVector, cameraTurnSpeed, tempVector);
	vectorCopy(upVector, tempVector);

	rotateAroundVector(rightVector, forwardVector, cameraTurnSpeed, tempVector);
	vectorCopy(rightVector, tempVector);
}

// Roll the camera to the left
void Camera::rollLeft(void)
{
	float tempVector[3];

	// Rotate the up and right vectors around the forward vector axis for roll
	rotateAroundVector(upVector, forwardVector, -cameraTurnSpeed, tempVector);
	vectorCopy(upVector, tempVector);

	rotateAroundVector(rightVector, forwardVector, -cameraTurnSpeed, tempVector);
	vectorCopy(rightVector, tempVector);
}

// Pitch the camera up
void Camera::pitchUp(void)
{
	float tempVector[3];

	// Rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVector(forwardVector, rightVector, cameraTurnSpeed, tempVector);
	vectorCopy(forwardVector, tempVector);

	rotateAroundVector(upVector, rightVector, cameraTurnSpeed, tempVector);
	vectorCopy(upVector, tempVector);
}

// Pitch the camera down
void Camera::pitchDown(void)
{
	float tempVector[3];

	// Rotate the forward and up vectors around the right vector axis for pitch
	rotateAroundVector(forwardVector, rightVector, -cameraTurnSpeed, tempVector);
	vectorCopy(forwardVector, tempVector);

	rotateAroundVector(upVector, rightVector, -cameraTurnSpeed, tempVector);
	vectorCopy(upVector, tempVector);
}

// Yaw the camera left
void Camera::yawLeft(void)
{
	float tempVector[3];

	// Rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVector(forwardVector, upVector, cameraTurnSpeed, tempVector);
	vectorCopy(forwardVector, tempVector);

	rotateAroundVector(rightVector, upVector, cameraTurnSpeed, tempVector);
	vectorCopy(rightVector, tempVector);
}

// Yaw the camera right
void Camera::yawRight(void)
{
	float tempVector[3];

	// Rotate the forward and right vectors around the up vector axis for yaw
	rotateAroundVector(forwardVector, upVector, -cameraTurnSpeed, tempVector);
	vectorCopy(forwardVector, tempVector);

	rotateAroundVector(rightVector, upVector, -cameraTurnSpeed, tempVector);
	vectorCopy(rightVector, tempVector);
}

void Camera::reset(void)
{
	vectorCopy(position, positionDefault);
	vectorCopy(forwardVector, forwardDefaultVector);
	vectorCopy(rightVector, rightDefaultVector);
	vectorCopy(upVector, upDefaultVector);
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
