#pragma once

#include <Windows.h>

#include <GL\glut.h>
#include <vector>

#include "texture.h"
#include "camera.h"


namespace OGLSolarSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OGLSolarSystem
	/// </summary>
	public ref class OGLSolarSystem : public System::Windows::Forms::Form
	{
		public:
			HDC		hDC;	// Private GDI Device Context
			HGLRC	hRC;	// Get handle to panel on form and call initialization function
							
			Camera  *camera;	// The instance of the camera

		OGLSolarSystem(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			HWND hWnd = (HWND)pMainOGLViewport->Handle.ToInt64();
			_initializeOpenGL(GetDC(hWnd));
			_initOpenGL();
		}

		void Render(void)
		{
			glLoadIdentity();
			// clear the buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glColor3f(1.0, 1.0, 1.0);

			this->_drawUniverse();

			SwapBuffers(hDC);
		}

		protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OGLSolarSystem()
		{
			if (components)
			{
				delete components;
			}
		}

		private: System::ComponentModel::IContainer^  components;
		private: System::Windows::Forms::MenuStrip^  menuStripMain;
		private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  miExit;

		private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
		private: System::Windows::Forms::Panel^  pControls;
		private: System::Windows::Forms::Panel^  pMainOGLViewport;
		private: System::Windows::Forms::NumericUpDown^  nudParamsTimeScale;
		private: System::Windows::Forms::NumericUpDown^  nudParamsDistanceScale;

		private: System::Windows::Forms::CheckBox^  cbParamsShowOrbits;

		private: System::Windows::Forms::Label^  lGlobalParams;
		private: System::Windows::Forms::Label^  lCurrentDateTimeTitle;
		private: System::Windows::Forms::Label^  lCurrentDateTime;
		private: System::Windows::Forms::Label^  lCross;
		private: System::Windows::Forms::Label^  lParamsTimeScale;
		private: System::Windows::Forms::Label^  lParamsDistanceScale;

		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Timer^  timer1;

		private:
			// These control the simulation of time
			double time;
			double timeSpeed;

			// Toggles drawn of the orbits
			bool showOrbits = true;

			Texture *stars = new Texture("textures/\stars.tga");

			ref struct ControlStates
			{
				bool forward, backward, left, right, yawLeft, yawRight, pitchUp, pitchDown, rollLeft, rollRight;
			} controls;

			bool _initializeOpenGL(HDC hdc)
			{
				hDC = hdc;


				// set up time scales
				this->time = 2.552f;
				this->timeSpeed = 0.1f;

				// reset controls
				this->controls.forward = false;
				this->controls.backward = false;
				this->controls.left = false;
				this->controls.right = false;
				this->controls.rollRight = false;
				this->controls.rollLeft = false;
				this->controls.pitchDown = false;
				this->controls.pitchUp = false;
				this->controls.yawLeft = false;
				this->controls.yawRight = false;

				// Set the pixel format description
				PIXELFORMATDESCRIPTOR pfd = {
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

				int iPixelFormat = ChoosePixelFormat(hDC, &pfd);

				if (iPixelFormat == 0) {
					MessageBox::Show("ChoosePixelFormat Failed");
					return false;
				}

				if (SetPixelFormat(hDC, iPixelFormat, &pfd) == FALSE) {
					MessageBox::Show("SetPixelFormat Failed");
					return false;
				}

				wglDeleteContext(hRC);
				hRC = wglCreateContext(hDC);
				if (hRC == NULL) {
					MessageBox::Show("wglCreateContext Failed");
					return false;
				}
				if (wglMakeCurrent(hDC, hRC) == NULL) {
					MessageBox::Show("wglMakeCurrent Failed");
					return false;
				}

				return true;
			}

			int _initOpenGL(GLvoid)
			{
				// Initialization
				glEnable(GL_TEXTURE_2D);				// Enable Texture Mapping
				glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
				glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Black Background

				// Set up lights
				glEnable(GL_LIGHT0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
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

				return TRUE;										// Initialization went OK
			}

			void _drawUniverse(void)
			{
				glBegin(GL_QUADS);

				// draw the box with stars on the sides
				glBindTexture(GL_TEXTURE_2D, this->stars->getTextureHandle());

				// side 1 
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
				// side 2
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
				// side 3
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
				// side 4
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
				// side 5
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
				// side 6
				glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
				glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

				glEnd();
			}

			/// <summary>
			/// Required designer variable.
			/// </summary>


#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStripMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->miExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pControls = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lParamsDistanceScale = (gcnew System::Windows::Forms::Label());
			this->nudParamsDistanceScale = (gcnew System::Windows::Forms::NumericUpDown());
			this->lCross = (gcnew System::Windows::Forms::Label());
			this->lParamsTimeScale = (gcnew System::Windows::Forms::Label());
			this->nudParamsTimeScale = (gcnew System::Windows::Forms::NumericUpDown());
			this->cbParamsShowOrbits = (gcnew System::Windows::Forms::CheckBox());
			this->lGlobalParams = (gcnew System::Windows::Forms::Label());
			this->pMainOGLViewport = (gcnew System::Windows::Forms::Panel());
			this->lCurrentDateTimeTitle = (gcnew System::Windows::Forms::Label());
			this->lCurrentDateTime = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStripMain->SuspendLayout();
			this->pControls->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsDistanceScale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsTimeScale))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStripMain
			// 
			this->menuStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStripMain->Location = System::Drawing::Point(0, 0);
			this->menuStripMain->Name = L"menuStripMain";
			this->menuStripMain->Size = System::Drawing::Size(1040, 24);
			this->menuStripMain->TabIndex = 0;
			this->menuStripMain->Text = L"menuStripMain";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->miExit });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// miExit
			// 
			this->miExit->Name = L"miExit";
			this->miExit->Size = System::Drawing::Size(92, 22);
			this->miExit->Text = L"Exit";
			this->miExit->Click += gcnew System::EventHandler(this, &OGLSolarSystem::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->aboutToolStripMenuItem->Text = L"About ...";
			// 
			// pControls
			// 
			this->pControls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->pControls->AutoScroll = true;
			this->pControls->Controls->Add(this->label2);
			this->pControls->Controls->Add(this->lParamsDistanceScale);
			this->pControls->Controls->Add(this->nudParamsDistanceScale);
			this->pControls->Controls->Add(this->lCross);
			this->pControls->Controls->Add(this->lParamsTimeScale);
			this->pControls->Controls->Add(this->nudParamsTimeScale);
			this->pControls->Controls->Add(this->cbParamsShowOrbits);
			this->pControls->Controls->Add(this->lGlobalParams);
			this->pControls->Location = System::Drawing::Point(0, 27);
			this->pControls->Name = L"pControls";
			this->pControls->Size = System::Drawing::Size(271, 522);
			this->pControls->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(189, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 13);
			this->label2->TabIndex = 53;
			this->label2->Text = L"x / 10 000 000";
			// 
			// lParamsDistanceScale
			// 
			this->lParamsDistanceScale->AutoSize = true;
			this->lParamsDistanceScale->Location = System::Drawing::Point(47, 87);
			this->lParamsDistanceScale->Name = L"lParamsDistanceScale";
			this->lParamsDistanceScale->Size = System::Drawing::Size(83, 13);
			this->lParamsDistanceScale->TabIndex = 52;
			this->lParamsDistanceScale->Text = L"Distance scale :";
			// 
			// nudParamsDistanceScale
			// 
			this->nudParamsDistanceScale->Location = System::Drawing::Point(136, 85);
			this->nudParamsDistanceScale->Name = L"nudParamsDistanceScale";
			this->nudParamsDistanceScale->Size = System::Drawing::Size(47, 20);
			this->nudParamsDistanceScale->TabIndex = 51;
			this->nudParamsDistanceScale->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// lCross
			// 
			this->lCross->AutoSize = true;
			this->lCross->Location = System::Drawing::Point(189, 61);
			this->lCross->Name = L"lCross";
			this->lCross->Size = System::Drawing::Size(12, 13);
			this->lCross->TabIndex = 50;
			this->lCross->Text = L"x";
			// 
			// lParamsTimeScale
			// 
			this->lParamsTimeScale->AutoSize = true;
			this->lParamsTimeScale->Location = System::Drawing::Point(16, 61);
			this->lParamsTimeScale->Name = L"lParamsTimeScale";
			this->lParamsTimeScale->Size = System::Drawing::Size(114, 13);
			this->lParamsTimeScale->TabIndex = 49;
			this->lParamsTimeScale->Text = L"Time scale slowdown :";
			// 
			// nudParamsTimeScale
			// 
			this->nudParamsTimeScale->Location = System::Drawing::Point(136, 59);
			this->nudParamsTimeScale->Name = L"nudParamsTimeScale";
			this->nudParamsTimeScale->Size = System::Drawing::Size(47, 20);
			this->nudParamsTimeScale->TabIndex = 48;
			this->nudParamsTimeScale->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// cbParamsShowOrbits
			// 
			this->cbParamsShowOrbits->AutoSize = true;
			this->cbParamsShowOrbits->Checked = true;
			this->cbParamsShowOrbits->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbParamsShowOrbits->Location = System::Drawing::Point(15, 36);
			this->cbParamsShowOrbits->Name = L"cbParamsShowOrbits";
			this->cbParamsShowOrbits->Size = System::Drawing::Size(81, 17);
			this->cbParamsShowOrbits->TabIndex = 3;
			this->cbParamsShowOrbits->Text = L"Show orbits";
			this->cbParamsShowOrbits->UseVisualStyleBackColor = true;
			// 
			// lGlobalParams
			// 
			this->lGlobalParams->AutoSize = true;
			this->lGlobalParams->Location = System::Drawing::Point(12, 10);
			this->lGlobalParams->Name = L"lGlobalParams";
			this->lGlobalParams->Size = System::Drawing::Size(92, 13);
			this->lGlobalParams->TabIndex = 47;
			this->lGlobalParams->Text = L"Global parameters";
			// 
			// pMainOGLViewport
			// 
			this->pMainOGLViewport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pMainOGLViewport->AutoScroll = true;
			this->pMainOGLViewport->Location = System::Drawing::Point(277, 63);
			this->pMainOGLViewport->Name = L"pMainOGLViewport";
			this->pMainOGLViewport->Size = System::Drawing::Size(758, 486);
			this->pMainOGLViewport->TabIndex = 2;
			this->pMainOGLViewport->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OGLSolarSystem::pMainOGLViewport_Paint);
			// 
			// lCurrentDateTimeTitle
			// 
			this->lCurrentDateTimeTitle->AutoSize = true;
			this->lCurrentDateTimeTitle->Location = System::Drawing::Point(277, 37);
			this->lCurrentDateTimeTitle->Name = L"lCurrentDateTimeTitle";
			this->lCurrentDateTimeTitle->Size = System::Drawing::Size(33, 13);
			this->lCurrentDateTimeTitle->TabIndex = 6;
			this->lCurrentDateTimeTitle->Text = L"Time:";
			// 
			// lCurrentDateTime
			// 
			this->lCurrentDateTime->AutoSize = true;
			this->lCurrentDateTime->Location = System::Drawing::Point(316, 37);
			this->lCurrentDateTime->Name = L"lCurrentDateTime";
			this->lCurrentDateTime->Size = System::Drawing::Size(107, 13);
			this->lCurrentDateTime->TabIndex = 7;
			this->lCurrentDateTime->Text = L"Jan 1/2015 12:45:00";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &OGLSolarSystem::timer1_Tick);
			// 
			// OGLSolarSystem
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1040, 554);
			this->Controls->Add(this->lCurrentDateTime);
			this->Controls->Add(this->lCurrentDateTimeTitle);
			this->Controls->Add(this->pMainOGLViewport);
			this->Controls->Add(this->pControls);
			this->Controls->Add(this->menuStripMain);
			this->MainMenuStrip = this->menuStripMain;
			this->Name = L"OGLSolarSystem";
			this->Text = L"OGLSolarSystem";
			this->Load += gcnew System::EventHandler(this, &OGLSolarSystem::OGLSolarSystem_Load);
			this->menuStripMain->ResumeLayout(false);
			this->menuStripMain->PerformLayout();
			this->pControls->ResumeLayout(false);
			this->pControls->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsDistanceScale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsTimeScale))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
		private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
		}
		private: System::Void OGLSolarSystem_Load(System::Object^  sender, System::EventArgs^  e) {

		}
		private: System::Void pMainOGLViewport_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			Render();
		}
		private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			Render();
		}
	};
}
