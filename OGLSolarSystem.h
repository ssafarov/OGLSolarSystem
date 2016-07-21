#pragma once

#include <Windows.h>
#include <string>
#include <ctime>

#include "texture.h"
#include "camera.h"
#include "solarsystem.h"

#include "Libraries\glew\GL\glew.h"
#include "Libraries\freeglut\GL\freeglut.h"


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
			OGLSolarSystem(void)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//
				HWND hWnd = (HWND)pMainOGLViewport->Handle.ToInt64();
				if (initializeContexts(GetDC(hWnd))) {
					initializeOpenGL();
					initializeSystem();
				}
			}

			void OGLRender(void);
			void OGLShutdown(void);

		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~OGLSolarSystem()
			{
				OGLShutdown();

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
		private: System::Windows::Forms::NumericUpDown^  nudParamsTimeSpeed;

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
			HDC		_hDC;	// Private GDI Device Context
			HGLRC	_hRC;	// Get handle to panel on form and call initialization function						

			// These control the simulation of time line and scale
			double timeScale;
			double timeSpeed;

			bool showOrbits;
			int planetSelected;

			ref struct ControlStates
			{
				bool moveForward, moveBackward, slideLeft, slideRight, yawLeft, yawRight, pitchUp, pitchDown, rollLeft, rollRight;
			} controls;

			// Custom functions for solar system
			bool initializeContexts(HDC hdc);
			void initializeOpenGL(GLvoid);
			void initializeSystem(void);

			void setViewport(int width, int height);
			void setCamera(void);
			void renderUniverse(void);
			void OGLviewportResize(void);
			void OGLupdateGUI(void);

			float viewPortAspectRatio;


			Texture* starsTexture;
			Texture* sunTexture;
			Texture* mercuryTexture;
			Texture* venusTexture;
			Texture* earthTexture;
			Texture* moonTexture1;
			Texture* moonTexture2;
			Texture* moonTexture3;
			Texture* marsTexture;
			Texture* saturnTexture;
			Texture* jupiterTexture;
			Texture* neptuneTexture;
			Texture* uranusTexture;
			Texture* plutoTexture;

			Camera* camera;	// The instance of the camera

			SolarSystem* solarSystem; // The main instance of the solar system


			private: System::Windows::Forms::Label^  lPosZ;
			private: System::Windows::Forms::Label^  lPosY;
			private: System::Windows::Forms::Label^  lPosX;
			private: System::Windows::Forms::Label^  lRoll;
			private: System::Windows::Forms::Label^  lHeading;
			private: System::Windows::Forms::Label^  lPitch;
			private: System::Windows::Forms::Label^  label1;
			private: System::Windows::Forms::Label^  label3;
			private: System::Windows::Forms::Label^  label7;
			private: System::Windows::Forms::Label^  label8;
			private: System::Windows::Forms::Label^  label9;
			private: System::Windows::Forms::Label^  label6;
			private: System::Windows::Forms::Label^  label5;
			private: System::Windows::Forms::Label^  label4;
			private: System::Windows::Forms::Button^  button1;


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
			this->lRoll = (gcnew System::Windows::Forms::Label());
			this->lHeading = (gcnew System::Windows::Forms::Label());
			this->lPitch = (gcnew System::Windows::Forms::Label());
			this->lPosZ = (gcnew System::Windows::Forms::Label());
			this->lPosY = (gcnew System::Windows::Forms::Label());
			this->lPosX = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lParamsDistanceScale = (gcnew System::Windows::Forms::Label());
			this->nudParamsDistanceScale = (gcnew System::Windows::Forms::NumericUpDown());
			this->lCross = (gcnew System::Windows::Forms::Label());
			this->lParamsTimeScale = (gcnew System::Windows::Forms::Label());
			this->nudParamsTimeSpeed = (gcnew System::Windows::Forms::NumericUpDown());
			this->cbParamsShowOrbits = (gcnew System::Windows::Forms::CheckBox());
			this->lGlobalParams = (gcnew System::Windows::Forms::Label());
			this->pMainOGLViewport = (gcnew System::Windows::Forms::Panel());
			this->lCurrentDateTimeTitle = (gcnew System::Windows::Forms::Label());
			this->lCurrentDateTime = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStripMain->SuspendLayout();
			this->pControls->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsDistanceScale))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsTimeSpeed))->BeginInit();
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
			this->pControls->Controls->Add(this->lRoll);
			this->pControls->Controls->Add(this->lHeading);
			this->pControls->Controls->Add(this->lPitch);
			this->pControls->Controls->Add(this->lPosZ);
			this->pControls->Controls->Add(this->lPosY);
			this->pControls->Controls->Add(this->lPosX);
			this->pControls->Controls->Add(this->button1);
			this->pControls->Controls->Add(this->label7);
			this->pControls->Controls->Add(this->label8);
			this->pControls->Controls->Add(this->label9);
			this->pControls->Controls->Add(this->label6);
			this->pControls->Controls->Add(this->label5);
			this->pControls->Controls->Add(this->label4);
			this->pControls->Controls->Add(this->label3);
			this->pControls->Controls->Add(this->label1);
			this->pControls->Controls->Add(this->label2);
			this->pControls->Controls->Add(this->lParamsDistanceScale);
			this->pControls->Controls->Add(this->nudParamsDistanceScale);
			this->pControls->Controls->Add(this->lCross);
			this->pControls->Controls->Add(this->lParamsTimeScale);
			this->pControls->Controls->Add(this->nudParamsTimeSpeed);
			this->pControls->Controls->Add(this->cbParamsShowOrbits);
			this->pControls->Controls->Add(this->lGlobalParams);
			this->pControls->Location = System::Drawing::Point(0, 27);
			this->pControls->Name = L"pControls";
			this->pControls->Size = System::Drawing::Size(271, 522);
			this->pControls->TabIndex = 1;
			// 
			// lRoll
			// 
			this->lRoll->AutoSize = true;
			this->lRoll->Location = System::Drawing::Point(201, 231);
			this->lRoll->Name = L"lRoll";
			this->lRoll->Size = System::Drawing::Size(44, 13);
			this->lRoll->TabIndex = 75;
			this->lRoll->Text = L"Z-coord";
			// 
			// lHeading
			// 
			this->lHeading->AutoSize = true;
			this->lHeading->Location = System::Drawing::Point(201, 210);
			this->lHeading->Name = L"lHeading";
			this->lHeading->Size = System::Drawing::Size(44, 13);
			this->lHeading->TabIndex = 74;
			this->lHeading->Text = L"Y-coord";
			// 
			// lPitch
			// 
			this->lPitch->AutoSize = true;
			this->lPitch->Location = System::Drawing::Point(201, 187);
			this->lPitch->Name = L"lPitch";
			this->lPitch->Size = System::Drawing::Size(44, 13);
			this->lPitch->TabIndex = 73;
			this->lPitch->Text = L"X-coord";
			// 
			// lPosZ
			// 
			this->lPosZ->AutoSize = true;
			this->lPosZ->Location = System::Drawing::Point(69, 229);
			this->lPosZ->Name = L"lPosZ";
			this->lPosZ->Size = System::Drawing::Size(44, 13);
			this->lPosZ->TabIndex = 72;
			this->lPosZ->Text = L"Z-coord";
			// 
			// lPosY
			// 
			this->lPosY->AutoSize = true;
			this->lPosY->Location = System::Drawing::Point(69, 208);
			this->lPosY->Name = L"lPosY";
			this->lPosY->Size = System::Drawing::Size(44, 13);
			this->lPosY->TabIndex = 71;
			this->lPosY->Text = L"Y-coord";
			// 
			// lPosX
			// 
			this->lPosX->AutoSize = true;
			this->lPosX->Location = System::Drawing::Point(69, 185);
			this->lPosX->Name = L"lPosX";
			this->lPosX->Size = System::Drawing::Size(44, 13);
			this->lPosX->TabIndex = 70;
			this->lPosX->Text = L"X-coord";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(61, 146);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(122, 23);
			this->button1->TabIndex = 69;
			this->button1->Text = L"Reset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &OGLSolarSystem::button1_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(163, 231);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(41, 13);
			this->label7->TabIndex = 65;
			this->label7->Text = L"Roll (Z)";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(141, 210);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(63, 13);
			this->label8->TabIndex = 64;
			this->label8->Text = L"Heading (Y)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(157, 187);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(47, 13);
			this->label9->TabIndex = 63;
			this->label9->Text = L"Pitch (X)";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(58, 229);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(14, 13);
			this->label6->TabIndex = 58;
			this->label6->Text = L"Z";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(58, 208);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 57;
			this->label5->Text = L"Y";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(58, 185);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 56;
			this->label4->Text = L"X";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 206);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 13);
			this->label3->TabIndex = 55;
			this->label3->Text = L"Position";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 151);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 13);
			this->label1->TabIndex = 54;
			this->label1->Text = L"Camera";
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
			this->lParamsTimeScale->Location = System::Drawing::Point(69, 61);
			this->lParamsTimeScale->Name = L"lParamsTimeScale";
			this->lParamsTimeScale->Size = System::Drawing::Size(61, 13);
			this->lParamsTimeScale->TabIndex = 49;
			this->lParamsTimeScale->Text = L"Time scale:";
			// 
			// nudParamsTimeSpeed
			// 
			this->nudParamsTimeSpeed->DecimalPlaces = 2;
			this->nudParamsTimeSpeed->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->nudParamsTimeSpeed->Location = System::Drawing::Point(136, 59);
			this->nudParamsTimeSpeed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 99, 0, 0, 0 });
			this->nudParamsTimeSpeed->Name = L"nudParamsTimeSpeed";
			this->nudParamsTimeSpeed->Size = System::Drawing::Size(47, 20);
			this->nudParamsTimeSpeed->TabIndex = 48;
			this->nudParamsTimeSpeed->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->nudParamsTimeSpeed->ValueChanged += gcnew System::EventHandler(this, &OGLSolarSystem::nudParamsTimeScale_ValueChanged);
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
			this->KeyPreview = true;
			this->MainMenuStrip = this->menuStripMain;
			this->Name = L"OGLSolarSystem";
			this->Text = L"OGLSolarSystem";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &OGLSolarSystem::OGLSolarSystem_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &OGLSolarSystem::OGLSolarSystem_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &OGLSolarSystem::OGLSolarSystem_KeyUp);
			this->Resize += gcnew System::EventHandler(this, &OGLSolarSystem::OGLSolarSystem_Resize);
			this->menuStripMain->ResumeLayout(false);
			this->menuStripMain->PerformLayout();
			this->pControls->ResumeLayout(false);
			this->pControls->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsDistanceScale))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudParamsTimeSpeed))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Application::Exit();
		}
		private: System::Void OGLSolarSystem_Resize(System::Object^  sender, System::EventArgs^  e) {
			OGLviewportResize();
			OGLRender();
		}
		private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			UNREFERENCED_PARAMETER(sender);
			UNREFERENCED_PARAMETER(e);
			OGLRender();
		}
		private: System::Void nudParamsTimeScale_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			timeSpeed = (double)nudParamsTimeSpeed->Value;
		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		camera->reset();
	}

private: System::Void OGLSolarSystem_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

	switch (e->KeyCode)
	{
	case Keys::W:
		controls.moveForward = true;
		break;
	case Keys::S:
		controls.moveBackward = true;
		break;
	case Keys::A:
		controls.slideLeft = true;
		break;
	case Keys::D:
		controls.slideRight = true;
		break;
	case Keys::L:
		controls.rollRight = true;
		break;
	case Keys::J:
		controls.rollLeft = true;
		break;
	case Keys::I:
		controls.pitchDown = true;
		break;
	case Keys::K:
		controls.pitchUp = true;
		break;
	case Keys::Q:
		controls.yawLeft = true;
		break;
	case Keys::E:
		controls.yawRight = true;
		break;
	}

}

private: System::Void OGLSolarSystem_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
{
	// check for numerical keys
	if (Char::IsDigit(e->KeyChar) == true)
	{
		// point at the specified planet
		float selected[3];
		solarSystem->getPlanetPosition(e->KeyChar - '0', selected);
		camera->pointAt(selected);

		// select that planet
		planetSelected = e->KeyChar - '0';
	}

	switch (e->KeyChar)
	{
	case '-':
		timeSpeed /= 2.0f; // half the rate of time passing
		break;
	case '=':
		timeSpeed *= 2.0f; // double the rate of time passing
		break;
	case '+':
		timeSpeed *= 2.0f; // double the rate of time passing
		break;
	case 'o':
		showOrbits = !showOrbits; // toggle show orbits
		break;
	case ',':
		camera->speedDown(); // slow down camera
		break;
	case '.':
		camera->speedUp(); // speed up camera
		break;
	}

	OGLupdateGUI();

}

private: System::Void OGLSolarSystem_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	switch (e->KeyCode)
	{
	case Keys::W:
		controls.moveForward = false;
		break;
	case Keys::S:
		controls.moveBackward = false;
		break;
	case Keys::A:
		controls.slideLeft = false;
		break;
	case Keys::D:
		controls.slideRight = false;
		break;
	case Keys::L:
		controls.rollRight = false;
		break;
	case Keys::J:
		controls.rollLeft = false;
		break;
	case Keys::I:
		controls.pitchDown = false;
		break;
	case Keys::K:
		controls.pitchUp = false;
		break;
	case Keys::Q:
		controls.yawLeft = false;
		break;
	case Keys::E:
		controls.yawRight = false;
		break;
	}

}
};
}
