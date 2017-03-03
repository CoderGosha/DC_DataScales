#pragma once


namespace Tablitsa {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for getVesyForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class getVesyForm : public System::Windows::Forms::Form
	{
	public:
		getVesyForm(List<String^>^ orcl)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			_orcl = orcl;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~getVesyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonGet;
	protected: 

	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::DataGridView^  dataGridView1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<String^>^ _orcl;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonGet = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonGet
			// 
			this->buttonGet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				));
			this->buttonGet->Location = System::Drawing::Point(475, 13);
			this->buttonGet->Name = L"buttonGet";
			this->buttonGet->Size = System::Drawing::Size(127, 23);
			this->buttonGet->TabIndex = 0;
			this->buttonGet->Text = L"Запрос";
			this->buttonGet->UseVisualStyleBackColor = true;
			this->buttonGet->Click += gcnew System::EventHandler(this, &getVesyForm::buttonGet_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Номер весов";
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				));
			this->textBox1->Location = System::Drawing::Point(92, 16);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
		));
			this->textBox2->Location = System::Drawing::Point(344, 16);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(227, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(111, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Количество записей";
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(15, 51);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(859, 432);
			this->dataGridView1->TabIndex = 5;
			// 
			// getVesyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(886, 495);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->buttonGet);
			this->Name = L"Form1";
			this->Text = L"Мониторинг";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonGet_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Запрос данных
try{
	Int32::Parse(this->textBox1->Text);

		String^ ConnectionString ="Data Source="+ _orcl[0] +";User ID="+ _orcl[1] +";Password="+ _orcl[2] +"";
		OracleConnection^ OC = gcnew OracleConnection(ConnectionString);
		OracleCommand^ cmd = gcnew OracleCommand("VESY_ZAP_PACK.Get_Ves", OC);
		cmd->CommandType = System::Data::CommandType::StoredProcedure;
		/*
		  --Получение N последних записей из таблицы логов по весам
			  procedure Get_Ves   
			   (
				Curs          in out TCursor,
				n             in     integer,
				vesy_nom_     in     vesy.vesy_nom%type
			   )
		*/
		cmd->Parameters->Add("Curs", Oracle::DataAccess::Client::OracleDbType::RefCursor, ParameterDirection::Output);
		cmd->Parameters->Add("n", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = Int32::Parse(textBox2->Text);
		cmd->Parameters->Add("vesy_nom", Oracle::DataAccess::Client::OracleDbType::Int32)->Value = Int32::Parse(this->textBox1->Text);



		try
		{
			OC->Open();
			OracleDataReader^ reader = cmd->ExecuteReader();
			//cmd->ExecuteNonQuery();
			int i = 0;
			DataTable^ table = gcnew DataTable();
			table->Load(reader);
			this->dataGridView1->DataSource = table;
			this->dataGridView1->ReadOnly = 1;	

		}
		catch (Oracle::DataAccess::Types::OracleTypeException::Exception ^e)
            { 
				System::Windows::Forms::MessageBox::Show(e->ToString());
            }
        finally
            {
				OC->Close(); 
            }

   }
	catch (Exception ^ e){
				 System::Windows::Forms::MessageBox::Show("Проверьте поля ввода");
			 }
}
			 };

			 }


