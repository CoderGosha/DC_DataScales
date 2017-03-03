#pragma once

#include "WE2110.h"

namespace EmulatorVesyWE2110 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

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

			vesy = gcnew List<CWE2110^>();
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


			for each(CWE2110^ elem in vesy ) {
				delete elem;
			}
		}
	private: System::Windows::Forms::Button^  VesyStart;
	protected: 
	private: System::Windows::Forms::Button^  VesyStop;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  CountVesy;
	private: System::Windows::Forms::TextBox^  Tcp_Port_Start;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timerUi;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		List<CWE2110^>^ vesy;
		Random^ rand;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->VesyStart = (gcnew System::Windows::Forms::Button());
			this->VesyStop = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->CountVesy = (gcnew System::Windows::Forms::TextBox());
			this->Tcp_Port_Start = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->timerUi = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// VesyStart
			// 
			this->VesyStart->Location = System::Drawing::Point(411, 16);
			this->VesyStart->Name = L"VesyStart";
			this->VesyStart->Size = System::Drawing::Size(75, 23);
			this->VesyStart->TabIndex = 0;
			this->VesyStart->Text = L"START";
			this->VesyStart->UseVisualStyleBackColor = true;
			this->VesyStart->Click += gcnew System::EventHandler(this, &Form1::VesyStart_Click);
			// 
			// VesyStop
			// 
			this->VesyStop->Location = System::Drawing::Point(506, 16);
			this->VesyStop->Name = L"VesyStop";
			this->VesyStop->Size = System::Drawing::Size(75, 23);
			this->VesyStop->TabIndex = 1;
			this->VesyStop->Text = L"STOP";
			this->VesyStop->UseVisualStyleBackColor = true;
			this->VesyStop->Click += gcnew System::EventHandler(this, &Form1::VesyStop_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Count";
			// 
			// CountVesy
			// 
			this->CountVesy->Location = System::Drawing::Point(54, 18);
			this->CountVesy->Name = L"CountVesy";
			this->CountVesy->Size = System::Drawing::Size(100, 20);
			this->CountVesy->TabIndex = 3;
			this->CountVesy->Text = L"5";
			// 
			// Tcp_Port_Start
			// 
			this->Tcp_Port_Start->Location = System::Drawing::Point(276, 18);
			this->Tcp_Port_Start->Name = L"Tcp_Port_Start";
			this->Tcp_Port_Start->Size = System::Drawing::Size(84, 20);
			this->Tcp_Port_Start->TabIndex = 4;
			this->Tcp_Port_Start->Text = L"32000";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(182, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"TCP Port Start";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->richTextBox1->Location = System::Drawing::Point(1, 341);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(664, 96);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(1, 54);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->Size = System::Drawing::Size(664, 278);
			this->dataGridView1->TabIndex = 7;
			// 
			// timerUi
			// 
			this->timerUi->Enabled = true;
			this->timerUi->Interval = 200;
			this->timerUi->Tick += gcnew System::EventHandler(this, &Form1::timerUi_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(665, 439);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Tcp_Port_Start);
			this->Controls->Add(this->CountVesy);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->VesyStop);
			this->Controls->Add(this->VesyStart);
			this->Name = L"Form1";
			this->Text = L"EmulatorMicrosim v-1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void VesyStart_Click(System::Object^  sender, System::EventArgs^  e) {
		//Создаем обекты новых весов :)
				 rand = gcnew Random();
				 int count = 0;
				 try{
					 count = Int32::Parse(CountVesy->Text);
					}
				 catch (Exception ^e){
					return;
				 }

				 for each(CWE2110^ elem in vesy ) {
					 delete elem;
				 }

				 vesy = gcnew List<CWE2110^>();
				 for (int i = 0; i < count; i++) {
					 Int32 port = Int32::Parse(Tcp_Port_Start->Text) + i;
					vesy->Add(gcnew CWE2110 (i+1, "EM", "localhost", port.ToString(), 800, rand));

				 }


			 }
private: System::Void timerUi_Tick(System::Object^  sender, System::EventArgs^  e) {
//Обновление таблиц
		int i = 0;

		//
		int CountVesZero = 0;

		if (vesy->Count == 0) {
				
			dataGridView1->RowCount =1;
			dataGridView1->Enabled = false;

		}
		else {
			dataGridView1->RowCount = vesy->Count;
			dataGridView1->Enabled = true;;


		 }
			 for each(CWE2110^ elem in vesy ) {
					

				 dataGridView1->Rows[i]->Cells[0]->Value = elem-> NPP.ToString();
				 dataGridView1->Rows[i]->Cells[1]->Value = elem-> NameVesy;

				 dataGridView1->Rows[i]->Cells[2]->Value = elem->TcpIp ;
				 dataGridView1->Rows[i]->Cells[3]->Value = elem->TcpPort;
				 dataGridView1->Rows[i]->Cells[4]->Value = elem->RawString ;
				 dataGridView1->Rows[i]->Cells[5]->Value = elem->TimeOutGenerateRaw;
				 dataGridView1->Rows[i]->Cells[6]->Value = elem->DateLastRaw;
				
				 i++;
				 if ((elem->VES == "0") || (elem->RawString == "NULL RAW")) {
					CountVesZero++;
					elem->UpdateRandom(rand);
				 }

		}

		if (( CountVesZero == i ) && (CountVesZero != 0)){
			rand = gcnew Random();

			//MessageBox::Show("as");
			 }
			 


		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 dataGridView1->ColumnCount = 7;
		 dataGridView1->Columns[0]->Width = 25;
		 dataGridView1->Columns[0]->HeaderText = "№";
		 dataGridView1->Columns[1]->HeaderText = "Name";
		 dataGridView1->Columns[1]->Width = 50;
		 dataGridView1->Columns[2]->HeaderText = "IP";
		 dataGridView1->Columns[2]->Width = 90;
		 dataGridView1->Columns[3]->HeaderText = "PORT";
		 dataGridView1->Columns[3]->Width = 50;
		 dataGridView1->Columns[4]->HeaderText = "RAW";
		 dataGridView1->Columns[4]->Width = 220;
		 dataGridView1->Columns[5]->HeaderText = "TIME_GEN_RAW";
		 dataGridView1->Columns[5]->Width = 50;
		 dataGridView1->Columns[6]->HeaderText = "DATE_LAST_GENS";
		 dataGridView1->Columns[6]->Width = 120;
		 }
private: System::Void VesyStop_Click(System::Object^  sender, System::EventArgs^  e) {
	for each(CWE2110^ elem in vesy ) {
		delete elem;
	}
			
		 }
};
}

