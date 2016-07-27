#pragma once

namespace OGLSolarSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for OGLSSAbout
	/// </summary>
	public ref class OGLSSAbout : public System::Windows::Forms::Form
	{
	public:
		OGLSSAbout(void)
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
		~OGLSSAbout()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::PictureBox^  pbOGLLogo;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  tbHintAbout;
	private: System::Windows::Forms::Button^  bCancel;
	private: System::Windows::Forms::LinkLabel^  llInfo;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Label^  label4;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(OGLSSAbout::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pbOGLLogo = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbHintAbout = (gcnew System::Windows::Forms::TextBox());
			this->bCancel = (gcnew System::Windows::Forms::Button());
			this->llInfo = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOGLLogo))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 20.75F));
			this->label1->Location = System::Drawing::Point(12, 120);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(161, 33);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Solar System";
			// 
			// pbOGLLogo
			// 
			this->pbOGLLogo->BackColor = System::Drawing::SystemColors::Control;
			this->pbOGLLogo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pbOGLLogo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbOGLLogo.Image")));
			this->pbOGLLogo->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbOGLLogo.InitialImage")));
			this->pbOGLLogo->Location = System::Drawing::Point(12, 12);
			this->pbOGLLogo->Name = L"pbOGLLogo";
			this->pbOGLLogo->Size = System::Drawing::Size(168, 105);
			this->pbOGLLogo->TabIndex = 1;
			this->pbOGLLogo->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(15, 188);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(149, 15);
			this->label2->TabIndex = 2;
			this->label2->Text = L"by Sergey Safarov (c) 2016";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 16.75F));
			this->label3->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label3->Location = System::Drawing::Point(13, 153);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(107, 26);
			this->label3->TabIndex = 3;
			this->label3->Text = L"v. 0.5 beta";
			// 
			// tbHintAbout
			// 
			this->tbHintAbout->Location = System::Drawing::Point(209, 39);
			this->tbHintAbout->Multiline = true;
			this->tbHintAbout->Name = L"tbHintAbout";
			this->tbHintAbout->ReadOnly = true;
			this->tbHintAbout->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->tbHintAbout->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbHintAbout->Size = System::Drawing::Size(290, 164);
			this->tbHintAbout->TabIndex = 4;
			this->tbHintAbout->Text = resources->GetString(L"tbHintAbout.Text");
			// 
			// bCancel
			// 
			this->bCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->bCancel->Location = System::Drawing::Point(424, 220);
			this->bCancel->Name = L"bCancel";
			this->bCancel->Size = System::Drawing::Size(75, 23);
			this->bCancel->TabIndex = 5;
			this->bCancel->Text = L"Close";
			this->bCancel->UseVisualStyleBackColor = true;
			// 
			// llInfo
			// 
			this->llInfo->AutoSize = true;
			this->llInfo->Location = System::Drawing::Point(15, 209);
			this->llInfo->Name = L"llInfo";
			this->llInfo->Size = System::Drawing::Size(124, 13);
			this->llInfo->TabIndex = 6;
			this->llInfo->TabStop = true;
			this->llInfo->Text = L"http://sergeysafarov.info";
			this->llInfo->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &OGLSSAbout::llInfo_LinkClicked);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(15, 230);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(132, 13);
			this->linkLabel1->TabIndex = 7;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"inbox@sergeysafarov.com";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &OGLSSAbout::linkLabel1_LinkClicked);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(206, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(268, 15);
			this->label4->TabIndex = 8;
			this->label4->Text = L"This software is free and goes under MIT license";
			// 
			// OGLSSAbout
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->bCancel;
			this->ClientSize = System::Drawing::Size(526, 255);
			this->ControlBox = false;
			this->Controls->Add(this->label4);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->llInfo);
			this->Controls->Add(this->bCancel);
			this->Controls->Add(this->tbHintAbout);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pbOGLLogo);
			this->Controls->Add(this->label1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->KeyPreview = true;
			this->Name = L"OGLSSAbout";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Sergei Safarov`s OpenGL Solar System. About";
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &OGLSSAbout::OGLSSAbout_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbOGLLogo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void OGLSSAbout_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		if (e->KeyChar == (char)Keys::Escape)
		{
			this->Close();
		}
	}
private: System::Void llInfo_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	System::Diagnostics::Process::Start("http://sergeysafarov.info/");
}
private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	System::Diagnostics::Process::Start("mailto:inbox@sergeysafarov.com?Subject=Request%20from%20solar%20system%20application&Body=Hello!");
}
};
}
