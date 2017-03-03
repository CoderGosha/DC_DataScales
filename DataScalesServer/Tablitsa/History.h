#pragma once


namespace Tablitsa {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace Oracle::DataAccess::Client;
	using namespace Oracle::DataAccess::Types;

	/// <summary>
	/// Summary for History
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class History : public System::Windows::Forms::Form
	{
	public:
		History(List<String^>^ orcl)
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
		~History()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::DateTimePicker^  dateTime1;
	private: System::Windows::Forms::DateTimePicker^  dateTime11;
	private: System::Windows::Forms::DateTimePicker^  dateTime22;
	private: System::Windows::Forms::DateTimePicker^  dateTime2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  btnSearch;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Label^  label4;

	protected: 

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dateTime1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTime11 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTime22 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTime2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Дата";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(60, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(21, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"с:";
			// 
			// dateTime1
			// 
			this->dateTime1->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTime1->Location = System::Drawing::Point(83, 9);
			this->dateTime1->Name = L"dateTime1";
			this->dateTime1->Size = System::Drawing::Size(87, 20);
			this->dateTime1->TabIndex = 2;
			// 
			// dateTime11
			// 
			this->dateTime11->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dateTime11->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->dateTime11->Location = System::Drawing::Point(176, 9);
			this->dateTime11->Name = L"dateTime11";
			this->dateTime11->ShowUpDown = true;
			this->dateTime11->Size = System::Drawing::Size(78, 20);
			this->dateTime11->TabIndex = 3;
			// 
			// dateTime22
			// 
			this->dateTime22->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dateTime22->Location = System::Drawing::Point(390, 10);
			this->dateTime22->Name = L"dateTime22";
			this->dateTime22->ShowUpDown = true;
			this->dateTime22->Size = System::Drawing::Size(77, 20);
			this->dateTime22->TabIndex = 5;
			// 
			// dateTime2
			// 
			this->dateTime2->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dateTime2->Location = System::Drawing::Point(297, 10);
			this->dateTime2->Name = L"dateTime2";
			this->dateTime2->Size = System::Drawing::Size(87, 20);
			this->dateTime2->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(466, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(107, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Номер весов";
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(579, 6);
			this->textBox1->MaxLength = 5;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 7;
			// 
			// btnSearch
			// 
			this->btnSearch->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btnSearch->Location = System::Drawing::Point(685, 6);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(165, 23);
			this->btnSearch->TabIndex = 8;
			this->btnSearch->Text = L"Поиск";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &History::btnSearch_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->ImeMode = System::Windows::Forms::ImeMode::On;
			this->dataGridView1->Location = System::Drawing::Point(16, 38);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(834, 370);
			this->dataGridView1->TabIndex = 9;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(260, 10);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 20);
			this->label4->TabIndex = 10;
			this->label4->Text = L"по:";
			// 
			// History
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(862, 420);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->dateTime22);
			this->Controls->Add(this->dateTime2);
			this->Controls->Add(this->dateTime11);
			this->Controls->Add(this->dateTime1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MinimumSize = System::Drawing::Size(870, 320);
			this->Name = L"History";
			this->Text = L"Мониторинг и диагностика";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {
//Выгружаем данные из Oracle
////	Проверяем подключеник к Оракл

	
 try{
	Int32::Parse(this->textBox1->Text);

		String^ ConnectionString ="Data Source="+ _orcl[0] +";User ID="+ _orcl[1] +";Password="+ _orcl[2] +"";
		OracleConnection^ OC = gcnew OracleConnection(ConnectionString);
		OracleCommand^ cmd = gcnew OracleCommand("VESY_ZAP_PACK.Get_History", OC);
		cmd->CommandType = System::Data::CommandType::StoredProcedure;
		String^ host = System::Net::Dns::GetHostName();
		// Получение ip-адреса.
		System::Net::IPAddress^ ip = System::Net::Dns::GetHostByName(host)->AddressList[0];

		String^ now = DateTime::Today.ToString();
		String^ begin = this->dateTime1->Value.Date.ToString("d")+ this->dateTime11->Value.ToString(" HH:mm:ss");
		String^ end = this->dateTime2->Value.Date.ToString("d")+ this->dateTime22->Value.ToString(" HH:mm:ss");
		//System::Windows::Forms::MessageBox::Show(begin);
		//System::Windows::Forms::MessageBox::Show(now);
		cmd->Parameters->Add("Curs", Oracle::DataAccess::Client::OracleDbType::RefCursor, ParameterDirection::Output);
		cmd->Parameters->Add("vesy_nom_", Oracle::DataAccess::Client::OracleDbType::Int32)->Value = Int32::Parse(this->textBox1->Text);
		cmd->Parameters->Add("vesy_ip_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = ip->ToString(); //ip->ToString();
		cmd->Parameters->Add("vesy_datetime_begin_", Oracle::DataAccess::Client::OracleDbType::TimeStamp)->Value = DateTime::Parse(begin);
		cmd->Parameters->Add("vesy_datetime_end_", Oracle::DataAccess::Client::OracleDbType::TimeStamp)->Value = DateTime::Parse(end);


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
				 System::Windows::Forms::MessageBox::Show("Проверьте поле номера весов");
			 }
}
			 };

}

