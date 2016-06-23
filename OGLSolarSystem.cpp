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
	if (controls.moveForward) camera->moveForward();		
	if (controls.moveBackward) camera->moveBackward();
	if (controls.slideLeft) camera->slideLeft();			
	if (controls.slideRight) camera->slideRight();
	if (controls.yawLeft) camera->yawLeft();		
	if (controls.yawRight) camera->yawRight();
	if (controls.rollLeft) camera->rollLeft();	
	if (controls.rollRight) camera->rollRight();
	if (controls.pitchUp) camera->pitchUp();		
	if (controls.pitchDown) camera->pitchDown();

	// update the logic and simulation
	timeScale += timeSpeed;
	solarSystem->calculatePositions(timeScale);

	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	// @TODO Need to investigate!!!! ???????
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Render the Universe and solar system
	_drawUniverse();

	solarSystem->renderAll();

	// Perform the camera orientation transform
	setCamera();

	SwapBuffers(_hDC);
}




bool OGLSolarSystem::OGLSolarSystem::initializeContexts(HDC hdc)
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

bool OGLSolarSystem::OGLSolarSystem::initializeOpenGL(GLvoid)
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
	return true;
}

void OGLSolarSystem::OGLSolarSystem::initializeSystem(void)
{
	// Set up times
	timeScale = 2.552f;
	timeSpeed = 0.9f;

	// Toggles on and off drawn of the orbits
	showOrbits = true;

	// reset controls
	controls.moveForward = false;
	controls.moveBackward = false;
	controls.slideLeft = false;
	controls.slideRight = false;
	controls.rollRight = false;
	controls.rollLeft = false;
	controls.pitchDown = false;
	controls.pitchUp = false;
	controls.yawLeft = false;
	controls.yawRight = false;


	//@todo It need to be makes all textures load inside it`s own classes
	// Initialize and load textures
	// Begin from the Universe
	starsTexture = new Texture("textures/stars.tga");
	// Load Sun texture
	sunTexture = new Texture("textures/sun.tga");
	// Load Mercury texture
	mercuryTexture = new Texture("textures/mercury.tga");
	// Load Venus texture
	venusTexture = new Texture("textures/venus.tga");
	// Load Earth texture
	earthTexture = new Texture("textures/earth.tga");
	// Load Mars texture
	marsTexture = new Texture("textures/mars.tga");
	// Load Saturn texture
	saturnTexture = new Texture("textures/saturn.tga");
	// Load Jupiter texture
	jupiterTexture = new Texture("textures/jupiter.tga");
	// Load Neptune texture
	neptuneTexture = new Texture("textures/neptune.tga");
	// Load Neptune texture
	uranusTexture = new Texture("textures/uranus.tga");
	// Load Pluto texture
	plutoTexture = new Texture("textures/pluto.tga");
	// Load Moon 1 texture
	moonTexture1 = new Texture("textures/moon.tga");
	// Load Moon 2 texture
	moonTexture2 = new Texture("textures/moon.tga");
	// Load Moon 3 texture
	moonTexture3 = new Texture("textures/moon.tga");

	// Initialize solar system instance
	solarSystem = new SolarSystem();
	// Add all the planets with it's data. Distance measured in km, time measured in earth days.
	solarSystem->addPlanet(0, 1, 500, 695500, sunTexture->getTextureHandle());						// Sun
	solarSystem->addPlanet(57910000, 88, 58.6, 2439.7, mercuryTexture->getTextureHandle());			// Mercury
	solarSystem->addPlanet(108200000, 224.65, 243, 6052, venusTexture->getTextureHandle());			// Venus
	solarSystem->addPlanet(149600000, 365, 1, 6371, earthTexture->getTextureHandle());				// Earth
	solarSystem->addPlanet(227939100, 686, 1.03f, 3389, marsTexture->getTextureHandle());			// Mars
	solarSystem->addPlanet(778500000, 4332, 0.4139, 69911, jupiterTexture->getTextureHandle());		// Jupiter
	solarSystem->addPlanet(1433000000, 10759, 0.44375, 58232, saturnTexture->getTextureHandle());	// Saturn
	solarSystem->addPlanet(2877000000, 30685, 0.718056, 25362, uranusTexture->getTextureHandle());	// Uranus
	solarSystem->addPlanet(4503000000, 60188, 0.6713, 24622, neptuneTexture->getTextureHandle());	// Neptune
	solarSystem->addPlanet(5906380000, 90616, 6.39, 1137, plutoTexture->getTextureHandle());		// Pluto
	
	solarSystem->addSatellite(3, 384467, 27.3, 27.3, 1738, moonTexture1->getTextureHandle());		// Moon for the Earth
	
	solarSystem->addSatellite(4, 9489.2, 7.6, 7.3, 22, moonTexture2->getTextureHandle());			// Phobos for the Mars
	solarSystem->addSatellite(4, 23723, 30.3, 17.3, 12.2, moonTexture3->getTextureHandle());		// Deimos for the Mars

	// Initialize camera instance
	camera = new Camera();

	setViewport(pMainOGLViewport->Width, pMainOGLViewport->Height);

}

void OGLSolarSystem::OGLSolarSystem::setViewport(int width, int height)
{
	if (height <= 0)
		height = 1;

	int aspectratio = width / height;
	// set up the perspective matrix for rendering the 3d world
	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();

	glViewport(0, 0, width, height);
	gluPerspective(90.0f, aspectratio, 0.0f, 512.0f);

}

void OGLSolarSystem::OGLSolarSystem::setCamera(void)
{
	camera->transformOrientation();
	camera->transformTranslation();
}

void OGLSolarSystem::OGLSolarSystem::_drawUniverse(void)
{
	glPushMatrix();

	// Draw the box with stars on the sides
	glBindTexture(GL_TEXTURE_2D, starsTexture->getTextureHandle());

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
