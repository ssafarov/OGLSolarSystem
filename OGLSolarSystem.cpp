#include "OGLSolarSystem.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^ argv)
{
	Application::EnableVisualStyles;
	Application::SetCompatibleTextRenderingDefault(false);
	OGLSolarSystem::OGLSolarSystem form;
	Application::Run(%form);
}





void OGLSolarSystem::OGLSolarSystem::OGLShutdown(void)
{
	wglMakeCurrent(_hDC, NULL);	// release current device context
	wglDeleteContext(_hRC);		// delete rendering context
}


void OGLSolarSystem::OGLSolarSystem::OGLRender(void)
{
	// update the logic and simulation
	_timeScale += _timeSpeed;
	_solarSystem->calculatePositions(_timeScale);

	if (_controls.moveForward) _camera->moveForward();		if (_controls.moveBackward) _camera->moveBackward();
	if (_controls.slideLeft) _camera->slideLeft();			if (_controls.slideRight) _camera->slideRight();
	if (_controls.yawLeft) _camera->yawLeft();		if (_controls.yawRight) _camera->yawRight();
	if (_controls.rollLeft) _camera->rollLeft();	if (_controls.rollRight) _camera->rollRight();
	if (_controls.pitchUp) _camera->pitchUp();		if (_controls.pitchDown) _camera->pitchDown();

	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	_drawUniverse();

	_drawSolarSystem();

	// perform the camera orientation transform
	_setViewport(pMainOGLViewport->Width, pMainOGLViewport->Height);

	SwapBuffers(_hDC);
}




bool OGLSolarSystem::OGLSolarSystem::_initializeContexts(HDC hdc)
{
	_hDC = hdc;

	PIXELFORMATDESCRIPTOR pfd = {		// Set the pixel format description
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pixel format description 
		1,								// version number 
		PFD_DRAW_TO_WINDOW |            // support window 
		PFD_SUPPORT_OPENGL |            // support OpenGL 
		PFD_DOUBLEBUFFER,               // double buffered 
		PFD_TYPE_RGBA,                  // RGBA type 
		24,                             // 24-bit color depth 
		0, 0, 0, 0, 0, 0,               // color bits ignored 
		0,                              // no alpha buffer 
		0,                              // shift bit ignored 
		0,                              // no accumulation buffer 
		0, 0, 0, 0,                     // ignored bits
		32,                             // 32-bit z-buffer     
		0,                              // no stencil buffer 
		0,                              // no auxiliary buffer 
		PFD_MAIN_PLANE,                 // main layer 
		0,                              // reserved 
		0, 0, 0                         // layer masks ignored 
	};

	int iPixelFormat = ChoosePixelFormat(_hDC, &pfd);

	if (iPixelFormat == 0) {
		MessageBox::Show("ChoosePixelFormat Failed");
		return false;
	}

	if (SetPixelFormat(_hDC, iPixelFormat, &pfd) == FALSE) {
		MessageBox::Show("SetPixelFormat Failed");
		return false;
	}

	wglDeleteContext(_hRC);
	_hRC = wglCreateContext(_hDC);
	if (_hRC == NULL) {
		MessageBox::Show("wglCreateContext Failed");
		return false;
	}
	if (wglMakeCurrent(_hDC, _hRC) == NULL) {
		MessageBox::Show("wglMakeCurrent Failed");
		return false;
	}

	return true;
}

int OGLSolarSystem::OGLSolarSystem::_initializeOpenGL(GLvoid)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

	// set up lighting
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matShininess[] = { 20.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// Initialization went OK
	return TRUE;
}

void OGLSolarSystem::OGLSolarSystem::_initializeSystem(void)
{
	// Set up times
	_timeScale = 2.552f;
	_timeSpeed = 0.1f;

	// Toggles on and off drawn of the orbits
	_showOrbits = true;

	// reset controls
	_controls.moveForward = false;
	_controls.moveBackward = false;
	_controls.slideLeft = false;
	_controls.slideRight = false;
	_controls.rollRight = false;
	_controls.rollLeft = false;
	_controls.pitchDown = false;
	_controls.pitchUp = false;
	_controls.yawLeft = false;
	_controls.yawRight = false;


	// Initialize camera instance
	_camera = new Camera();

	// Initialize solar system instance
	_solarSystem = new SolarSystem();

	// Initialize and load textures
	// Begin from the Universe

	_starsTexture = new Texture("textures/\stars.tga");

	//@todo It need to be makes all textures load inside it`s own classes
	// Load Sun texture
	_sunTexture = new Texture("textures/\sun.tga");

	// Load Mercury texture
	_mercuryTexture = new Texture("textures/\mercury.tga");
	/*
	// Load Venus texture
	_venusTexture = new Texture("textures/\venus.tga");
	// Load Earth texture
	_earthTexture = new Texture("textures/\earth.tga");
	// Load Mars texture
	_marsTexture = new Texture("textures/\mars.tga");
	// Load Saturn texture
	_saturnTexture = new Texture("textures/\saturn.tga");
	// Load Jupiter texture
	_jupiterTexture = new Texture("textures/\jupiter.tga");
	// Load Neptune texture
	_neptuneTexture = new Texture("textures/\neptune.tga");
	// Load Neptune texture
	_uranusTexture = new Texture("textures/\uranus.tga");
	// Load Pluto texture
	_plutoTexture = new Texture("textures/\pluto.tga");
	// Load Moon 1 texture
	_moonTexture1 = new Texture("textures/\moon.tga");
	// Load Moon 2 texture
	_moonTexture2 = new Texture("textures/\moon.tga");
	// Load Moon 3 texture
	_moonTexture3 = new Texture("textures/\moon.tga");
	*/


}

void OGLSolarSystem::OGLSolarSystem::_setViewport(int width, int height)
{
	if (height <= 0)
		height = 1;

	int aspectratio = width / height;
	// set up the perspective matrix for rendering the 3d world
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(60.0f, aspectratio, 0.0f, 255.0f);

	_camera->transformOrientation();
	_camera->transformTranslation();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OGLSolarSystem::OGLSolarSystem::_drawUniverse(void)
{
	glPushMatrix();

	// Draw the box with stars on the sides
	glBindTexture(GL_TEXTURE_2D, _starsTexture->getTextureHandle());

	glBegin(GL_QUADS);
	// Side 1 
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Side 2
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	// Side 3
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	// Side 4
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	// Side 5
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
	// Side 6
	glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();

	glPopMatrix();
}

void OGLSolarSystem::OGLSolarSystem::_drawSolarSystem(void)
{
	// Add all the planets with accurate data. Distance measured in km, time measured in earth days.
	_solarSystem->addPlanet(0, 1, 500, 695500, _sunTexture->getTextureHandle());				// Sun
	_solarSystem->addPlanet(57910000, 88, 58.6, 2439.7, _mercuryTexture->getTextureHandle());	// Mercury

	_solarSystem->renderAll();

}