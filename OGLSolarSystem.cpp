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


void OGLSolarSystem::OGLSolarSystem::Render(void)
{
	glLoadIdentity();
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	_resize(pMainOGLViewport->Width, pMainOGLViewport->Height);
	_drawUniverse();
	_drawSolarSystem();

	SwapBuffers(_hDC);
}




bool OGLSolarSystem::OGLSolarSystem::_initializeSystem(HDC hdc)
{
	_hDC = hdc;

	// set up time scales
	_timeScale = 2.552f;
	_timeSpeed = 0.1f;

	// reset controls
	_controls.forward = false;
	_controls.backward = false;
	_controls.left = false;
	_controls.right = false;
	_controls.rollRight = false;
	_controls.rollLeft = false;
	_controls.pitchDown = false;
	_controls.pitchUp = false;
	_controls.yawLeft = false;
	_controls.yawRight = false;

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Initialization
	glEnable(GL_TEXTURE_2D);				// Enable Texture Mapping
	glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Black Background

											// Set up lights and materials
	glEnable(GL_LIGHT0);

	GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat matShininess[] = { 20.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

	GLfloat lightAmbient[] = { 0.9, 0.8, 0.3, 1.0 };
	GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glColor4f(0.6f, 0.0f, 0.0f, 1.0);					// Full Brightness.  50% Alpha

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

	_solarSystem = new SolarSystem();


	// Initialization went OK
	return TRUE;
}

void OGLSolarSystem::OGLSolarSystem::_resize(int width, int height)
{
	if (height <= 0)
		height = 1;

	int aspectratio = width / height;
	glViewport(0, 0, width, height);
	gluPerspective(90.0f, aspectratio, 0.1f, 255.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OGLSolarSystem::OGLSolarSystem::_drawUniverse(void)
{

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
}

void OGLSolarSystem::OGLSolarSystem::_drawSolarSystem(void)
{
	// Add all the planets with accurate data. Distance measured in km, time measured in earth days.
	_solarSystem->addPlanet(0, 1, 500, 695500, _sunTexture->getTextureHandle()); // Sun


	_solarSystem->renderAll();

}