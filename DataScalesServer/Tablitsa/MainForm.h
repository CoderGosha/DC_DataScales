#pragma once

#include "StdAfx.h"

#include "Weight.h"
#include "AdminForm.h"
#include "TCPServer.h"
#include "History.h"
#include "getVesyForm.h"
#include "InputBox.h"
//#include "pugixml.hpp"
#include "TCPSetverToOracle.h"
#include "DataTrack.h"


namespace Tablitsa {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Collections::Generic;
	using namespace System::Net;
	using namespace System::Security::Cryptography;
	using namespace System::Globalization;
	using namespace System::Xml;


	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			try{	

				CheckWorkedBool = true;
				CheckWorkedThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::CheckWorked));
				CheckWorkedThread->Start();
				//
				//TODO: Add the constructor code here
				//
				//array<String^>^ serialPorts = nullptr;
				//serialPorts = SerialPort::GetPortNames();
				GenerateLicenceList();
				CountLicense = 1;

				this->timer1->Interval = 300;
				this->timer1->Enabled = 1;
				toolStripLabel1->Text = "Update UI: " + this->timer1->Interval.ToString();

				this->Text += " : Start time: " + DateTime::Now.ToString();
				_weight = gcnew List<List<String^>^>();
				_weightJaguar = gcnew List<int>();
				_dataTrackListAll =gcnew List<List<String^>^>();
				_oracleList = gcnew List<String^>();
				_weight_list = gcnew List<CWeight^>();
				dtreckList = gcnew List<CDataTrack^>();
				_buttonControl = gcnew List<bool>();

				_weightJaguar->Add(0);
				_weightJaguar->Add(0);
				_weightJaguar->Add(0);

				_weightJaguar->Add(0);
				_weightJaguar->Add(0);
				_weightJaguar->Add(0);

				_weightJaguar->Add(0);
				_weightJaguar->Add(0);
				_weightJaguar->Add(0);

				if (this->LoadXml())
				{


				}

				else
				{
					MessageBox::Show("Файл настроек не найден! Настройки заданы по умолчанию.");



					//Зададим настройки для ОРАКЛ по умолчанию

					_oracleList->Add(""); //DATA Source
					_oracleList->Add(""); //User
					_oracleList->Add(""); //Pass
					_oracleList->Add(""); //TimeSend mc
					_oracleList->Add("true"); //On


					currentHashPassword = getHashSha256("1234");
					//
					_buttonControl->Add(false);
					_buttonControl->Add(false);
					_buttonControl->Add(false);
					_buttonControl->Add(false);


				}

				int i = 0;
				for each(List<String^>^ elem in _weight ) {

					//Проверим лицензию

					i++;
					if (i > CountLicense)
						break;

					bool vesKg = 1;
					if (elem[12] == "КГ") 
						vesKg = 1;
					else if (elem[12] == "Т") 
						vesKg = 0;

					if (elem[2] == "com"){
						_weight_list->Add(gcnew CWeight(elem[3], 9600, Parity::None, 8, StopBits::One, 600, elem[0], elem[1], _oracleList, _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15]));
					}
					else if (elem[2] == "Microsim/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}

					else if (elem[2] == "WE2120_ST/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}


					else if (elem[2] == "WE2120_ALT/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}

					else if (elem[2] == "INTECONT_OPUS_ST/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}
					else if (elem[2] == "DISOMAT_SATUS/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}

					else if (elem[2] == "DEFAULT/TCPIP"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}

					else if (elem[2] == "DATASCALES_REPEATER"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

					}


					else if (elem[2] == "DATASCALES_DLL"){
						_weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], elem[17]));

					}

					else if (elem[2] == "jaguar"){
						try
						{
							//TODO обределение DT
							String^ DTIP = _dataTrackListAll[0][0];
							Int32 DtPort = Int32::Parse(_dataTrackListAll[0][3]);


							_weight_list->Add(gcnew CWeight(elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList, int::Parse(elem[13]), vesKg, DTIP, DtPort, _weightJaguar, bool::Parse(elem[14])));
						}

						catch (SocketException^ e) {
							listBox1->Items->Add(elem[9] + e);
						}
					}
				}


				try {
					dataGridView1->RowCount = _weight_list->Count;
					dataGridView1->Enabled = true;
				}
				catch (System::ArgumentOutOfRangeException ^e){
					dataGridView1->RowCount = 1;
					dataGridView1->Enabled = false;
				}



				try
				{
					//Получим IP адрес
					String^ myHost = System::Net::Dns::GetHostName();
					String^ myIP = System::Net::Dns::GetHostByName(myHost)->AddressList[0]->ToString();
					//инициализируем и запускаем сервер
					Int32 port = 13000;
					IPAddress^ localAddr = IPAddress::Parse( myIP );
					tcp_server = gcnew CTCPServer(localAddr, port, _weight_list);

					//tcp_oracle = gcnew CTCPSetverToOracle(localAddr, 13005, _oracleList);
					_counter_logError = 5000;
				}
				catch (Exception^ e){
					this->listBox1->Items->Add(e->ToString());
				}


				int ii = 0;
				for each(List<String^>^ _dataTrackList in _dataTrackListAll) {
					//elem->_lo
					if (bool::Parse(_dataTrackList[4])){
						CDataTrack^ dtreck = gcnew CDataTrack(_weight_list, _dataTrackList[0], Int32::Parse(_dataTrackList[1]), Int32::Parse(_dataTrackList[2]), Int32::Parse(_dataTrackList[3]), ii);
						dtreckList->Add(dtreck);
						ii++;
					}
				}

			}
			catch (Exception^ e){
				listBox1->Items->Add(e->ToString());
			}

			listBox1->Items->Add("Доступно лицензий: " + CountLicense.ToString());
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			for each(CWeight^ elem in _weight_list ) {
				//elem->_lo
				delete elem;
			}
			delete tcp_server;
			delete _weight_list;
			/*	delete tcp_oracle;*/
			//delete dtreck;
			for each(CDataTrack^ elem in dtreckList ) {
				//elem->_lo
				delete elem;
			}

			CheckWorkedBool = false;
			CheckWorkedThread->Abort();

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  dataGridView1;

	private: System::Windows::Forms::ToolStrip^  toolStrip1;


	private: System::Windows::Forms::Timer^  timer1;


	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	protected: 




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		List<CWeight^>^ _weight_list;
		//Настройки для ОрАКл
		List<String^>^ _oracleList;
		List<List<String^>^>^ _dataTrackListAll;

		List<bool>^ _buttonControl;
		List<List<String^>^>^ _weight;
		List<int>^ _weightJaguar;

		List<String^>^ _LicenseList;

		Tablitsa::Form1^ _FormOut;
		Tablitsa::AdminForm^ _Admin;
		Tablitsa::History^ _History;

		String^ currentHashPassword;


		CTCPSetverToOracle^ tcp_oracle;
		int _counter_logError;
		//CDataTrack^ dtreck;
		List<CDataTrack^>^ dtreckList; 
		Int32 CountLicense;
		String^ CountLicenseHash;


		bool CheckWorkedBool;
		Thread^ CheckWorkedThread;


		//		void ShowInPutPassword(void);

	private: System::Windows::Forms::ToolStripButton^  BtnMonitorDiagnostic;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ToolStripButton^  ButtonGetVesy;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon2;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripLabel^  toolStripLabel1;
	private: System::Windows::Forms::ToolStripTextBox^  toolStripTextBoxUpdateUi;

	private: System::Windows::Forms::ToolStripButton^  toolStripAppleUpdateTimer;
			 CTCPServer^ tcp_server;



#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
				 this->BtnMonitorDiagnostic = (gcnew System::Windows::Forms::ToolStripButton());
				 this->ButtonGetVesy = (gcnew System::Windows::Forms::ToolStripButton());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripLabel1 = (gcnew System::Windows::Forms::ToolStripLabel());
				 this->toolStripTextBoxUpdateUi = (gcnew System::Windows::Forms::ToolStripTextBox());
				 this->toolStripAppleUpdateTimer = (gcnew System::Windows::Forms::ToolStripButton());
				 this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
				 this->listBox1 = (gcnew System::Windows::Forms::ListBox());
				 this->notifyIcon2 = (gcnew System::Windows::Forms::NotifyIcon(this->components));
				 this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
				 this->toolStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // dataGridView1
				 // 
				 this->dataGridView1->AllowUserToResizeColumns = false;
				 this->dataGridView1->AllowUserToResizeRows = false;
				 this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
				 this->dataGridView1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->dataGridView1->Location = System::Drawing::Point(0, 25);
				 this->dataGridView1->MultiSelect = false;
				 this->dataGridView1->Name = L"dataGridView1";
				 this->dataGridView1->ReadOnly = true;
				 this->dataGridView1->RowHeadersVisible = false;
				 this->dataGridView1->RowTemplate->Height = 23;
				 this->dataGridView1->Size = System::Drawing::Size(1186, 410);
				 this->dataGridView1->TabIndex = 0;
				 this->dataGridView1->CellMouseDoubleClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &MainForm::dataGridView1_CellMouseDoubleClick);
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->toolStripButton1, 
					 this->BtnMonitorDiagnostic, this->ButtonGetVesy, this->toolStripSeparator1, this->toolStripLabel1, this->toolStripTextBoxUpdateUi, 
					 this->toolStripAppleUpdateTimer});
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(1186, 25);
				 this->toolStrip1->TabIndex = 4;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // toolStripButton1
				 // 
				 this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
				 this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripButton1->Name = L"toolStripButton1";
				 this->toolStripButton1->Size = System::Drawing::Size(98, 22);
				 this->toolStripButton1->Text = L"Администратор";
				 this->toolStripButton1->Click += gcnew System::EventHandler(this, &MainForm::toolStripButton1_Click);
				 // 
				 // BtnMonitorDiagnostic
				 // 
				 this->BtnMonitorDiagnostic->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->BtnMonitorDiagnostic->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"BtnMonitorDiagnostic.Image")));
				 this->BtnMonitorDiagnostic->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->BtnMonitorDiagnostic->Name = L"BtnMonitorDiagnostic";
				 this->BtnMonitorDiagnostic->Size = System::Drawing::Size(81, 22);
				 this->BtnMonitorDiagnostic->Text = L"Диагностика";
				 this->BtnMonitorDiagnostic->Click += gcnew System::EventHandler(this, &MainForm::BtnMonitorDiagnostic_Click);
				 // 
				 // ButtonGetVesy
				 // 
				 this->ButtonGetVesy->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->ButtonGetVesy->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ButtonGetVesy.Image")));
				 this->ButtonGetVesy->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->ButtonGetVesy->Name = L"ButtonGetVesy";
				 this->ButtonGetVesy->Size = System::Drawing::Size(81, 22);
				 this->ButtonGetVesy->Text = L"Мониторинг";
				 this->ButtonGetVesy->Click += gcnew System::EventHandler(this, &MainForm::ButtonGetVesy_Click);
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
				 // 
				 // toolStripLabel1
				 // 
				 this->toolStripLabel1->Name = L"toolStripLabel1";
				 this->toolStripLabel1->Size = System::Drawing::Size(62, 22);
				 this->toolStripLabel1->Text = L"Update UI:";
				 // 
				 // toolStripTextBoxUpdateUi
				 // 
				 this->toolStripTextBoxUpdateUi->Name = L"toolStripTextBoxUpdateUi";
				 this->toolStripTextBoxUpdateUi->Size = System::Drawing::Size(60, 25);
				 // 
				 // toolStripAppleUpdateTimer
				 // 
				 this->toolStripAppleUpdateTimer->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripAppleUpdateTimer->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripAppleUpdateTimer.Image")));
				 this->toolStripAppleUpdateTimer->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripAppleUpdateTimer->Name = L"toolStripAppleUpdateTimer";
				 this->toolStripAppleUpdateTimer->Size = System::Drawing::Size(35, 22);
				 this->toolStripAppleUpdateTimer->Text = L"Save";
				 this->toolStripAppleUpdateTimer->Click += gcnew System::EventHandler(this, &MainForm::toolStripAppleUpdateTimer_Click);
				 // 
				 // timer1
				 // 
				 this->timer1->Interval = 300;
				 this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
				 // 
				 // listBox1
				 // 
				 this->listBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->listBox1->FormattingEnabled = true;
				 this->listBox1->Location = System::Drawing::Point(0, 337);
				 this->listBox1->Name = L"listBox1";
				 this->listBox1->Size = System::Drawing::Size(1186, 95);
				 this->listBox1->TabIndex = 5;
				 // 
				 // notifyIcon2
				 // 
				 this->notifyIcon2->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon2.Icon")));
				 this->notifyIcon2->Text = L"Весы  (C) ДАТАЦентр Автоматика";
				 this->notifyIcon2->Click += gcnew System::EventHandler(this, &MainForm::notifyIcon2_Click);
				 // 
				 // timer2
				 // 
				 this->timer2->Enabled = true;
				 this->timer2->Interval = 10000;
				 this->timer2->Tick += gcnew System::EventHandler(this, &MainForm::timer2_Tick);
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1186, 435);
				 this->Controls->Add(this->listBox1);
				 this->Controls->Add(this->dataGridView1);
				 this->Controls->Add(this->toolStrip1);
				 this->MinimumSize = System::Drawing::Size(700, 300);
				 this->Name = L"MainForm";
				 this->Text = L"Data-Scales - V21.23";
				 this->Load += gcnew System::EventHandler(this, &MainForm::Form1_Load);
				 this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
				 this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

			 //это процедурки для настроек
	private: char* SystemStringToChar(System::String^ string) 
			 {
				 return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
			 }

			 /*		 private: System::String^ CharToSystemString(pugi::char_t* ch) 
			 {
			 return gcnew System::String(ch);
			 }
			 */


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 dataGridView1->RowCount = dataGridView1->RowCount + 1;

			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 //dataGridView1->Co
				 dataGridView1->ColumnCount = 9;
				 dataGridView1->Columns[0]->Width = 45;
				 dataGridView1->Columns[0]->HeaderText = "Номер";
				 dataGridView1->Columns[1]->HeaderText = "Метоположение";
				 dataGridView1->Columns[1]->Width = 120;
				 dataGridView1->Columns[2]->HeaderText = "Тип весов";
				 dataGridView1->Columns[2]->Width = 160;
				 dataGridView1->Columns[3]->HeaderText = "IP";
				 dataGridView1->Columns[4]->HeaderText = "Вес";
				 dataGridView1->Columns[4]->Width = 200;
				 dataGridView1->Columns[5]->HeaderText = "Статус";
				 dataGridView1->Columns[6]->HeaderText = "Дата-трек";
				 dataGridView1->Columns[7]->HeaderText = "OracleTime";
				 dataGridView1->Columns[7]->Width = 120;
				 dataGridView1->Columns[8]->HeaderText = "RawData";
				 dataGridView1->Columns[8]->Width = 200;
				 //dataGridView1->Columns[5]->Visible= false;
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 dataGridView1->Rows[0]->Cells[0]->Value = "qweq qweq" ;

			 }
	private: System::Void dataGridView1_CellMouseDoubleClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e) {
				 int i;
				 i = dataGridView1->SelectedCells[0]->RowIndex;
				 //Form1::Text = i.ToString;
				 String ^str = dataGridView1[0, i]->Value->ToString(); 
				 //MainForm::Text = str;
				 for each(CWeight^ elem in _weight_list ) {
					 if (elem->name == str) { elem->Show(); break;}

				 }



			 }
	private: System::Void toolStripLabel1_Click(System::Object^  sender, System::EventArgs^  e) {
				 dataGridView1->RowCount = dataGridView1->RowCount + 1;
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 int i = 0;
				 //В _weight_list содержатся элементы класса CWeight
				 //в которых имеется информация о различных микросимах
				 for each(CWeight^ elem in _weight_list ) {

					 dataGridView1->Rows[i]->Cells[0]->Value = elem->name ;
					 dataGridView1->Rows[i]->Cells[1]->Value = elem->location ;

					 dataGridView1->Rows[i]->Cells[2]->Value = elem->getTypeScales() ;
					 dataGridView1->Rows[i]->Cells[3]->Value = elem->getIp();
					 dataGridView1->Rows[i]->Cells[4]->Value = elem->weight ;

					 if (elem->ind_stabil) {
						 dataGridView1->Rows[i]->Cells[4]->Style->BackColor = Color::LightGreen;
					 }
					 else {
						 dataGridView1->Rows[i]->Cells[4]->Style->BackColor = Color::WhiteSmoke;
					 }


					 if (elem->weight == "NoMicro"){
						 dataGridView1->Rows[i]->Cells[5]->Value = "Нет устройства";
						 dataGridView1->Rows[i]->Cells[5]->Style->BackColor = Color::Yellow;
					 }
					 else if (elem->connect) {
						 dataGridView1->Rows[i]->Cells[5]->Value = "Подключен";
						 dataGridView1->Rows[i]->Cells[5]->Style->BackColor = Color::LightGreen;


					 }

					 else {
						 dataGridView1->Rows[i]->Cells[5]->Value = "Отключен";
						 dataGridView1->Rows[i]->Cells[5]->Style->BackColor = Color::Tomato;
					 }
					 //TODO отображение в Таблице
					 dataGridView1->Rows[i]->Cells[6]->Value = elem->DataTrackIP + ":" + elem->getNomerSSM().ToString();
					 dataGridView1->Rows[i]->Cells[6]->Style->BackColor = Color::Tomato;

					 for each (CDataTrack^ dtreck in dtreckList) {
						 if (dtreck->_ip == elem->DataTrackIP) {

							 if ((elem->getTypeScales() == "Microsim/TCPIP" ) || 
								 (elem->getTypeScales() == "WE2120_ST/TCPIP") ||
								 (elem->getTypeScales() == "DISOMAT_SATUS/TCPIP") ||
								 (elem->getTypeScales() == "DATASCALES_REPEATER") ||
								 (elem->getTypeScales() == "WE2120_ALT/TCPIP" )
								 )
							 {
								 if (dtreck->getStatusMicrosim()) 
								 {
									 dataGridView1->Rows[i]->Cells[6]->Value = elem->DataTrackIP + ":" + elem->getNomerSSM().ToString();
									 dataGridView1->Rows[i]->Cells[6]->Style->BackColor = Color::LightGreen;
								 }
								 else 
								 {
									 dataGridView1->Rows[i]->Cells[6]->Value = elem->DataTrackIP + ":" + elem->getNomerSSM().ToString();
									 dataGridView1->Rows[i]->Cells[6]->Style->BackColor = Color::Tomato;
							  }
							 }
							 else if (elem->getTypeScales() == "Jaguar/TCPIP" )
							 {
								 if (elem->getStatusSSMJaguar()) 
								 {
									 dataGridView1->Rows[i]->Cells[6]->Value = elem->DataTrackIP + ":" + elem->getNomerSSM().ToString();
									 dataGridView1->Rows[i]->Cells[6]->Style->BackColor = Color::LightGreen;
								 }

								 else 
								 {
									 dataGridView1->Rows[i]->Cells[6]->Value = elem->DataTrackIP + ":" + elem->getNomerSSM().ToString();
									 dataGridView1->Rows[i]->Cells[6]->Style->BackColor = Color::Tomato;
								 }
							 }



						 }


					 }



					 if (elem->oracleConnect) {
						 //А тут запилим раздениие в зависимости от времени
						 if (elem->getLastSendDateTime() > DateTime::Now.AddMinutes(-10))
							dataGridView1->Rows[i]->Cells[7]->Style->BackColor = Color::LightGreen;
						 else 
							 dataGridView1->Rows[i]->Cells[7]->Style->BackColor = Color::LightCyan;
					 }
					 else {
						 dataGridView1->Rows[i]->Cells[7]->Style->BackColor = Color::Tomato;
					 }




					 //listBox1->Items->Add(elem->name +  " : " +elem->getVesMicrosim().ToString());
					 dataGridView1->Rows[i]->Cells[7]->Value = elem->getLastSendTime();
					 dataGridView1->Rows[i]->Cells[8]->Value = elem->getRawData();

					 //dataGridView1->Rows[0]->Cells[0]->Value = _wght->name ;
					 i++;
				 }

				 _counter_logError += this->timer1->Interval;
				 //Пишем лог на экран
				 if ((_weight_list->Count > 0 ) && (_counter_logError >= 2000)) 
				 {
					 for (int i=0; i < _weight_list->Count; i++)
						 if ((_weight_list[i]->getErrorOracle() != "0") && (_weight_list[i]->sendOracle()))
						 {

							 String^ now = DateTime::Now.ToString();
							 String^ send = now + " : " + _weight_list[i]->getErrorOracle();
							 listBox1->Items->Add(send);
						 }

				 } 
				 if (_counter_logError >= 2000) _counter_logError = 0;


			 }
	private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (!ShowInPutPassword()) {

					 return;
				 }
				 _Admin = gcnew Tablitsa::AdminForm(_weight, _oracleList, _dataTrackListAll, currentHashPassword, _buttonControl);
				 for each(CWeight^ elem in _weight_list ) {
					 elem->Stop();
				 }


				 if ( _Admin->ShowDialog( this ) == Tablitsa::DialogResult::OK )
				 {
					 List<String^>^ orcl = _Admin->getOracleList();
					 List<List<String^>^>^  data = _Admin->getDataTrackList();
					 _weight = _Admin->getWeightList();
					 _oracleList = orcl;
					 _dataTrackListAll = data;
					 currentHashPassword = _Admin->getHashPassword();
					 _buttonControl = _Admin->getButtonControl();

					 //перезапускаем TCP сервер
					 delete tcp_server;
					 //delete tcp_oracle;
					 //delete dtreck;
					 for each(CDataTrack^ elem in dtreckList ) {
						 //elem->_lo
						 delete elem;
					 }
					 //Удаляем старые подключения
					 for each(CWeight^ elem in _weight_list ) {
						 delete elem;
					 }
					 delete _weight_list;
					 _weight_list = gcnew List<CWeight^>();

					 int i = 0;
					 for each(List<String^>^ elem in _weight ) {
						 //Проверим лицензию

						 i++;
						 if (i > CountLicense)
							 break;

						 bool vesKg = 1;
						 if (elem[12] == "КГ") 
							 vesKg = 1;
						 else if (elem[12] == "Т") 
							 vesKg = 0;
						 //_weight_list->Add(gcnew CWeight(elem[2], 9600, Parity::None, 8, StopBits::One, 600, elem[0], elem[1], orcl, data, _buttonControl));
						 if (elem[2] == "com"){
							 _weight_list->Add(gcnew CWeight(elem[3], 9600, Parity::None, 8, StopBits::One, 600, elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15]));
						 }
						 else if (elem[2] == "Microsim/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }
						 else if (elem[2] == "WE2120_ST/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }


						 else if (elem[2] == "WE2120_ALT/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }
						 else if (elem[2] == "DEFAULT/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }

						 else if (elem[2] == "INTECONT_OPUS_ST/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }
						 else if (elem[2] == "DISOMAT_SATUS/TCPIP"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }

						 //DATASCALES_REPEATER

						 else if (elem[2] == "DATASCALES_REPEATER"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], nullptr));

						 }

						 //DATASCALES_REPEATER

						 else if (elem[2] == "DATASCALES_DLL"){
							 _weight_list->Add(gcnew CWeight(elem[2], elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList,  _buttonControl, int::Parse(elem[13]), vesKg, bool::Parse(elem[14]), elem[15], elem[16], elem[17]));

						 }
						 else if (elem[2] == "jaguar")
						 {
							 try{
								 //TODO обределение DT
								 String^ DTIP = _dataTrackListAll[0][0];
								 Int32 DtPort = Int32::Parse(_dataTrackListAll[0][3]);


								 _weight_list->Add(gcnew CWeight(elem[9], elem[10], Int32::Parse(elem[11]), elem[0], elem[1], _oracleList, int::Parse(elem[13]), vesKg, DTIP, DtPort , _weightJaguar, bool::Parse(elem[14])));

							 }
							 catch (SocketException^ e) 
							 {//dns не найден
								 listBox1->Items->Add(elem[9] + e);
							 }
						 }



					 }

					 try {
						 for (int i=0; i < 8; i++) 
							 dataGridView1->Rows[0]->Cells[i]->Style->BackColor = Color::White;

						 dataGridView1->RowCount = _weight_list->Count;
						 dataGridView1->Enabled = true;
					 }
					 catch (System::ArgumentOutOfRangeException ^e){
						 dataGridView1->RowCount = 1;
						 for (int i=0; i < 8; i++) {
							 dataGridView1->Rows[0]->Cells[i]->Value = "";
							 dataGridView1->Rows[0]->Cells[i]->Style->BackColor = Color::Gray;
						 }
						 dataGridView1->Enabled = false;

					 }


					 //Получим IP адресс
					 String^ myHost = System::Net::Dns::GetHostName();
					 String^ myIP = System::Net::Dns::GetHostByName(myHost)->AddressList[0]->ToString();
					 //инициализируем и запускаем сервер
					 Int32 port = 13000;
					 IPAddress^ localAddr = IPAddress::Parse( myIP );
					 tcp_server = gcnew CTCPServer(localAddr, port, _weight_list);
					 //tcp_oracle = gcnew CTCPSetverToOracle(localAddr, 13005, _oracleList);*/

					 dtreckList->Clear();
					 int  ii= 0;
					 for each(List<String^>^ _dataTrackList in _dataTrackListAll) {
						 //elem->_lo
						 if (bool::Parse(_dataTrackList[4])){
							 CDataTrack^ dtreck = gcnew CDataTrack(_weight_list, _dataTrackList[0], Int32::Parse(_dataTrackList[1]), Int32::Parse(_dataTrackList[2]), Int32::Parse(_dataTrackList[3]), ii);
							 dtreckList->Add(dtreck);
							 ii++;
						 }
					 }

					 /*	if (bool::Parse(_dataTrackList[4]))
					 dtreck = gcnew CDataTrack(_weight_list, _dataTrackList[0], Int32::Parse(_dataTrackList[1]), Int32::Parse(_dataTrackList[2]), Int32::Parse(_dataTrackList[3]));
					 */	//Сохраняем настройки
					 this->SaveXml();

				 }
				 else
				 {
					 for each(CWeight^ elem in _weight_list ) {
						 elem->Start();
					 }
				 }
				 delete _Admin;

			 }

	private: System::Void BtnMonitorDiagnostic_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Вызов модуля диагностика
				 _History = gcnew Tablitsa::History(_oracleList);
				 _History->ShowDialog();
				 delete _History;

			 }
	private: System::Void ButtonGetVesy_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Вызов модуля диагностика
				 getVesyForm^ Form = gcnew Tablitsa::getVesyForm(_oracleList);
				 Form->ShowDialog();
				 delete Form;

			 }
	private: bool ShowInPutPassword(void){
				 //Использование пароля

				 InputBox^ input;
				 if (currentHashPassword == getHashSha256("1234"))
				 {
					 input = gcnew Tablitsa::InputBox("Доступ ограничен", "Стандартный пароль: 1234");
				 }
				 else 
				 {
					 input = gcnew Tablitsa::InputBox("Доступ ограничен", "Введите пароль");

				 }

				 String^ inPutHash;

				 if (input->ShowDialog( this ) == Tablitsa::DialogResult::OK) 
				 {
					 inPutHash = getHashSha256( input->getValue());
					 if (currentHashPassword == inPutHash ) 
					 {
						 return true;
					 }

					 else {
						 MessageBox::Show("Пароль неверный", "Error",  MessageBoxButtons::OK, MessageBoxIcon::Error);	
						 return false;
						}

				 }
				 else 
				 {
					 return false;
				 }
			 };

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

	private: void GenerateLicenceList(){
				 _LicenseList = gcnew List<String^>();

				 for (int j = 0; j < 30; j++) {

					 String^ hashValuseString = j.ToString();
					 for (int i = 0; i < 10; i++)
						 hashValuseString = getHashSha256(hashValuseString);

					 _LicenseList->Add(hashValuseString);

				 }
			 }

	private: int GetCountLicence(String^ hash){
				 int c = _LicenseList->IndexOf(hash);
				 if (c < 1)
					 c = 1;
				 return c;
			 }

	private: void SaveXml(void)
			 {
				 XmlDocument ^myXml = gcnew XmlDocument();
				 myXml->LoadXml("<Vesy>" 
					 "</Vesy>");

				 //oracle
				 XmlNode ^oracleNode = myXml->DocumentElement;
				 XmlElement ^ oracleElem = myXml->CreateElement("Oracle");

				 XmlElement ^ elem1 = myXml->CreateElement("DataSource");
				 elem1->InnerText = _oracleList[0];
				 oracleElem->AppendChild(elem1);

				 XmlElement ^ elem2 = myXml->CreateElement("User");
				 elem2->InnerText = _oracleList[1];
				 oracleElem->AppendChild(elem2);

				 XmlElement ^ elem3 = myXml->CreateElement("Password");
				 elem3->InnerText = _oracleList[2];
				 oracleElem->AppendChild(elem3);

				 XmlElement ^ elem4 = myXml->CreateElement("Interval");
				 elem4->InnerText = _oracleList[3];
				 oracleElem->AppendChild(elem4);

				 XmlElement ^ elem5 = myXml->CreateElement("Send");
				 elem5->InnerText = _oracleList[4];
				 oracleElem->AppendChild(elem5);

				 oracleNode->AppendChild(oracleElem);

				 ////dataTrack
				 //XmlNode ^dataNode = myXml->DocumentElement;
				 //XmlElement ^ dataElem = myXml->CreateElement("DataTrack");
				 //
				 //XmlElement ^ elem11 = myXml->CreateElement("IP");
				 //elem11->InnerText = _dataTrackList[0];
				 //dataElem->AppendChild(elem11);

				 //XmlElement ^ elem22 = myXml->CreateElement("TimeOut");
				 //elem22->InnerText = _dataTrackList[1];
				 //dataElem->AppendChild(elem22);

				 //XmlElement ^ elem33 = myXml->CreateElement("PortMicrosim");
				 //elem33->InnerText = _dataTrackList[2];
				 //dataElem->AppendChild(elem33);
				 //
				 //XmlElement ^ elem44 = myXml->CreateElement("PortJaguar");
				 //elem44->InnerText = _dataTrackList[3];
				 //dataElem->AppendChild(elem44);

				 //XmlElement ^ elem55 = myXml->CreateElement("Send");
				 //elem55->InnerText = _dataTrackList[4];
				 //dataElem->AppendChild(elem55);

				 //dataNode->AppendChild(dataElem);
				 //Весоизмерители
				 XmlNode ^VesyizmNode = myXml->DocumentElement;

				 for each(List<String^>^ elem in _dataTrackListAll ) {
					 //пишем весоизмерители
					 //for ( int i = 0; i < 10; i++) {
					 XmlElement ^ VesyizmElem = myXml->CreateElement("DataTrack");

					 XmlElement ^ elem0;

					 elem0 = myXml->CreateElement("IP");
					 elem0->InnerText = elem[0];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("TimeOut");
					 elem0->InnerText = elem[1];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("PortMicrosim");
					 elem0->InnerText = elem[2];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("PortJaguar");
					 elem0->InnerText = elem[3];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Send");
					 elem0->InnerText = elem[4];
					 VesyizmElem->AppendChild(elem0);

					 VesyizmNode->AppendChild(VesyizmElem);
				 }
				 /*		 


				 //Password 
				 node = doc.append_child("Password");
				 node.append_attribute("Hash") = SystemStringToChar(currentHashPassword);
				 */
				 //password
				 XmlNode ^passNode = myXml->DocumentElement;
				 XmlElement ^ passElem = myXml->CreateElement("Password");

				 XmlElement ^ elem111 = myXml->CreateElement("hash");
				 elem111->InnerText = currentHashPassword;
				 passElem->AppendChild(elem111);

				 passNode->AppendChild(passElem);


				 //License
				 passNode = myXml->DocumentElement;
				 passElem = myXml->CreateElement("License");

				 elem111 = myXml->CreateElement("count");
				 elem111->InnerText = CountLicenseHash;
				 passElem->AppendChild(elem111);
				 passNode->AppendChild(passElem);

				 //ButtonControl
				 XmlNode ^ButtonNode = myXml->DocumentElement;
				 XmlElement ^ ButtonElem = myXml->CreateElement("ButtonControl");

				 XmlElement ^ elem1111 = myXml->CreateElement("Null");
				 elem1111->InnerText =  _buttonControl[0].ToString();
				 ButtonElem->AppendChild(elem1111);

				 XmlElement ^ elem2222 = myXml->CreateElement("Tara");
				 elem2222->InnerText =  _buttonControl[1].ToString();
				 ButtonElem->AppendChild(elem2222);

				 XmlElement ^ elem3333 = myXml->CreateElement("Mode");
				 elem3333->InnerText =  _buttonControl[2].ToString();
				 ButtonElem->AppendChild(elem3333);

				 XmlElement ^ elem4444 = myXml->CreateElement("Select");
				 elem4444->InnerText =  _buttonControl[3].ToString();
				 ButtonElem->AppendChild(elem4444);

				 ButtonNode->AppendChild(ButtonElem);


				 //Весоизмерители
				 VesyizmNode = myXml->DocumentElement;
				 XmlElement ^ Vesyizm = myXml->CreateElement("Vesyizm");

				 for each(List<String^>^ elem in _weight ) {
					 //пишем весоизмерители
					 //for ( int i = 0; i < 10; i++) {
					 XmlElement ^ VesyizmElem = myXml->CreateElement("VesyizmPart");

					 XmlElement ^ elem0;

					 elem0 = myXml->CreateElement("Number");
					 elem0->InnerText = elem[0];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Place");
					 elem0->InnerText = elem[1];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Type");
					 elem0->InnerText = elem[2];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Port");
					 elem0->InnerText = elem[3];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Speed");
					 elem0->InnerText = elem[4];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Parity");
					 elem0->InnerText = elem[5];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("BitCount");
					 elem0->InnerText =elem[6];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("StopBitCount");
					 elem0->InnerText = elem[7];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("Interval");
					 elem0->InnerText = elem[8];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("IpMoxa");
					 elem0->InnerText = elem[9];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("PortMoxa");
					 elem0->InnerText = elem[10];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("UpdateMoxa");
					 elem0->InnerText = elem[11];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("EdIzm");
					 elem0->InnerText = elem[12];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("NomerSSM");
					 elem0->InnerText = elem[13];
					 VesyizmElem->AppendChild(elem0);


					 elem0 = myXml->CreateElement("SendRaw");
					 elem0->InnerText = elem[14];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("IPSSM");
					 elem0->InnerText = elem[15];
					 VesyizmElem->AppendChild(elem0);

					 elem0 = myXml->CreateElement("MagicString");
					 elem0->InnerText = elem[16];
					 VesyizmElem->AppendChild(elem0);


					 elem0 = myXml->CreateElement("ModelDLL");
					 elem0->InnerText = elem[17];
					 VesyizmElem->AppendChild(elem0);

					 Vesyizm->AppendChild(VesyizmElem);
				 }

				 VesyizmNode->AppendChild(Vesyizm);

				 //Сохранение 
				 myXml->Save("settings.xml");


			 }


	private: bool LoadXml(void) 
			 {
				 XmlDocument^ doc = gcnew XmlDocument;
				 try
				 {
					 doc->Load("settings.xml");
				 }
				 catch (System::Xml::XmlException ^ e)
				 {
					 return false;
				 }

				 catch (System::IO::FileNotFoundException^ e)
				 {
					 return false;
				 }

				 XmlNode^ node;
				 XmlNode^ root = doc->DocumentElement;

				 //Oracle
				 node = root->SelectSingleNode("//Oracle");
				 _oracleList->Add(node->SelectSingleNode("./DataSource")->InnerText);
				 _oracleList->Add(node->SelectSingleNode("./User")->InnerText);
				 _oracleList->Add(node->SelectSingleNode("./Password")->InnerText);
				 _oracleList->Add(node->SelectSingleNode("./Interval")->InnerText);
				 _oracleList->Add(node->SelectSingleNode("./Send")->InnerText);

				 //	//DataTrack
				 //node = root->SelectSingleNode("//DataTrack");
				 //_dataTrackList->Add(node->SelectSingleNode("./IP")->InnerText);
				 //   _dataTrackList->Add(node->SelectSingleNode("./TimeOut")->InnerText);
				 //_dataTrackList->Add(node->SelectSingleNode("./PortMicrosim")->InnerText);
				 //_dataTrackList->Add(node->SelectSingleNode("./PortJaguar")->InnerText);
				 //_dataTrackList->Add(node->SelectSingleNode("./Send")->InnerText);


				 //DataTrackList
				 XmlNodeList^ nodeList;
				 nodeList = root->SelectNodes("//DataTrack");
				 System::Collections::IEnumerator^ myEnum = nodeList->GetEnumerator();
				 while ( myEnum->MoveNext() )
				 {
					 List<String^>^ w1= gcnew List<String^>();

					 XmlNode^ vesy = safe_cast<XmlNode^>(myEnum->Current);

					 w1->Add(vesy->SelectSingleNode("./IP")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./TimeOut")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./PortMicrosim")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./PortJaguar")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Send")->InnerText);
					 // _weight->Add(w1);
					 _dataTrackListAll->Add(w1);

				 }

				 //ButtonControl
				 node = root->SelectSingleNode("//ButtonControl");
				 _buttonControl->Add(bool::Parse(node->SelectSingleNode("./Null")->InnerText));
				 _buttonControl->Add(bool::Parse(node->SelectSingleNode("./Tara")->InnerText));
				 _buttonControl->Add(bool::Parse(node->SelectSingleNode("./Mode")->InnerText));
				 _buttonControl->Add(bool::Parse(node->SelectSingleNode("./Select")->InnerText));

				 //Password
				 node = root->SelectSingleNode("//Password");
				 currentHashPassword = node->SelectSingleNode("//hash")->InnerText; 



				 //License
				 node = root->SelectSingleNode("//License");
				 CountLicenseHash = node->SelectSingleNode("//count")->InnerText; 

				 CountLicense = GetCountLicence(CountLicenseHash);
				 //Весоизмерители

				 nodeList = root->SelectNodes("//VesyizmPart");
				 myEnum = nodeList->GetEnumerator();
				 while ( myEnum->MoveNext() )
				 {
					 List<String^>^ w1= gcnew List<String^>();

					 XmlNode^ vesy = safe_cast<XmlNode^>(myEnum->Current);

					 w1->Add(vesy->SelectSingleNode("./Number")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Place")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Type")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Port")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Speed")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Parity")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./BitCount")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./StopBitCount")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./Interval")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./IpMoxa")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./PortMoxa")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./UpdateMoxa")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./EdIzm")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./NomerSSM")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./SendRaw")->InnerText);
					 w1->Add(vesy->SelectSingleNode("./IPSSM")->InnerText);
					 try{
						 w1->Add(vesy->SelectSingleNode("./MagicString")->InnerText);
					 }

					 catch (Exception^ eee){
						 w1->Add("");
					 }

					 w1->Add(vesy->SelectSingleNode("./ModelDLL")->InnerText);
					 _weight->Add(w1);

				 }

				 return true;
			 }


	private: void CheckWorked(void){
				 //Тут будет небольшая задержка
				 Thread::Sleep(10);

				 while (CheckWorkedBool) {
					 //Алгоритм записи во временный файл
					 try {
						 StreamWriter^ sw = gcnew StreamWriter("DataScales-KeepAlive.lock", false, Encoding::GetEncoding(1251));
						 String^ temp_str = DateTime::Now.ToString();
						 sw->WriteLine(temp_str);
						 sw->Close();

					 }

					 catch (Exception^ e5){

					 }

					 Thread::Sleep(200);
				 }

			 };


	private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {

				 if (this->WindowState == FormWindowState::Minimized)
				 {
					 this->Hide();
					 notifyIcon2->Visible = true;
				 }



			 }
	private: System::Void notifyIcon2_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Show();
				 this->WindowState = FormWindowState::Normal;
				 notifyIcon2->Visible = false;
			 }
	private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
				 //Очистим listBox

				 if (listBox1->Items->Count > 200) {
					 listBox1->Items->Clear();

				 }
			 }
	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {


			 }
	private: System::Void toolStripAppleUpdateTimer_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
					 Int32::Parse(toolStripTextBoxUpdateUi->Text);

				 }

				 catch (Exception ^e) {
					 return;
				 }
				 int i = Int32::Parse(toolStripTextBoxUpdateUi->Text);

				 if ((i<50) || (i > 500000))
					 return;

				 timer1->Interval = i;
				 toolStripLabel1->Text = "Update UI: " + i.ToString();
			 }


	};
}


