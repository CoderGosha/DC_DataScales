#pragma once


namespace licenseGenerDataScales {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
using namespace System::Security::Cryptography;
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Generate;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;

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
			this->Generate = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Generate
			// 
			this->Generate->Location = System::Drawing::Point(431, 24);
			this->Generate->Name = L"Generate";
			this->Generate->Size = System::Drawing::Size(75, 23);
			this->Generate->TabIndex = 0;
			this->Generate->Text = L"Generate";
			this->Generate->UseVisualStyleBackColor = true;
			this->Generate->Click += gcnew System::EventHandler(this, &Form1::Generate_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(92, 24);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 21);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(13, 73);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(539, 21);
			this->textBox2->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Count License";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(564, 121);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Generate);
			this->Name = L"Form1";
			this->Text = L"LicenseGenerateDataScales";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: String^ getHashSha256(String^ in){
			SHA256 ^ mySHA256 = SHA256Managed::Create();
			array<Byte>^ hashValue;
			String^ hashValuseString;
			hashValue = mySHA256->ComputeHash( System::Text::Encoding::UTF8->GetBytes(in));

			for (int i = 0; i < hashValue->Length; i++){
				hashValuseString += hashValue[i].ToString();
			}
			
			return hashValuseString;
		 }

	private: System::Void Generate_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 Int32::Parse(textBox1->Text);
				 }

				 catch (Exception ^e) {
					 MessageBox::Show("¬ведите корректное знеачение");
					 return;
				 }

				 String^ count = textBox1->Text;
				
			
				 String^ hashValuseString = count;

				 for (int i = 0; i < 10; i++)
					hashValuseString = getHashSha256(hashValuseString);

				 textBox2->Text = hashValuseString;
			 }
	};
}

