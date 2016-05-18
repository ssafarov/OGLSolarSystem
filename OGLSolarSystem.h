#pragma once

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
	private: System::Windows::Forms::MenuStrip^  menuStripMain;
	protected:

	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  miExit;

	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::Panel^  pControls;
	private: System::Windows::Forms::Panel^  pMainOGLViewport;

	private: System::Windows::Forms::CheckBox^  cbgpShowOrbits;
	private: System::Windows::Forms::Label^  lGlobalParams;
	private: System::Windows::Forms::Label^  lCurrentDateTimeTitle;
	private: System::Windows::Forms::Label^  lCurrentDateTime;
	private: System::Windows::Forms::Label^  lCross;
	private: System::Windows::Forms::Label^  lgpTimeScale;
	private: System::Windows::Forms::NumericUpDown^  nudgpTimeScale;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStripMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->miExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pControls = (gcnew System::Windows::Forms::Panel());
			this->lCross = (gcnew System::Windows::Forms::Label());
			this->lgpTimeScale = (gcnew System::Windows::Forms::Label());
			this->nudgpTimeScale = (gcnew System::Windows::Forms::NumericUpDown());
			this->cbgpShowOrbits = (gcnew System::Windows::Forms::CheckBox());
			this->lGlobalParams = (gcnew System::Windows::Forms::Label());
			this->pMainOGLViewport = (gcnew System::Windows::Forms::Panel());
			this->lCurrentDateTimeTitle = (gcnew System::Windows::Forms::Label());
			this->lCurrentDateTime = (gcnew System::Windows::Forms::Label());
			this->menuStripMain->SuspendLayout();
			this->pControls->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudgpTimeScale))->BeginInit();
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
			this->pControls->Controls->Add(this->lCross);
			this->pControls->Controls->Add(this->lgpTimeScale);
			this->pControls->Controls->Add(this->nudgpTimeScale);
			this->pControls->Controls->Add(this->cbgpShowOrbits);
			this->pControls->Controls->Add(this->lGlobalParams);
			this->pControls->Location = System::Drawing::Point(0, 27);
			this->pControls->Name = L"pControls";
			this->pControls->Size = System::Drawing::Size(271, 522);
			this->pControls->TabIndex = 1;
			// 
			// lCross
			// 
			this->lCross->AutoSize = true;
			this->lCross->Location = System::Drawing::Point(140, 61);
			this->lCross->Name = L"lCross";
			this->lCross->Size = System::Drawing::Size(12, 13);
			this->lCross->TabIndex = 50;
			this->lCross->Text = L"x";
			// 
			// lgpTimeScale
			// 
			this->lgpTimeScale->AutoSize = true;
			this->lgpTimeScale->Location = System::Drawing::Point(16, 61);
			this->lgpTimeScale->Name = L"lgpTimeScale";
			this->lgpTimeScale->Size = System::Drawing::Size(64, 13);
			this->lgpTimeScale->TabIndex = 49;
			this->lgpTimeScale->Text = L"Time scale :";
			// 
			// nudgpTimeScale
			// 
			this->nudgpTimeScale->Location = System::Drawing::Point(80, 59);
			this->nudgpTimeScale->Name = L"nudgpTimeScale";
			this->nudgpTimeScale->Size = System::Drawing::Size(55, 20);
			this->nudgpTimeScale->TabIndex = 48;
			this->nudgpTimeScale->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// cbgpShowOrbits
			// 
			this->cbgpShowOrbits->AutoSize = true;
			this->cbgpShowOrbits->Checked = true;
			this->cbgpShowOrbits->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbgpShowOrbits->Location = System::Drawing::Point(15, 36);
			this->cbgpShowOrbits->Name = L"cbgpShowOrbits";
			this->cbgpShowOrbits->Size = System::Drawing::Size(81, 17);
			this->cbgpShowOrbits->TabIndex = 3;
			this->cbgpShowOrbits->Text = L"Show orbits";
			this->cbgpShowOrbits->UseVisualStyleBackColor = true;
			this->cbgpShowOrbits->CheckedChanged += gcnew System::EventHandler(this, &OGLSolarSystem::checkBox1_CheckedChanged);
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
			this->pMainOGLViewport->Size = System::Drawing::Size(763, 486);
			this->pMainOGLViewport->TabIndex = 2;
			this->pMainOGLViewport->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &OGLSolarSystem::panel1_Paint);
			// 
			// lCurrentDateTimeTitle
			// 
			this->lCurrentDateTimeTitle->AutoSize = true;
			this->lCurrentDateTimeTitle->Location = System::Drawing::Point(277, 37);
			this->lCurrentDateTimeTitle->Name = L"lCurrentDateTimeTitle";
			this->lCurrentDateTimeTitle->Size = System::Drawing::Size(33, 13);
			this->lCurrentDateTimeTitle->TabIndex = 6;
			this->lCurrentDateTimeTitle->Text = L"Time:";
			this->lCurrentDateTimeTitle->Click += gcnew System::EventHandler(this, &OGLSolarSystem::label7_Click);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudgpTimeScale))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
	}
private: System::Void OGLSolarSystem_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
