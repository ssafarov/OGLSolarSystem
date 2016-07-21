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

void OGLSolarSystem::OGLSolarSystem::initializeOpenGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_LIGHTING);

	OGLviewportResize();
}

void OGLSolarSystem::OGLSolarSystem::initializeSystem(void)
{
	// Set up times
	__time64_t rawTime;
	_time64(&rawTime);
	timeScale = 1.0f;// rawTime;
	timeSpeed = 0.01f;

	// Initialize camera instance
	camera = new Camera();

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
	starsTexture = new Texture("textures/stars.tga");		// Begin from the Universe
	sunTexture = new Texture("textures/sun.tga");			// Load Sun texture
	mercuryTexture = new Texture("textures/mercury.tga");	// Load Mercury texture
	venusTexture = new Texture("textures/venus.tga");		// Load Venus texture
	earthTexture = new Texture("textures/earth.tga");		// Load Earth texture
	marsTexture = new Texture("textures/mars.tga");			// Load Mars texture
	saturnTexture = new Texture("textures/saturn.tga");		// Load Saturn texture
	jupiterTexture = new Texture("textures/jupiter.tga");	// Load Jupiter texture
	neptuneTexture = new Texture("textures/neptune.tga");	// Load Neptune texture
	uranusTexture = new Texture("textures/uranus.tga");		// Load Neptune texture
	plutoTexture = new Texture("textures/pluto.tga");		// Load Pluto texture
	moonTexture1 = new Texture("textures/moon.tga");		// Load Moon 1 texture
	moonTexture2 = new Texture("textures/moon.tga");		// Load Moon 2 texture
	moonTexture3 = new Texture("textures/moon.tga");		// Load Moon 3 texture

															// Initialize solar system instance
	solarSystem = new SolarSystem();
	// Add all the planets with it's data. Distance measured in km, time measured in earth days.
	solarSystem->addPlanet(0, 1, 500, 695500, sunTexture->getTextureHandle());						// Sun
	solarSystem->addPlanet(57910000, 88, 58.6, 2439.7, mercuryTexture->getTextureHandle());			// Mercury
	solarSystem->addPlanet(108200000, 224.65, 243, 6052, venusTexture->getTextureHandle());			// Venus
	solarSystem->addPlanet(149600000, 365, 1, 6378.16, earthTexture->getTextureHandle());				// Earth
	solarSystem->addPlanet(227939100, 686, 1.03f, 3389, marsTexture->getTextureHandle());			// Mars
	solarSystem->addPlanet(778500000, 4332, 0.4139, 69911, jupiterTexture->getTextureHandle());		// Jupiter
	solarSystem->addPlanet(1433000000, 10759, 0.44375, 58232, saturnTexture->getTextureHandle());	// Saturn
	solarSystem->addPlanet(2877000000, 30685, 0.718056, 25362, uranusTexture->getTextureHandle());	// Uranus
	solarSystem->addPlanet(4503000000, 60188, 0.6713, 24622, neptuneTexture->getTextureHandle());	// Neptune
	solarSystem->addPlanet(5906380000, 90616, 6.39, 1137, plutoTexture->getTextureHandle());		// Pluto
	
	solarSystem->addSatellite(3, 384467, 27.3, 27.3, 1738, moonTexture1->getTextureHandle());		// Moon for the Earth
	
	solarSystem->addSatellite(4, 948920, 7.6, 7.3, 22, moonTexture2->getTextureHandle());			// Phobos for the Mars
	solarSystem->addSatellite(4, 2372300, 30.3, 17.3, 12.2, moonTexture3->getTextureHandle());		// Deimos for the Mars

}

void OGLSolarSystem::OGLSolarSystem::setViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void OGLSolarSystem::OGLSolarSystem::setCamera(void)
{
	camera->transformOrientation();
	camera->transformTranslation();
}

void OGLSolarSystem::OGLSolarSystem::renderUniverse(void)
{
	glPushMatrix();

	// translate to the right position
	glTranslatef(0.0f, 0.0f, 0.0f);

	// Draw the box with stars on the sides
	glBindTexture(GL_TEXTURE_2D, starsTexture->getTextureHandle());

	// render as a GLU sphere quadric object
	GLUquadricObj* OQquadric = gluNewQuadric();
	gluQuadricTexture(OQquadric, true);
	gluQuadricNormals(OQquadric, GLU_SMOOTH);
	gluQuadricOrientation(OQquadric, GLU_INSIDE);
	float universeRadius = 100.0f;

	// Setup global lighting for the universe -- BEGIN
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat lightDiffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	// Setup global lighting of the universe -- END

	gluSphere(OQquadric, universeRadius, 512, 512);

	glPopMatrix();

}

void OGLSolarSystem::OGLSolarSystem::OGLviewportResize(void)
{
	int _iWidth = pMainOGLViewport->Width;
	int _iHeight = pMainOGLViewport->Height;

	if (_iHeight == 0) _iHeight = 1;

	glViewport(0, 0, _iWidth, _iHeight);

	viewPortAspectRatio = _iWidth / _iHeight;
	viewPortAspectRatio = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(80.0f, viewPortAspectRatio, 0.01f, 512.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OGLSolarSystem::OGLSolarSystem::OGLupdateGUI(void)
{

	lPosX->Text = String::Format("{0:0.000000000}", camera->position[0]);
	lPosY->Text = String::Format("{0:0.000000000}", camera->position[1]);
	lPosZ->Text = String::Format("{0:0.000000000}", camera->position[2]);

	lCurrentDateTime->Text = String::Format("{0:0.000000000}", timeScale);
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

	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set up the model matrix for rendering the 3d objects
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// perform the camera orientation transform
	setCamera();


	// Render the Universe
	renderUniverse();

	glDisable(GL_LIGHTING);
	if (showOrbits)
		solarSystem->renderOrbits();

	// render the solar system
	solarSystem->render();
	glEnable(GL_LIGHTING);

	glFlush();
	SwapBuffers(_hDC);

	OGLupdateGUI();
}

