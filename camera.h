#pragma once

/*Published under The MIT License (MIT)
See LICENSE.TXT*/

// Definitions of the Camera/View port class methods and properties

//
// Sergey Safarov
//

class Camera
{
private:
	// a vector pointing in the direction you are facing
	float forwardVector[3];

	// a vector pointing to the right of where your facing (to describe orientation
	float rightVector[3];

	// a vector pointing upwards from where you are facing
	float upVector[3];

	// the camera position point
	float position[3];

	// the camera speeds
	float cameraSpeed;
	float cameraTurnSpeed;

public:
	Camera(void);

	// transform the OpenGL view matrix for the orientation
	void transformOrientation(void);

	// transform the OpenGL view matrix for the translation
	void transformTranslation(void);

	// points the camera at the given point in 3d space
	void pointAt(float* targetVector);

	// speed up the camera
	void speedUp(void);

	// speed down the camera
	void speedDown(void);

	// move the camera forward
	void moveForward(void);

	// strafe the camera left
	void slideLeft(void);

	// strafe the camera right
	void slideRight(void);

	// move the camera backward
	void moveBackward(void);

	// roll the camera to the right
	void rollRight(void);

	// roll the camera to the left
	void rollLeft(void);

	// pitch the camera up
	void pitchUp(void);

	// pitch the camera down
	void pitchDown(void);

	// yaw the camera left
	void yawLeft(void);

	// yaw the camera right
	void yawRight(void);

};
