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


		private: System::Windows::Forms::Label^  lCurrentDateTimeTitle;
		private: System::Windows::Forms::Label^  lCurrentDateTime;


		private: System::Windows::Forms::Label^  lParamsTimeScale;


		private: System::Windows::Forms::Timer^  timer1;

		private:
			HDC		_hDC;	// Private GDI Device Context
			HGLRC	_hRC;	// Get handle to panel on form and call initialization function						

			// These control the simulation of time line and scale
			double timeScale;
			double timeSpeed;

			bool light;
			bool showOrbits;
			int planetSelected;

		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::Label^  lPosZ;
		private: System::Windows::Forms::Label^  lPosY;
		private: System::Windows::Forms::Label^  lPosX;
		private: System::Windows::Forms::Label^  label6;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::CheckBox^  cbParamsShowOrbits;
		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::ComboBox^  cbTimeScale;
		private: System::Windows::Forms::Label^  lRoll;
		private: System::Windows::Forms::Label^  lHeading;
		private: System::Windows::Forms::Label^  lPitch;
		private: System::Windows::Forms::Label^  label7;
		private: System::Windows::Forms::Label^  label8;
		private: System::Windows::Forms::Label^  label9;
		private: System::Windows::Forms::Label^  lHeadingZ;

		private: System::Windows::Forms::Label^  lHeadingY;

		private: System::Windows::Forms::Label^  lHeadingX;

		private: System::Windows::Forms::Label^  label13;
		private: System::Windows::Forms::Label^  label14;
		private: System::Windows::Forms::Label^  label15;
		private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  gbSolarSystemSettings;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::CheckBox^  cbLightSwitch;

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

			double viewPortAspectRatio;


			Texture* starsTexture;
			Texture* sunTexture;
			Texture* mercuryTexture;
			Texture* venusTexture;
			Texture* earthTexture;
			Texture* moonTexture1;
			Texture* moonTexture2;
			Texture* moonTexture3;
			Texture* moonTexture4;
			Texture* marsTexture;
			Texture* saturnTexture;
			Texture* jupiterTexture;
			Texture* neptuneTexture;
			Texture* uranusTexture;
			Texture* plutoTexture;

			Camera* camera;	// The instance of the camera

			SolarSystem* solarSystem; // The main instance of the solar system












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
			this->gbSolarSystemSettings = (gcnew System::Windows::Forms::GroupBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->cbLightSwitch = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->cbParamsShowOrbits = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lRoll = (gcnew System::Windows::Forms::Label());
			this->lHeading = (gcnew System::Windows::Forms::Label());
			this->lPitch = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->lHeadingZ = (gcnew System::Windows::Forms::Label());
			this->lHeadingY = (gcnew System::Windows::Forms::Label());
			this->lHeadingX = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lPosZ = (gcnew System::Windows::Forms::Label());
			this->lPosY = (gcnew System::Windows::Forms::Label());
			this->lPosX = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lParamsTimeScale = (gcnew System::Windows::Forms::Label());
			this->pMainOGLViewport = (gcnew System::Windows::Forms::Panel());
			this->lCurrentDateTimeTitle = (gcnew System::Windows::Forms::Label());
			this->lCurrentDateTime = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->cbTimeScale = (gcnew System::Windows::Forms::ComboBox());
			this->menuStripMain->SuspendLayout();
			this->pControls->SuspendLayout();
			this->gbSolarSystemSettings->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
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
			this->pControls->Controls->Add(this->gbSolarSystemSettings);
			this->pControls->Controls->Add(this->groupBox2);
			this->pControls->Controls->Add(this->groupBox1);
			this->pControls->Location = System::Drawing::Point(0, 27);
			this->pControls->Name = L"pControls";
			this->pControls->Size = System::Drawing::Size(297, 584);
			this->pControls->TabIndex = 1;
			// 
			// gbSolarSystemSettings
			// 
			this->gbSolarSystemSettings->Controls->Add(this->label38);
			this->gbSolarSystemSettings->Controls->Add(this->label39);
			this->gbSolarSystemSettings->Controls->Add(this->label37);
			this->gbSolarSystemSettings->Controls->Add(this->label36);
			this->gbSolarSystemSettings->Controls->Add(this->label35);
			this->gbSolarSystemSettings->Controls->Add(this->label34);
			this->gbSolarSystemSettings->Controls->Add(this->label33);
			this->gbSolarSystemSettings->Controls->Add(this->label32);
			this->gbSolarSystemSettings->Controls->Add(this->label31);
			this->gbSolarSystemSettings->Controls->Add(this->label30);
			this->gbSolarSystemSettings->Controls->Add(this->label29);
			this->gbSolarSystemSettings->Controls->Add(this->label28);
			this->gbSolarSystemSettings->Controls->Add(this->label27);
			this->gbSolarSystemSettings->Controls->Add(this->label26);
			this->gbSolarSystemSettings->Controls->Add(this->label25);
			this->gbSolarSystemSettings->Controls->Add(this->label24);
			this->gbSolarSystemSettings->Controls->Add(this->label23);
			this->gbSolarSystemSettings->Controls->Add(this->label22);
			this->gbSolarSystemSettings->Controls->Add(this->label21);
			this->gbSolarSystemSettings->Controls->Add(this->label20);
			this->gbSolarSystemSettings->Controls->Add(this->label19);
			this->gbSolarSystemSettings->Controls->Add(this->label18);
			this->gbSolarSystemSettings->Controls->Add(this->label17);
			this->gbSolarSystemSettings->Controls->Add(this->label16);
			this->gbSolarSystemSettings->Controls->Add(this->label12);
			this->gbSolarSystemSettings->Controls->Add(this->label11);
			this->gbSolarSystemSettings->Controls->Add(this->label10);
			this->gbSolarSystemSettings->Controls->Add(this->label2);
			this->gbSolarSystemSettings->Location = System::Drawing::Point(8, 203);
			this->gbSolarSystemSettings->Name = L"gbSolarSystemSettings";
			this->gbSolarSystemSettings->Size = System::Drawing::Size(279, 340);
			this->gbSolarSystemSettings->TabIndex = 77;
			this->gbSolarSystemSettings->TabStop = false;
			this->gbSolarSystemSettings->Text = L"Solar System Data";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label38->Location = System::Drawing::Point(80, 311);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(26, 13);
			this->label38->TabIndex = 116;
			this->label38->Text = L"Sun";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(13, 311);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(31, 13);
			this->label39->TabIndex = 115;
			this->label39->Text = L"Pluto";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(80, 289);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(26, 13);
			this->label37->TabIndex = 114;
			this->label37->Text = L"Sun";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(80, 266);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(26, 13);
			this->label36->TabIndex = 113;
			this->label36->Text = L"Sun";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(80, 243);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(26, 13);
			this->label35->TabIndex = 112;
			this->label35->Text = L"Sun";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(80, 220);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(26, 13);
			this->label34->TabIndex = 111;
			this->label34->Text = L"Sun";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(80, 197);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(26, 13);
			this->label33->TabIndex = 110;
			this->label33->Text = L"Sun";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(80, 174);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(26, 13);
			this->label32->TabIndex = 109;
			this->label32->Text = L"Sun";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(80, 151);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(26, 13);
			this->label31->TabIndex = 108;
			this->label31->Text = L"Sun";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(80, 128);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(26, 13);
			this->label30->TabIndex = 107;
			this->label30->Text = L"Sun";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(80, 105);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(26, 13);
			this->label29->TabIndex = 106;
			this->label29->Text = L"Sun";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(80, 82);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(26, 13);
			this->label28->TabIndex = 105;
			this->label28->Text = L"Sun";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(80, 59);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(26, 13);
			this->label27->TabIndex = 104;
			this->label27->Text = L"Sun";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(80, 36);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(26, 13);
			this->label26->TabIndex = 103;
			this->label26->Text = L"Sun";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(26, 197);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(42, 13);
			this->label25->TabIndex = 102;
			this->label25->Text = L"Deimos";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(26, 174);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(43, 13);
			this->label24->TabIndex = 101;
			this->label24->Text = L"Phobos";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(13, 289);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(41, 13);
			this->label23->TabIndex = 100;
			this->label23->Text = L"Uranus";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(13, 266);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(48, 13);
			this->label22->TabIndex = 99;
			this->label22->Text = L"Neptune";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(13, 243);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(41, 13);
			this->label21->TabIndex = 98;
			this->label21->Text = L"Juniper";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(13, 220);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(38, 13);
			this->label20->TabIndex = 97;
			this->label20->Text = L"Saturn";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(13, 151);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(30, 13);
			this->label19->TabIndex = 96;
			this->label19->Text = L"Mars";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(26, 128);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(34, 13);
			this->label18->TabIndex = 95;
			this->label18->Text = L"Moon";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(13, 105);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(32, 13);
			this->label17->TabIndex = 94;
			this->label17->Text = L"Earth";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(13, 82);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(37, 13);
			this->label16->TabIndex = 93;
			this->label16->Text = L"Venus";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(13, 59);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(45, 13);
			this->label12->TabIndex = 92;
			this->label12->Text = L"Mercury";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(13, 36);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(26, 13);
			this->label11->TabIndex = 91;
			this->label11->Text = L"Sun";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(157, 16);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(77, 13);
			this->label10->TabIndex = 90;
			this->label10->Text = L"Velocity (km/s)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(80, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 89;
			this->label2->Text = L"Mass (kg)";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->cbLightSwitch);
			this->groupBox2->Controls->Add(this->checkBox1);
			this->groupBox2->Controls->Add(this->cbParamsShowOrbits);
			this->groupBox2->Location = System::Drawing::Point(8, 10);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(279, 66);
			this->groupBox2->TabIndex = 76;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Global settings";
			// 
			// cbLightSwitch
			// 
			this->cbLightSwitch->AutoSize = true;
			this->cbLightSwitch->Checked = true;
			this->cbLightSwitch->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbLightSwitch->Location = System::Drawing::Point(99, 19);
			this->cbLightSwitch->Name = L"cbLightSwitch";
			this->cbLightSwitch->Size = System::Drawing::Size(105, 17);
			this->cbLightSwitch->TabIndex = 6;
			this->cbLightSwitch->Text = L"Lightning On/Off";
			this->cbLightSwitch->UseVisualStyleBackColor = true;
			this->cbLightSwitch->CheckedChanged += gcnew System::EventHandler(this, &OGLSolarSystem::cbLightSwitch_CheckedChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Enabled = false;
			this->checkBox1->Location = System::Drawing::Point(9, 42);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(81, 17);
			this->checkBox1->TabIndex = 5;
			this->checkBox1->Text = L"Use Gravity";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// cbParamsShowOrbits
			// 
			this->cbParamsShowOrbits->AutoSize = true;
			this->cbParamsShowOrbits->Checked = true;
			this->cbParamsShowOrbits->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbParamsShowOrbits->Location = System::Drawing::Point(9, 19);
			this->cbParamsShowOrbits->Name = L"cbParamsShowOrbits";
			this->cbParamsShowOrbits->Size = System::Drawing::Size(81, 17);
			this->cbParamsShowOrbits->TabIndex = 4;
			this->cbParamsShowOrbits->Text = L"Show orbits";
			this->cbParamsShowOrbits->UseVisualStyleBackColor = true;
			this->cbParamsShowOrbits->CheckedChanged += gcnew System::EventHandler(this, &OGLSolarSystem::cbParamsShowOrbits_CheckedChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->lRoll);
			this->groupBox1->Controls->Add(this->lHeading);
			this->groupBox1->Controls->Add(this->lPitch);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->lHeadingZ);
			this->groupBox1->Controls->Add(this->lHeadingY);
			this->groupBox1->Controls->Add(this->lHeadingX);
			this->groupBox1->Controls->Add(this->label13);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->label15);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->lPosZ);
			this->groupBox1->Controls->Add(this->lPosY);
			this->groupBox1->Controls->Add(this->lPosX);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Location = System::Drawing::Point(8, 82);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(279, 115);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Camera Settings";
			// 
			// lRoll
			// 
			this->lRoll->AutoSize = true;
			this->lRoll->Location = System::Drawing::Point(215, 99);
			this->lRoll->Name = L"lRoll";
			this->lRoll->Size = System::Drawing::Size(44, 13);
			this->lRoll->TabIndex = 93;
			this->lRoll->Text = L"Z-coord";
			// 
			// lHeading
			// 
			this->lHeading->AutoSize = true;
			this->lHeading->Location = System::Drawing::Point(136, 99);
			this->lHeading->Name = L"lHeading";
			this->lHeading->Size = System::Drawing::Size(44, 13);
			this->lHeading->TabIndex = 92;
			this->lHeading->Text = L"Y-coord";
			// 
			// lPitch
			// 
			this->lPitch->AutoSize = true;
			this->lPitch->Location = System::Drawing::Point(37, 99);
			this->lPitch->Name = L"lPitch";
			this->lPitch->Size = System::Drawing::Size(44, 13);
			this->lPitch->TabIndex = 91;
			this->lPitch->Text = L"X-coord";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(190, 99);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(28, 13);
			this->label7->TabIndex = 90;
			this->label7->Text = L"Roll:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(89, 99);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(50, 13);
			this->label8->TabIndex = 89;
			this->label8->Text = L"Heading:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 99);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(34, 13);
			this->label9->TabIndex = 88;
			this->label9->Text = L"Pitch:";
			// 
			// lHeadingZ
			// 
			this->lHeadingZ->AutoSize = true;
			this->lHeadingZ->Location = System::Drawing::Point(204, 70);
			this->lHeadingZ->Name = L"lHeadingZ";
			this->lHeadingZ->Size = System::Drawing::Size(44, 13);
			this->lHeadingZ->TabIndex = 87;
			this->lHeadingZ->Text = L"Z-coord";
			// 
			// lHeadingY
			// 
			this->lHeadingY->AutoSize = true;
			this->lHeadingY->Location = System::Drawing::Point(204, 49);
			this->lHeadingY->Name = L"lHeadingY";
			this->lHeadingY->Size = System::Drawing::Size(44, 13);
			this->lHeadingY->TabIndex = 86;
			this->lHeadingY->Text = L"Y-coord";
			// 
			// lHeadingX
			// 
			this->lHeadingX->AutoSize = true;
			this->lHeadingX->Location = System::Drawing::Point(204, 26);
			this->lHeadingX->Name = L"lHeadingX";
			this->lHeadingX->Size = System::Drawing::Size(44, 13);
			this->lHeadingX->TabIndex = 85;
			this->lHeadingX->Text = L"X-coord";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(193, 70);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(14, 13);
			this->label13->TabIndex = 84;
			this->label13->Text = L"Z";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(193, 49);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(14, 13);
			this->label14->TabIndex = 83;
			this->label14->Text = L"Y";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(193, 26);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(14, 13);
			this->label15->TabIndex = 82;
			this->label15->Text = L"X";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(136, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 81;
			this->label1->Text = L"Looking At";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(160, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 22);
			this->button1->TabIndex = 80;
			this->button1->Text = L"Reset to default";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// lPosZ
			// 
			this->lPosZ->AutoSize = true;
			this->lPosZ->Location = System::Drawing::Point(64, 69);
			this->lPosZ->Name = L"lPosZ";
			this->lPosZ->Size = System::Drawing::Size(44, 13);
			this->lPosZ->TabIndex = 79;
			this->lPosZ->Text = L"Z-coord";
			// 
			// lPosY
			// 
			this->lPosY->AutoSize = true;
			this->lPosY->Location = System::Drawing::Point(64, 48);
			this->lPosY->Name = L"lPosY";
			this->lPosY->Size = System::Drawing::Size(44, 13);
			this->lPosY->TabIndex = 78;
			this->lPosY->Text = L"Y-coord";
			// 
			// lPosX
			// 
			this->lPosX->AutoSize = true;
			this->lPosX->Location = System::Drawing::Point(64, 25);
			this->lPosX->Name = L"lPosX";
			this->lPosX->Size = System::Drawing::Size(44, 13);
			this->lPosX->TabIndex = 77;
			this->lPosX->Text = L"X-coord";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(53, 69);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(14, 13);
			this->label6->TabIndex = 76;
			this->label6->Text = L"Z";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(53, 48);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 75;
			this->label5->Text = L"Y";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(53, 25);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(14, 13);
			this->label4->TabIndex = 74;
			this->label4->Text = L"X";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 25);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(44, 13);
			this->label3->TabIndex = 73;
			this->label3->Text = L"Position";
			// 
			// lParamsTimeScale
			// 
			this->lParamsTimeScale->AutoSize = true;
			this->lParamsTimeScale->Location = System::Drawing::Point(305, 37);
			this->lParamsTimeScale->Name = L"lParamsTimeScale";
			this->lParamsTimeScale->Size = System::Drawing::Size(61, 13);
			this->lParamsTimeScale->TabIndex = 49;
			this->lParamsTimeScale->Text = L"Time scale:";
			// 
			// pMainOGLViewport
			// 
			this->pMainOGLViewport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->pMainOGLViewport->AutoScroll = true;
			this->pMainOGLViewport->Location = System::Drawing::Point(303, 63);
			this->pMainOGLViewport->Name = L"pMainOGLViewport";
			this->pMainOGLViewport->Size = System::Drawing::Size(732, 548);
			this->pMainOGLViewport->TabIndex = 2;
			// 
			// lCurrentDateTimeTitle
			// 
			this->lCurrentDateTimeTitle->AutoSize = true;
			this->lCurrentDateTimeTitle->Location = System::Drawing::Point(431, 37);
			this->lCurrentDateTimeTitle->Name = L"lCurrentDateTimeTitle";
			this->lCurrentDateTimeTitle->Size = System::Drawing::Size(33, 13);
			this->lCurrentDateTimeTitle->TabIndex = 6;
			this->lCurrentDateTimeTitle->Text = L"Time:";
			// 
			// lCurrentDateTime
			// 
			this->lCurrentDateTime->AutoSize = true;
			this->lCurrentDateTime->Location = System::Drawing::Point(459, 37);
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
			// cbTimeScale
			// 
			this->cbTimeScale->Cursor = System::Windows::Forms::Cursors::Default;
			this->cbTimeScale->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbTimeScale->FormattingEnabled = true;
			this->cbTimeScale->Items->AddRange(gcnew cli::array< System::Object^  >(17) {
				L"0.1", L"0.2", L"0.3", L"0.4", L"0.5", L"0.6",
					L"0.7", L"0.8", L"0.9", L"1.0", L"1.1", L"1.2", L"1.5", L"2.0", L"3.0", L"5.0", L"10.0"
			});
			this->cbTimeScale->Location = System::Drawing::Point(365, 34);
			this->cbTimeScale->Name = L"cbTimeScale";
			this->cbTimeScale->Size = System::Drawing::Size(49, 21);
			this->cbTimeScale->TabIndex = 50;
			this->cbTimeScale->SelectedIndexChanged += gcnew System::EventHandler(this, &OGLSolarSystem::cbTimeScale_SelectedIndexChanged);
			// 
			// OGLSolarSystem
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1040, 616);
			this->Controls->Add(this->cbTimeScale);
			this->Controls->Add(this->lCurrentDateTime);
			this->Controls->Add(this->lCurrentDateTimeTitle);
			this->Controls->Add(this->pMainOGLViewport);
			this->Controls->Add(this->pControls);
			this->Controls->Add(this->menuStripMain);
			this->Controls->Add(this->lParamsTimeScale);
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
			this->gbSolarSystemSettings->ResumeLayout(false);
			this->gbSolarSystemSettings->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
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
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		camera->reset();
	}

private: System::Void OGLSolarSystem_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

	switch (e->KeyCode)
	{
	case Keys::S:
		controls.moveForward = true;
		break;
	case Keys::W:
		controls.moveBackward = true;
		break;
	case Keys::D:
		controls.slideLeft = true;
		break;
	case Keys::A:
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
	case '`':
		light = !light; // toggle show light On / Off
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
	case Keys::S:
		controls.moveForward = false;
		break;
	case Keys::W:
		controls.moveBackward = false;
		break;
	case Keys::D:
		controls.slideLeft = false;
		break;
	case Keys::A:
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
private: System::Void cbTimeScale_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
{
	timeSpeed *= TIME_SCALE_MULTIPLIERS[cbTimeScale->SelectedIndex];
}
private: System::Void cbParamsShowOrbits_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	showOrbits = cbParamsShowOrbits->Checked;
}
private: System::Void cbLightSwitch_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
{
	light = cbLightSwitch->Checked;
}
};
}
