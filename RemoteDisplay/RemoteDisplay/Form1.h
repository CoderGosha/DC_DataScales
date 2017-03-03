#pragma once
#include "TCPClient.h"
#include "pugixml.hpp"
#include "InputBox.h"

namespace RemoteDisplay {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Security::Cryptography;
	using namespace System::Globalization;
	using namespace pugi;
//	using namespace System::Windows::Forms::MessageBox;


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
	public: System::Drawing::Text::PrivateFontCollection^ _clectFont;
	public: int^ _windowTop;
	private: System::Windows::Forms::CheckBox^  checkBoxSelect;
	public: 
	private: System::Windows::Forms::CheckBox^  checkBoxMode;
	private: System::Windows::Forms::CheckBox^  checkBoxTara;
	private: System::Windows::Forms::CheckBox^  checkBoxNull;
	private: System::Windows::Forms::Button^  buttonPass;
	public: int^ _windowLeft;

	

	public:
		Form1(void)
		{


			InitializeComponent();
			_SettingHeight = tableLayoutPanel1->RowStyles[0]->Height;

			//
			//TODO: Add the constructor code here
			//
			//cmbBxVesoizmeritel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			//шрифтики 
			
			try 
			{
			_clectFont = gcnew System::Drawing::Text::PrivateFontCollection();
			_clectFont->AddFontFile("1111.ttf");
			CurrentFont = _clectFont->Families[0];
			
			}
			catch (Exception ^ e){
				MessageBox::Show("Файл шрифта не найден, используем стандартный");
				FontFamily^ TFont = gcnew FontFamily(System::Drawing::Text::GenericFontFamilies::SansSerif);
				CurrentFont = TFont;
		
			}

			lblVes->Font = gcnew System::Drawing::Font(
				CurrentFont,
				23,
				Drawing::FontStyle::Italic,
				lblVes->Font->Unit
				);

	
			tableLayoutPanel1->RowStyles[0]->Height = 0;
			resizeLabels();
			_client = nullptr;
			_ip = "127.0.0.1";
			_port = 13000;
			_countConnect = 0;
			this->timer1->Enabled = false;
			this->timer2->Enabled = false;

			//По умолчанию все выключаем
			lblVes->Text = "OFFLINE";
			picBoxTaraIndicator->BackColor = Color::Black;
			picBoxStabilIndicator->BackColor = Color::Black;
			picBoxNolIndicator->BackColor = Color::Black;
			picBoxKgIndicator->BackColor = Color::Black;
			picBoxTindicator->BackColor = Color::Black;
			picBoxShtIndicator->BackColor = Color::Black;
			picBoxMESIndicator->BackColor = Color::Red;
			_showSettings = false;
		
			//Выводим настройки в соответсвующие поля
			//this->txtBxIpAddress->Text = _ip;
			//this->txtBxPort->Text = _port.ToString();

			_buttonControl = gcnew List<bool>();
			

		inLoad();


		this->Location.X = 600;
		this->Location.Y = 600;
		this->Top = 600;
		this->Left = 600;


					//Запускаем
			try{
				this->_ip = txtBxIpAddress->Text;
				this->_port = Int32::Parse(txtBxPort->Text);
				this->timer1->Interval = Int32::Parse(txtBxChastotaOprosa->Text);
				this->timer1->Enabled= 1;
			}
			catch (Exception ^ e){
				txtBxIpAddress->Text = "127.0.0.1";
				txtBxPort->Text = "13000";
				txtBxChastotaOprosa->Text = "200";

			}
			
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

			if (_client) 
			{
				delete _client;
			}
		}

		private: System::Windows::Forms::ToolStrip^  toolStrip1;
	protected: 
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Button^  btnNol;
	private: System::Windows::Forms::Button^  btnTara;
	private: System::Windows::Forms::Button^  btnRejim;
	private: System::Windows::Forms::Button^  btnVibor;




	private: System::Windows::Forms::Label^  lblNolButton;
	private: System::Windows::Forms::Label^  lblTaraButton;
	private: System::Windows::Forms::Label^  lblRejimButton;
	private: System::Windows::Forms::Label^  lblViborButton;




	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::PictureBox^  picBoxTaraIndicator;
	private: System::Windows::Forms::PictureBox^  picBoxStabilIndicator;
	private: System::Windows::Forms::PictureBox^  picBoxNolIndicator;



	private: System::Windows::Forms::Label^  lblTara;
	private: System::Windows::Forms::Label^  lblStabil;
	private: System::Windows::Forms::Label^  lblNol;
	private: System::Windows::Forms::Label^  lblVes;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::PictureBox^  picBoxShtIndicator;

	private: System::Windows::Forms::PictureBox^  picBoxKgIndicator;

	private: System::Windows::Forms::Label^  lblKg;
	private: System::Windows::Forms::Label^  lblT;
	private: System::Windows::Forms::Label^  lblSht;




	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::Label^  lblSvyazSServerom;









	private: System::Windows::Forms::PictureBox^  picBoxTindicator;


	private: System::Windows::Forms::PictureBox^  picBoxMESIndicator;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::ComponentModel::IContainer^  components;
    private: System::Windows::Forms::ToolStripLabel^  lblName;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;


	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::Label^  lblIpAddress;

	private: System::Windows::Forms::Label^  lblPort;
	private: System::Windows::Forms::Label^  lblChastotaOprosa;
	private: System::Windows::Forms::Button^  btnPrimenit;




	private: System::Windows::Forms::TextBox^  txtBxIpAddress;
	private: System::Windows::Forms::TextBox^  txtBxPort;
	private: System::Windows::Forms::TextBox^  txtBxChastotaOprosa;
private: System::Windows::Forms::ComboBox^  cmbBxVesoizmeritel;






private: System::Windows::Forms::Button^  btnObnovit;
private: System::Windows::Forms::CheckBox^  chckBxFullscreen;



private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::ToolStripButton^  toolStripButton2;










private: System::Windows::Forms::ToolStripButton^  toolStripButton1;




		
		
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
//		System::ComponentModel::Container ^components;

		
		CTCPClient^ _client;
		Int32 _port;
		String^ _ip;
		String^ _nomerVesy;
		//Счетчик для неудачных подключений
		Int32 _countConnect;
		FontFamily^ CurrentFont;
		String^ currentHashPassword;

private: System::Windows::Forms::ToolStripButton^  tlStpBtnPoverhVsehOkon;

private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;

		//окно настройки
		bool _showSettings;
		int _SettingHeight;
		List<bool>^ _buttonControl;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->lblName = (gcnew System::Windows::Forms::ToolStripLabel());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tlStpBtnPoverhVsehOkon = (gcnew System::Windows::Forms::ToolStripButton());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->btnNol = (gcnew System::Windows::Forms::Button());
			this->btnTara = (gcnew System::Windows::Forms::Button());
			this->btnRejim = (gcnew System::Windows::Forms::Button());
			this->btnVibor = (gcnew System::Windows::Forms::Button());
			this->lblNolButton = (gcnew System::Windows::Forms::Label());
			this->lblTaraButton = (gcnew System::Windows::Forms::Label());
			this->lblRejimButton = (gcnew System::Windows::Forms::Label());
			this->lblViborButton = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->picBoxTaraIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->picBoxStabilIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->picBoxNolIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->lblTara = (gcnew System::Windows::Forms::Label());
			this->lblStabil = (gcnew System::Windows::Forms::Label());
			this->lblNol = (gcnew System::Windows::Forms::Label());
			this->lblVes = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->picBoxShtIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->picBoxKgIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->lblKg = (gcnew System::Windows::Forms::Label());
			this->lblT = (gcnew System::Windows::Forms::Label());
			this->lblSht = (gcnew System::Windows::Forms::Label());
			this->picBoxTindicator = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->lblSvyazSServerom = (gcnew System::Windows::Forms::Label());
			this->picBoxMESIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->checkBoxSelect = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxMode = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxTara = (gcnew System::Windows::Forms::CheckBox());
			this->lblIpAddress = (gcnew System::Windows::Forms::Label());
			this->lblPort = (gcnew System::Windows::Forms::Label());
			this->lblChastotaOprosa = (gcnew System::Windows::Forms::Label());
			this->btnPrimenit = (gcnew System::Windows::Forms::Button());
			this->txtBxIpAddress = (gcnew System::Windows::Forms::TextBox());
			this->txtBxPort = (gcnew System::Windows::Forms::TextBox());
			this->txtBxChastotaOprosa = (gcnew System::Windows::Forms::TextBox());
			this->cmbBxVesoizmeritel = (gcnew System::Windows::Forms::ComboBox());
			this->btnObnovit = (gcnew System::Windows::Forms::Button());
			this->chckBxFullscreen = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxNull = (gcnew System::Windows::Forms::CheckBox());
			this->buttonPass = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->toolStrip1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxTaraIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxStabilIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxNolIndicator))->BeginInit();
			this->tableLayoutPanel7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxShtIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxKgIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxTindicator))->BeginInit();
			this->tableLayoutPanel8->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxMESIndicator))->BeginInit();
			this->tableLayoutPanel5->SuspendLayout();
			this->SuspendLayout();
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->toolStripButton1, 
				this->toolStripSeparator2, this->toolStripButton2, this->lblName, this->toolStripSeparator1, this->tlStpBtnPoverhVsehOkon});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(790, 25);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(81, 22);
			this->toolStripButton1->Text = L"Настройки";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &Form1::toolStripButton1_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			this->toolStripSeparator2->Click += gcnew System::EventHandler(this, &Form1::toolStripSeparator2_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->toolStripButton2->Checked = true;
			this->toolStripButton2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(81, 22);
			this->toolStripButton2->Text = L"Во весь экран";
			this->toolStripButton2->ToolTipText = L"Во весь экран";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &Form1::toolStripButton2_Click);
			// 
			// lblName
			// 
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(123, 22);
			this->lblName->Text = L"Номер весоизмерителя";
			this->lblName->Click += gcnew System::EventHandler(this, &Form1::lblName_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// tlStpBtnPoverhVsehOkon
			// 
			this->tlStpBtnPoverhVsehOkon->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->tlStpBtnPoverhVsehOkon->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tlStpBtnPoverhVsehOkon->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"tlStpBtnPoverhVsehOkon.Image")));
			this->tlStpBtnPoverhVsehOkon->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tlStpBtnPoverhVsehOkon->Name = L"tlStpBtnPoverhVsehOkon";
			this->tlStpBtnPoverhVsehOkon->Size = System::Drawing::Size(101, 22);
			this->tlStpBtnPoverhVsehOkon->Text = L"Поверх всех окон";
			this->tlStpBtnPoverhVsehOkon->Click += gcnew System::EventHandler(this, &Form1::tlStpBtnPoverhVsehOkon_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel8, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 25);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 93)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 65.24216F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 27.35043F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 7.122507F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(790, 415);
			this->tableLayoutPanel1->TabIndex = 1;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel2->ColumnCount = 4;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25)));
			this->tableLayoutPanel2->Controls->Add(this->btnNol, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->btnTara, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->btnRejim, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->btnVibor, 3, 1);
			this->tableLayoutPanel2->Controls->Add(this->lblNolButton, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->lblTaraButton, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->lblRejimButton, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->lblViborButton, 3, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 306);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 30)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(784, 82);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// btnNol
			// 
			this->btnNol->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnNol.BackgroundImage")));
			this->btnNol->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnNol->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnNol->Location = System::Drawing::Point(21, 28);
			this->btnNol->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnNol->Name = L"btnNol";
			this->btnNol->Size = System::Drawing::Size(154, 50);
			this->btnNol->TabIndex = 0;
			this->btnNol->UseVisualStyleBackColor = true;
			this->btnNol->Click += gcnew System::EventHandler(this, &Form1::btnNol_Click);
			// 
			// btnTara
			// 
			this->btnTara->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnTara.BackgroundImage")));
			this->btnTara->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnTara->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnTara->Location = System::Drawing::Point(216, 28);
			this->btnTara->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnTara->Name = L"btnTara";
			this->btnTara->Size = System::Drawing::Size(154, 50);
			this->btnTara->TabIndex = 1;
			this->btnTara->UseVisualStyleBackColor = true;
			this->btnTara->Click += gcnew System::EventHandler(this, &Form1::btnTara_Click);
			// 
			// btnRejim
			// 
			this->btnRejim->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnRejim.BackgroundImage")));
			this->btnRejim->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnRejim->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnRejim->Location = System::Drawing::Point(411, 28);
			this->btnRejim->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnRejim->Name = L"btnRejim";
			this->btnRejim->Size = System::Drawing::Size(154, 50);
			this->btnRejim->TabIndex = 2;
			this->btnRejim->UseVisualStyleBackColor = true;
			this->btnRejim->Click += gcnew System::EventHandler(this, &Form1::btnRejim_Click);
			// 
			// btnVibor
			// 
			this->btnVibor->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnVibor.BackgroundImage")));
			this->btnVibor->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnVibor->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnVibor->Location = System::Drawing::Point(606, 28);
			this->btnVibor->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnVibor->Name = L"btnVibor";
			this->btnVibor->Size = System::Drawing::Size(157, 50);
			this->btnVibor->TabIndex = 3;
			this->btnVibor->UseVisualStyleBackColor = true;
			this->btnVibor->Click += gcnew System::EventHandler(this, &Form1::btnVibor_Click);
			// 
			// lblNolButton
			// 
			this->lblNolButton->AutoSize = true;
			this->lblNolButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblNolButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblNolButton->Location = System::Drawing::Point(4, 1);
			this->lblNolButton->Name = L"lblNolButton";
			this->lblNolButton->Size = System::Drawing::Size(188, 23);
			this->lblNolButton->TabIndex = 4;
			this->lblNolButton->Text = L"Ноль";
			this->lblNolButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblTaraButton
			// 
			this->lblTaraButton->AutoSize = true;
			this->lblTaraButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblTaraButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblTaraButton->Location = System::Drawing::Point(199, 1);
			this->lblTaraButton->Name = L"lblTaraButton";
			this->lblTaraButton->Size = System::Drawing::Size(188, 23);
			this->lblTaraButton->TabIndex = 5;
			this->lblTaraButton->Text = L"Тара";
			this->lblTaraButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblRejimButton
			// 
			this->lblRejimButton->AutoSize = true;
			this->lblRejimButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblRejimButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblRejimButton->Location = System::Drawing::Point(394, 1);
			this->lblRejimButton->Name = L"lblRejimButton";
			this->lblRejimButton->Size = System::Drawing::Size(188, 23);
			this->lblRejimButton->TabIndex = 6;
			this->lblRejimButton->Text = L"Режим";
			this->lblRejimButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblViborButton
			// 
			this->lblViborButton->AutoSize = true;
			this->lblViborButton->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblViborButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblViborButton->Location = System::Drawing::Point(589, 1);
			this->lblViborButton->Name = L"lblViborButton";
			this->lblViborButton->Size = System::Drawing::Size(191, 23);
			this->lblViborButton->TabIndex = 7;
			this->lblViborButton->Text = L"Выбор";
			this->lblViborButton->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 3;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20.75338F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				65.62486F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				13.62177F)));
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel4, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->lblVes, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel7, 2, 0);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 96);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(784, 204);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel4->ColumnCount = 2;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				80)));
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20)));
			this->tableLayoutPanel4->Controls->Add(this->picBoxTaraIndicator, 1, 0);
			this->tableLayoutPanel4->Controls->Add(this->picBoxStabilIndicator, 1, 1);
			this->tableLayoutPanel4->Controls->Add(this->picBoxNolIndicator, 1, 2);
			this->tableLayoutPanel4->Controls->Add(this->lblTara, 0, 0);
			this->tableLayoutPanel4->Controls->Add(this->lblStabil, 0, 1);
			this->tableLayoutPanel4->Controls->Add(this->lblNol, 0, 2);
			this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel4->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 3;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(156, 198);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// picBoxTaraIndicator
			// 
			this->picBoxTaraIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxTaraIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxTaraIndicator->Location = System::Drawing::Point(127, 9);
			this->picBoxTaraIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxTaraIndicator->Name = L"picBoxTaraIndicator";
			this->picBoxTaraIndicator->Size = System::Drawing::Size(25, 48);
			this->picBoxTaraIndicator->TabIndex = 0;
			this->picBoxTaraIndicator->TabStop = false;
			// 
			// picBoxStabilIndicator
			// 
			this->picBoxStabilIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxStabilIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxStabilIndicator->Location = System::Drawing::Point(127, 74);
			this->picBoxStabilIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxStabilIndicator->Name = L"picBoxStabilIndicator";
			this->picBoxStabilIndicator->Size = System::Drawing::Size(25, 48);
			this->picBoxStabilIndicator->TabIndex = 1;
			this->picBoxStabilIndicator->TabStop = false;
			// 
			// picBoxNolIndicator
			// 
			this->picBoxNolIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxNolIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxNolIndicator->Location = System::Drawing::Point(127, 139);
			this->picBoxNolIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxNolIndicator->Name = L"picBoxNolIndicator";
			this->picBoxNolIndicator->Size = System::Drawing::Size(25, 50);
			this->picBoxNolIndicator->TabIndex = 2;
			this->picBoxNolIndicator->TabStop = false;
			// 
			// lblTara
			// 
			this->lblTara->AutoSize = true;
			this->lblTara->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblTara->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblTara->Location = System::Drawing::Point(4, 1);
			this->lblTara->Name = L"lblTara";
			this->lblTara->Size = System::Drawing::Size(116, 64);
			this->lblTara->TabIndex = 3;
			this->lblTara->Text = L"Тара  ";
			this->lblTara->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblStabil
			// 
			this->lblStabil->AutoSize = true;
			this->lblStabil->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblStabil->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblStabil->Location = System::Drawing::Point(4, 67);
			this->lblStabil->Margin = System::Windows::Forms::Padding(3, 1, 3, 1);
			this->lblStabil->Name = L"lblStabil";
			this->lblStabil->Size = System::Drawing::Size(116, 62);
			this->lblStabil->TabIndex = 4;
			this->lblStabil->Text = L"Стабил";
			this->lblStabil->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblNol
			// 
			this->lblNol->AutoSize = true;
			this->lblNol->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblNol->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblNol->Location = System::Drawing::Point(4, 131);
			this->lblNol->Name = L"lblNol";
			this->lblNol->Size = System::Drawing::Size(116, 66);
			this->lblNol->TabIndex = 5;
			this->lblNol->Text = L"Ноль ";
			this->lblNol->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblVes
			// 
			this->lblVes->AutoSize = true;
			this->lblVes->BackColor = System::Drawing::SystemColors::ControlText;
			this->lblVes->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblVes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 54.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblVes->ForeColor = System::Drawing::Color::Red;
			this->lblVes->Location = System::Drawing::Point(166, 4);
			this->lblVes->Margin = System::Windows::Forms::Padding(4);
			this->lblVes->Name = L"lblVes";
			this->lblVes->Size = System::Drawing::Size(506, 196);
			this->lblVes->TabIndex = 1;
			this->lblVes->Text = L"8888.888";
			this->lblVes->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tableLayoutPanel7
			// 
			this->tableLayoutPanel7->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel7->ColumnCount = 2;
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				30)));
			this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				70)));
			this->tableLayoutPanel7->Controls->Add(this->picBoxShtIndicator, 0, 2);
			this->tableLayoutPanel7->Controls->Add(this->picBoxKgIndicator, 0, 0);
			this->tableLayoutPanel7->Controls->Add(this->lblKg, 1, 0);
			this->tableLayoutPanel7->Controls->Add(this->lblT, 1, 1);
			this->tableLayoutPanel7->Controls->Add(this->lblSht, 1, 2);
			this->tableLayoutPanel7->Controls->Add(this->picBoxTindicator, 0, 1);
			this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel7->Location = System::Drawing::Point(679, 3);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 3;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(102, 198);
			this->tableLayoutPanel7->TabIndex = 2;
			// 
			// picBoxShtIndicator
			// 
			this->picBoxShtIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxShtIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxShtIndicator->Location = System::Drawing::Point(4, 139);
			this->picBoxShtIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxShtIndicator->Name = L"picBoxShtIndicator";
			this->picBoxShtIndicator->Size = System::Drawing::Size(23, 50);
			this->picBoxShtIndicator->TabIndex = 3;
			this->picBoxShtIndicator->TabStop = false;
			// 
			// picBoxKgIndicator
			// 
			this->picBoxKgIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxKgIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxKgIndicator->Location = System::Drawing::Point(4, 9);
			this->picBoxKgIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxKgIndicator->Name = L"picBoxKgIndicator";
			this->picBoxKgIndicator->Size = System::Drawing::Size(23, 48);
			this->picBoxKgIndicator->TabIndex = 1;
			this->picBoxKgIndicator->TabStop = false;
			// 
			// lblKg
			// 
			this->lblKg->AutoSize = true;
			this->lblKg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblKg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKg->Location = System::Drawing::Point(34, 1);
			this->lblKg->Name = L"lblKg";
			this->lblKg->Size = System::Drawing::Size(64, 64);
			this->lblKg->TabIndex = 4;
			this->lblKg->Text = L"Кг";
			this->lblKg->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblT
			// 
			this->lblT->AutoSize = true;
			this->lblT->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblT->Location = System::Drawing::Point(34, 66);
			this->lblT->Name = L"lblT";
			this->lblT->Size = System::Drawing::Size(64, 64);
			this->lblT->TabIndex = 5;
			this->lblT->Text = L"Т ";
			this->lblT->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblSht
			// 
			this->lblSht->AutoSize = true;
			this->lblSht->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblSht->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblSht->Location = System::Drawing::Point(34, 131);
			this->lblSht->Name = L"lblSht";
			this->lblSht->Size = System::Drawing::Size(64, 66);
			this->lblSht->TabIndex = 6;
			this->lblSht->Text = L"Шт";
			this->lblSht->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// picBoxTindicator
			// 
			this->picBoxTindicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxTindicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxTindicator->Location = System::Drawing::Point(4, 74);
			this->picBoxTindicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxTindicator->Name = L"picBoxTindicator";
			this->picBoxTindicator->Size = System::Drawing::Size(23, 48);
			this->picBoxTindicator->TabIndex = 7;
			this->picBoxTindicator->TabStop = false;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel8->ColumnCount = 2;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				94.81383F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				5.18617F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				20)));
			this->tableLayoutPanel8->Controls->Add(this->lblSvyazSServerom, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->picBoxMESIndicator, 1, 0);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(1, 392);
			this->tableLayoutPanel8->Margin = System::Windows::Forms::Padding(1);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(788, 22);
			this->tableLayoutPanel8->TabIndex = 2;
			// 
			// lblSvyazSServerom
			// 
			this->lblSvyazSServerom->AutoSize = true;
			this->lblSvyazSServerom->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblSvyazSServerom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblSvyazSServerom->Location = System::Drawing::Point(4, 1);
			this->lblSvyazSServerom->Name = L"lblSvyazSServerom";
			this->lblSvyazSServerom->Size = System::Drawing::Size(738, 20);
			this->lblSvyazSServerom->TabIndex = 2;
			this->lblSvyazSServerom->Text = L"Связь с сервером";
			this->lblSvyazSServerom->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->lblSvyazSServerom->Click += gcnew System::EventHandler(this, &Form1::lblMES_Click);
			// 
			// picBoxMESIndicator
			// 
			this->picBoxMESIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxMESIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxMESIndicator->Location = System::Drawing::Point(749, 4);
			this->picBoxMESIndicator->Name = L"picBoxMESIndicator";
			this->picBoxMESIndicator->Size = System::Drawing::Size(35, 14);
			this->picBoxMESIndicator->TabIndex = 5;
			this->picBoxMESIndicator->TabStop = false;
			// 
			// tableLayoutPanel5
			// 
			this->tableLayoutPanel5->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel5->ColumnCount = 5;
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				11.87739F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				21.96679F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				25.92593F)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20)));
			this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				20)));
			this->tableLayoutPanel5->Controls->Add(this->checkBoxSelect, 3, 2);
			this->tableLayoutPanel5->Controls->Add(this->checkBoxMode, 2, 2);
			this->tableLayoutPanel5->Controls->Add(this->checkBoxTara, 1, 2);
			this->tableLayoutPanel5->Controls->Add(this->lblIpAddress, 0, 0);
			this->tableLayoutPanel5->Controls->Add(this->lblPort, 0, 1);
			this->tableLayoutPanel5->Controls->Add(this->lblChastotaOprosa, 3, 0);
			this->tableLayoutPanel5->Controls->Add(this->btnPrimenit, 4, 1);
			this->tableLayoutPanel5->Controls->Add(this->txtBxIpAddress, 1, 0);
			this->tableLayoutPanel5->Controls->Add(this->txtBxPort, 1, 1);
			this->tableLayoutPanel5->Controls->Add(this->txtBxChastotaOprosa, 4, 0);
			this->tableLayoutPanel5->Controls->Add(this->cmbBxVesoizmeritel, 2, 1);
			this->tableLayoutPanel5->Controls->Add(this->btnObnovit, 2, 0);
			this->tableLayoutPanel5->Controls->Add(this->chckBxFullscreen, 3, 1);
			this->tableLayoutPanel5->Controls->Add(this->checkBoxNull, 0, 2);
			this->tableLayoutPanel5->Controls->Add(this->buttonPass, 4, 2);
			this->tableLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel5->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
			this->tableLayoutPanel5->RowCount = 3;
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 28)));
			this->tableLayoutPanel5->Size = System::Drawing::Size(784, 87);
			this->tableLayoutPanel5->TabIndex = 3;
			// 
			// checkBoxSelect
			// 
			this->checkBoxSelect->AutoSize = true;
			this->checkBoxSelect->Location = System::Drawing::Point(472, 60);
			this->checkBoxSelect->Name = L"checkBoxSelect";
			this->checkBoxSelect->Size = System::Drawing::Size(59, 17);
			this->checkBoxSelect->TabIndex = 5;
			this->checkBoxSelect->Text = L"Выбор";
			this->checkBoxSelect->UseVisualStyleBackColor = true;
			// 
			// checkBoxMode
			// 
			this->checkBoxMode->AutoSize = true;
			this->checkBoxMode->Location = System::Drawing::Point(269, 60);
			this->checkBoxMode->Name = L"checkBoxMode";
			this->checkBoxMode->Size = System::Drawing::Size(61, 17);
			this->checkBoxMode->TabIndex = 4;
			this->checkBoxMode->Text = L"Режим";
			this->checkBoxMode->UseVisualStyleBackColor = true;
			// 
			// checkBoxTara
			// 
			this->checkBoxTara->AutoSize = true;
			this->checkBoxTara->Location = System::Drawing::Point(97, 60);
			this->checkBoxTara->Name = L"checkBoxTara";
			this->checkBoxTara->Size = System::Drawing::Size(51, 17);
			this->checkBoxTara->TabIndex = 3;
			this->checkBoxTara->Text = L"Тара";
			this->checkBoxTara->UseVisualStyleBackColor = true;
			// 
			// lblIpAddress
			// 
			this->lblIpAddress->AutoSize = true;
			this->lblIpAddress->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblIpAddress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblIpAddress->Location = System::Drawing::Point(4, 4);
			this->lblIpAddress->Margin = System::Windows::Forms::Padding(3);
			this->lblIpAddress->Name = L"lblIpAddress";
			this->lblIpAddress->Size = System::Drawing::Size(86, 21);
			this->lblIpAddress->TabIndex = 0;
			this->lblIpAddress->Text = L"IP адрес";
			this->lblIpAddress->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblPort
			// 
			this->lblPort->AutoSize = true;
			this->lblPort->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblPort->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblPort->Location = System::Drawing::Point(4, 32);
			this->lblPort->Margin = System::Windows::Forms::Padding(3);
			this->lblPort->Name = L"lblPort";
			this->lblPort->Size = System::Drawing::Size(86, 21);
			this->lblPort->TabIndex = 1;
			this->lblPort->Text = L"Порт";
			this->lblPort->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblChastotaOprosa
			// 
			this->lblChastotaOprosa->AutoSize = true;
			this->lblChastotaOprosa->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblChastotaOprosa->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblChastotaOprosa->Location = System::Drawing::Point(472, 1);
			this->lblChastotaOprosa->Name = L"lblChastotaOprosa";
			this->lblChastotaOprosa->Size = System::Drawing::Size(149, 27);
			this->lblChastotaOprosa->TabIndex = 0;
			this->lblChastotaOprosa->Text = L"Частота опроса, мс";
			this->lblChastotaOprosa->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnPrimenit
			// 
			this->btnPrimenit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnPrimenit->Location = System::Drawing::Point(628, 32);
			this->btnPrimenit->Name = L"btnPrimenit";
			this->btnPrimenit->Size = System::Drawing::Size(152, 21);
			this->btnPrimenit->TabIndex = 0;
			this->btnPrimenit->Text = L"Применить";
			this->btnPrimenit->UseVisualStyleBackColor = true;
			this->btnPrimenit->Click += gcnew System::EventHandler(this, &Form1::btnPrimenit_Click);
			// 
			// txtBxIpAddress
			// 
			this->txtBxIpAddress->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtBxIpAddress->Location = System::Drawing::Point(97, 4);
			this->txtBxIpAddress->Name = L"txtBxIpAddress";
			this->txtBxIpAddress->Size = System::Drawing::Size(165, 20);
			this->txtBxIpAddress->TabIndex = 0;
			// 
			// txtBxPort
			// 
			this->txtBxPort->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtBxPort->Location = System::Drawing::Point(97, 32);
			this->txtBxPort->Name = L"txtBxPort";
			this->txtBxPort->Size = System::Drawing::Size(165, 20);
			this->txtBxPort->TabIndex = 0;
			// 
			// txtBxChastotaOprosa
			// 
			this->txtBxChastotaOprosa->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtBxChastotaOprosa->Location = System::Drawing::Point(628, 4);
			this->txtBxChastotaOprosa->Name = L"txtBxChastotaOprosa";
			this->txtBxChastotaOprosa->Size = System::Drawing::Size(152, 20);
			this->txtBxChastotaOprosa->TabIndex = 0;
			this->txtBxChastotaOprosa->Text = L"500";
			// 
			// cmbBxVesoizmeritel
			// 
			this->cmbBxVesoizmeritel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cmbBxVesoizmeritel->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbBxVesoizmeritel->Enabled = false;
			this->cmbBxVesoizmeritel->FormattingEnabled = true;
			this->cmbBxVesoizmeritel->Location = System::Drawing::Point(269, 32);
			this->cmbBxVesoizmeritel->Name = L"cmbBxVesoizmeritel";
			this->cmbBxVesoizmeritel->Size = System::Drawing::Size(196, 21);
			this->cmbBxVesoizmeritel->TabIndex = 0;
			// 
			// btnObnovit
			// 
			this->btnObnovit->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnObnovit->Location = System::Drawing::Point(269, 4);
			this->btnObnovit->Name = L"btnObnovit";
			this->btnObnovit->Size = System::Drawing::Size(196, 21);
			this->btnObnovit->TabIndex = 0;
			this->btnObnovit->Text = L"Обновить";
			this->btnObnovit->UseVisualStyleBackColor = true;
			this->btnObnovit->Click += gcnew System::EventHandler(this, &Form1::btnObnovit_Click);
			// 
			// chckBxFullscreen
			// 
			this->chckBxFullscreen->AutoSize = true;
			this->chckBxFullscreen->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->chckBxFullscreen->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chckBxFullscreen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->chckBxFullscreen->Location = System::Drawing::Point(472, 32);
			this->chckBxFullscreen->Name = L"chckBxFullscreen";
			this->chckBxFullscreen->Size = System::Drawing::Size(149, 21);
			this->chckBxFullscreen->TabIndex = 0;
			this->chckBxFullscreen->Text = L"Во весь экран";
			this->chckBxFullscreen->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->chckBxFullscreen->UseVisualStyleBackColor = true;
			// 
			// checkBoxNull
			// 
			this->checkBoxNull->AutoSize = true;
			this->checkBoxNull->Location = System::Drawing::Point(4, 60);
			this->checkBoxNull->Name = L"checkBoxNull";
			this->checkBoxNull->Size = System::Drawing::Size(52, 17);
			this->checkBoxNull->TabIndex = 2;
			this->checkBoxNull->Text = L"Ноль";
			this->checkBoxNull->UseVisualStyleBackColor = true;
			// 
			// buttonPass
			// 
			this->buttonPass->Location = System::Drawing::Point(628, 60);
			this->buttonPass->Name = L"buttonPass";
			this->buttonPass->Size = System::Drawing::Size(152, 23);
			this->buttonPass->TabIndex = 6;
			this->buttonPass->Text = L"Изменить пароль";
			this->buttonPass->UseVisualStyleBackColor = true;
			this->buttonPass->Click += gcnew System::EventHandler(this, &Form1::buttonPass_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(40, 463);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"label2";
			this->label2->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(790, 440);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->toolStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Удаленный монитор весоизмерителя";
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxTaraIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxStabilIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxNolIndicator))->EndInit();
			this->tableLayoutPanel7->ResumeLayout(false);
			this->tableLayoutPanel7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxShtIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxKgIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxTindicator))->EndInit();
			this->tableLayoutPanel8->ResumeLayout(false);
			this->tableLayoutPanel8->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxMESIndicator))->EndInit();
			this->tableLayoutPanel5->ResumeLayout(false);
			this->tableLayoutPanel5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: void inLoad(void) 
		 {
			 //добавляем шрифтик
			//System::Drawing::Text::PrivateFontCollection clect;
			//clect.AddFontFile("1111.ttf");
			//System::Drawing::Font fnt; fnt.

			
			//lblVes->Font = gcnew System::Drawing::Font( clect.Families[0] , 23,
				//button1->Font->Style,
			//	Drawing::FontStyle::Italic,
			//	lblVes->Font->Unit);
			//this->Top= 400;

//загружаем настройки из файла
			pugi::xml_document doc;
			//указываем файл
			if (doc.load_file("settings.xml"))
			{
			//ищем по ноду connection
			pugi::xml_node tool = doc.child("Connection");
			//загружаем соответствующие данные
			txtBxIpAddress->Text = gcnew System::String(tool.attribute("IP_address").value());
			txtBxPort->Text = gcnew System::String(tool.attribute("Port").value());
			txtBxChastotaOprosa->Text = gcnew System::String(tool.attribute("Chastota_oprosa").value());
			
			
					
			//название весоизмерителя
			String ^vesoizmeritel;
			vesoizmeritel = gcnew System::String(tool.attribute("Vesoizmeritel").value());
			if (vesoizmeritel != "-1")
			{
			this->_nomerVesy = gcnew System::String(tool.attribute("Vesoizmeritel").value());
			cmbBxVesoizmeritel->Items->Add(this->_nomerVesy);
			cmbBxVesoizmeritel->SelectedIndex = 0;
			this->lblName->Text = this->_nomerVesy;
			}
	
			 tool = doc.child("Position");//положение на экране
			//проверяем на полноэкранность
			String^ fulscrn = gcnew System::String(tool.attribute("Fullscreen").value());
			if (fulscrn == "yes")
			{
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
				this->TopMost = true;
				chckBxFullscreen->Checked = true ;
			}
			//положение слева
			//int poloj
				
			_windowLeft	= Int32::Parse( gcnew System::String(tool.attribute("Left").value()));
			//this->Left = poloj;
			//положение сверху
		//	poloj 
				
			_windowTop	= Int32::Parse( gcnew System::String(tool.attribute("Top").value()));


		//	this->Top = poloj;
		//	form
			//ширина окна
			this->Width =  Int32::Parse(gcnew System::String(tool.attribute("Width").value()));
			//высота окна
			this->Height =Int32::Parse( gcnew System::String(tool.attribute("Height").value()));

			tool = doc.child("ButtonControl");
			_buttonControl->Add(bool::Parse(gcnew System::String(tool.attribute("Null").value())));
			_buttonControl->Add(bool::Parse(gcnew System::String(tool.attribute("Tara").value())));
			_buttonControl->Add(bool::Parse(gcnew System::String(tool.attribute("Mode").value())));
			_buttonControl->Add(bool::Parse(gcnew System::String(tool.attribute("Select").value())));

						//пароль
			tool = doc.child("Password");
			currentHashPassword = gcnew System::String(tool.attribute("Hash").value()); 
			
			}
			else {MessageBox::Show("Файла с настроками не найдено. Заданы настройки по умолчанию.");
				this->Width = 800;
				this->Height = 470;
							//DeFAULT

				_buttonControl->Add(true);
				_buttonControl->Add(false);
				_buttonControl->Add(false);
				_buttonControl->Add(false);
				currentHashPassword = getHashSha256("1234");
			
			}

		
			checkBoxNull->Checked =  _buttonControl[0];
			checkBoxTara->Checked= _buttonControl[1];
			checkBoxMode->Checked = _buttonControl[2];
			checkBoxSelect->Checked = _buttonControl[3];

			btnNol->Enabled =  _buttonControl[0];
			btnTara->Enabled = _buttonControl[1];
			btnRejim->Enabled =  _buttonControl[2];
			btnVibor->Enabled =  _buttonControl[3];
		 }

	private: char* SystemStringToChar(System::String^ string) 
{
    return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string);
}

			 private: System::String^ CharToSystemString(pugi::char_t* ch) 
{
    return gcnew System::String(ch);
}


			private: float getTextSize(Label ^lbl)
		 {
			 int W = lbl->Width;
			 int H = lbl->Height;
			 float currentSize = 6;
			 label2->Font = lbl->Font;
			 label2->Text = lbl->Text;
			 label2->Font =gcnew System::Drawing::Font(label2->Font->Name, 
                currentSize, label2->Font->Style, label2->Font->Unit);

			bool b = false;
			while (!b)
			{
				if (W > label2->Width && H > label2->Height)
				{
					currentSize = currentSize + 0.5;
					label2->Font =gcnew System::Drawing::Font
						(
					
						 label2->Font->Name,
						 currentSize,
						 label2->Font->Style,
						 label2->Font->Unit
						);

				}
				else { b = true;}
			} 


			 return currentSize -0.5 ;
		 }
	
		 private: float getTextSize2(Label ^lbl)
		 {
			 int W = lbl->Width;
			 int H = lbl->Height;
			 float currentSize = 6;
			 label2->Font = lbl->Font;
			 label2->Text = "8888.888";
			 label2->Font =gcnew System::Drawing::Font(CurrentFont, 
                currentSize, label2->Font->Style, label2->Font->Unit);

			bool b = false;
			while (!b)
			{
				if (W > label2->Width && H > label2->Height)
				{
					currentSize = currentSize + 0.5;
					label2->Font =gcnew System::Drawing::Font
						(
					
						 CurrentFont,
						 currentSize ,
						 label2->Font->Style,
						 label2->Font->Unit
						);

				}
				else { b = true;}
			} 


			 return currentSize -0.5 ;
		 }
private: void resizeLabels(void)
				  {
					  lblVes->Font = gcnew System::Drawing::Font(CurrentFont, 
				 getTextSize2(lblVes), lblVes->Font->Style, lblVes->Font->Unit);

			 lblTara->Font = gcnew System::Drawing::Font(lblTara->Font->Name, 
				 getTextSize(lblTara),lblTara->Font->Style,lblTara->Font->Unit);

			 lblStabil->Font = gcnew System::Drawing::Font(lblStabil->Font->Name, 
				 getTextSize(lblStabil),lblStabil->Font->Style,lblStabil->Font->Unit);

			 lblNol->Font = gcnew System::Drawing::Font(lblNol->Font->Name, 
				 getTextSize(lblNol), lblNol->Font->Style, lblNol->Font->Unit);

			 lblSht->Font = gcnew System::Drawing::Font(lblSht->Font->Name, 
				 getTextSize(lblSht), lblSht->Font->Style, lblSht->Font->Unit);

			 lblT->Font = gcnew System::Drawing::Font(lblT->Font->Name, 
				 getTextSize(lblT), lblT->Font->Style, lblT->Font->Unit);
				
			 lblKg->Font = gcnew System::Drawing::Font(lblKg->Font->Name, 
				 getTextSize(lblKg), lblKg->Font->Style, lblKg->Font->Unit);

			 lblNolButton->Font = gcnew System::Drawing::Font(lblNolButton->Font->Name, 
				 getTextSize(lblNolButton), lblNolButton->Font->Style, lblNolButton->Font->Unit);

			 lblTaraButton->Font = gcnew System::Drawing::Font(lblTaraButton->Font->Name, 
				 getTextSize(lblTaraButton), lblTaraButton->Font->Style, lblTaraButton->Font->Unit);

			 lblRejimButton->Font = gcnew System::Drawing::Font(lblRejimButton->Font->Name, 
				 getTextSize(lblRejimButton), lblRejimButton->Font->Style, lblRejimButton->Font->Unit);

			 lblViborButton->Font = gcnew System::Drawing::Font(lblViborButton->Font->Name, 
				 getTextSize(lblViborButton), lblViborButton->Font->Style, lblViborButton->Font->Unit);

			 lblSvyazSServerom->Font = gcnew System::Drawing::Font(lblSvyazSServerom->Font->Name, 
				 getTextSize(lblSvyazSServerom), lblSvyazSServerom->Font->Style, lblSvyazSServerom->Font->Unit);
			 

				  }

private: System::Void btnObnovit_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Обновим весоизмерители
try{
	array<String^>^ ResMsg = gcnew array<String^>(10);
	cmbBxVesoizmeritel->Enabled = true ;
	cmbBxVesoizmeritel->Text = "Выберите весоизмеритель" ;
	if (_client){
		_client->Setup(this->txtBxIpAddress->Text, Int32::Parse(this->txtBxPort->Text));
	}
	
	else 
	{
			_client = gcnew CTCPClient(this->txtBxIpAddress->Text, Int32::Parse(this->txtBxPort->Text));
					
	}
	//this->timer1->Enabled = false;
	//Запрашиваем данные
	ResMsg = _client->getDevice();
	//Проверим волшебное слово
	if (ResMsg[0] == "get_device") {

		cmbBxVesoizmeritel->Items->Clear();

		for (int i = 1; i < 10; i++)
		{
			if (ResMsg[i] != "") cmbBxVesoizmeritel->Items->Add(ResMsg[i]);
		}
	}
}
catch (Exception^ ex) 
   {
	   //MessageBox e;

	   MessageBox::Show("Сервер не найден, проверьте настройки IP и порт");
	   cmbBxVesoizmeritel->Enabled = false ;
}
}


private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
			 resizeLabels();
			// this->Top= 600;
			// this->Left = 600;

				// btnPrimenit->Text = "sddgr";

		 }
private: System::Void btnPrimenit_Click(System::Object^  sender, System::EventArgs^  e) {
			 if ((this->cmbBxVesoizmeritel->Enabled) && (this->cmbBxVesoizmeritel->SelectedIndex != -1))
			 {//Если сервер найден и выбрано весоизмерительное устройство
				_nomerVesy = cmbBxVesoizmeritel->SelectedItem->ToString();
				tableLayoutPanel1->RowStyles[0]->Height = 0;
				resizeLabels();	
				lblName->Text = cmbBxVesoizmeritel->SelectedItem->ToString() ;
				cmbBxVesoizmeritel->Enabled = false;
				this->Text = cmbBxVesoizmeritel->SelectedItem->ToString() ;

				//Сохраняем настойки
				_ip = this->txtBxIpAddress->Text;
				_port = Int32::Parse(this->txtBxPort->Text);
				this->timer1->Interval = Int32::Parse(this->txtBxChastotaOprosa->Text);

				pugi::xml_document doc;

				 ////сохранение настроек соединения
				 pugi::xml_node node = doc.append_child("Connection");
				 ////ip address
				 node.append_attribute("IP_address") = SystemStringToChar(txtBxIpAddress->Text->ToString());
				 ////port
				 node.append_attribute("Port") = SystemStringToChar(txtBxPort->Text->ToString());
				 ////Весоизмеритель
				 node.append_attribute("Vesoizmeritel") = SystemStringToChar(cmbBxVesoizmeritel->SelectedItem->ToString());
				 ////Частота опроса
				 node.append_attribute("Chastota_oprosa") = SystemStringToChar(txtBxChastotaOprosa->Text->ToString());
				
				 
				 pugi::xml_node node1 = doc.append_child("Position");
				 
				 ////во весь экран
				 if (chckBxFullscreen->Checked)
				 {node1.append_attribute("Fullscreen") = "yes";}
				 else {node1.append_attribute("Fullscreen") = "no";}

				 //ширина формы
				 node1.append_attribute("Width") = this->Width ;
				 //высота формы
				 node1.append_attribute("Height") = this->Height ;
				 //положение сверху
				 node1.append_attribute("Top") = this->Top ; 
				 //полложение слева
				 node1.append_attribute("Left") = this->Left ;


				 //сохраняем настройку "поверх всех окон"
				 if (this->TopMost)
				 {node1.append_attribute("TopMost") = "yes" ;}
				 else
				 {node1.append_attribute("TopMost") = "no" ;}
					
				 _buttonControl[0] = checkBoxNull->Checked;
				 _buttonControl[1] = checkBoxTara->Checked;
				 _buttonControl[2] = checkBoxMode->Checked;
				 _buttonControl[3] = checkBoxSelect->Checked;

				 
				 //Button Control 
					node1 = doc.append_child("ButtonControl");
					node1.append_attribute("Null") = SystemStringToChar( _buttonControl[0].ToString());
					node1.append_attribute("Tara") = SystemStringToChar(_buttonControl[1].ToString());
					node1.append_attribute("Mode") = SystemStringToChar(_buttonControl[2].ToString());
					node1.append_attribute("Select") = SystemStringToChar(_buttonControl[3].ToString());
					
								//Password 
				node1 = doc.append_child("Password");
				node1.append_attribute("Hash") = SystemStringToChar(currentHashPassword);
			
					
				 ////сохраняем настройки в файл
				 doc.save_file("settings.xml");
				
				btnNol->Enabled =  _buttonControl[0];
				btnTara->Enabled = _buttonControl[1];
				btnRejim->Enabled =  _buttonControl[2];
				btnVibor->Enabled =  _buttonControl[3];

				this->timer1->Interval = Int32::Parse(txtBxChastotaOprosa->Text);
				this->timer1->Enabled= 1;
			 }
			 else {
				 MessageBox::Show("Выберите весоизмерительное устройство");
			 }

 		 }
private: System::Void lblName_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void lblData_Click(System::Object^  sender, System::EventArgs^  e) {
			tableLayoutPanel1->RowStyles[0]->Height = 66;
			resizeLabels();

		 }
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(_showSettings)
			 {//если окно настройки видимо
				tableLayoutPanel1->RowStyles[0]->Height = 0;
				resizeLabels();
				_showSettings = false;			
			 }
			 else 
			 {
				if (!ShowInPutPassword()) {
 				 return;
				 }
	
				_showSettings = true;
				tableLayoutPanel1->RowStyles[0]->Height = _SettingHeight;
				resizeLabels();
			 }
		 }
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			 
					
				if (this->FormBorderStyle == System::Windows::Forms::FormBorderStyle::Sizable)
				{
					this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
					this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
					this->TopMost = true;
				}
				else
				{
					this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
					this->WindowState = System::Windows::Forms::FormWindowState::Normal;
					this->TopMost = false;
				}


		 }
private: System::Void lblMES_Click(System::Object^  sender, System::EventArgs^  e) {
		 }



private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //Запрос данных и установка значений
			
try{
	array<String^>^ ResMsg = gcnew array<String^>(10);
	if (_client){
		_client->Setup(_ip, _port);
	}
	
	else 
	{
			_client = gcnew CTCPClient(_ip, _port);
					
	}
	
	//Запрашиваем данные
	ResMsg = _client->getData(this->_nomerVesy);
	//Проверим волшебное слово
	if (ResMsg[0] == "get_data") {

		//Задаем даныне

		lblVes->Text = ResMsg[2]; //Вес

		if (bool::Parse(ResMsg[3])) //Тара
			picBoxTaraIndicator->BackColor = Color::Red;
		else
			picBoxTaraIndicator->BackColor = Color::Black;

		if (bool::Parse(ResMsg[4])) //Стабильность
			picBoxStabilIndicator->BackColor = Color::Red;
		else
			picBoxStabilIndicator->BackColor = Color::Black;

		if (bool::Parse(ResMsg[5])) //Ноль
			picBoxNolIndicator->BackColor = Color::Red;
		else
			picBoxNolIndicator->BackColor = Color::Black;

		if (bool::Parse(ResMsg[6])) //КГ
			picBoxKgIndicator->BackColor = Color::Red;
		else
			picBoxKgIndicator->BackColor = Color::Black;

		if (bool::Parse(ResMsg[7])) //Т
			picBoxTindicator->BackColor = Color::Red;
		else
			picBoxTindicator->BackColor = Color::Black;
		
		if (bool::Parse(ResMsg[8])) //шт
			picBoxShtIndicator->BackColor = Color::Red;
		else
			picBoxShtIndicator->BackColor = Color::Black;
		//Говорим что связь есть
		picBoxMESIndicator->BackColor = Color::Green;
	_countConnect = 0;

	}
}
catch (Exception^ ex) 
   {
	   _countConnect += 1;
	   lblVes->Text = "OFFLINE";
	   picBoxTaraIndicator->BackColor = Color::Black;
	   picBoxStabilIndicator->BackColor = Color::Black;
	   picBoxNolIndicator->BackColor = Color::Black;
	   picBoxKgIndicator->BackColor = Color::Black;
	   picBoxTindicator->BackColor = Color::Black;
	   picBoxShtIndicator->BackColor = Color::Black;
	   //picBoxMESIndicator->BackColor = Color::Yellow;


	/*	if (_countConnect > 20)
			 {
				//значит подключение отвалилось
				
				picBoxMESIndicator->BackColor = Color::Red;
				//Ждем секунду
				this->timer1->Enabled = false;

			 }
*/

	   picBoxMESIndicator->BackColor = Color::Red;
	  // System::Threading::Thread::Sleep(5000);
	   this->timer1->Enabled = false;
	   this->timer2->Interval = 5000;
	   this->timer2->Enabled = true;
   }



		 }
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Запускаем таймер
			 this->timer1->Interval = Int32::Parse(this->txtBxChastotaOprosa->Text->ToString());
			 this->timer1->Enabled = true;

		 }
private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Выключаем таймер
		this->timer1->Enabled = false;
		//Выключаем все индикаторы
		lblVes->Text = "OFFLINE";
		picBoxTaraIndicator->BackColor = Color::Black;
		picBoxStabilIndicator->BackColor = Color::Black;
		picBoxNolIndicator->BackColor = Color::Black;
		picBoxKgIndicator->BackColor = Color::Black;
		picBoxTindicator->BackColor = Color::Black;
		picBoxShtIndicator->BackColor = Color::Black;
		picBoxMESIndicator->BackColor = Color::Red;
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //Для тестирования подключения

			 this->timer1->Enabled = true;
		 }
private: System::Void btnNol_Click(System::Object^  sender, System::EventArgs^  e) {
			 //Команда ноль
	if (_client)
	{
		_client->Setup(_ip, _port);
	}
		
	else 
	{
		_client = gcnew CTCPClient(_ip, _port);
					
	}
	_client->getCmd(this->_nomerVesy, "A");
		 }
private: System::Void btnTara_Click(System::Object^  sender, System::EventArgs^  e) {
	if (_client)
	{
		_client->Setup(_ip, _port);
	}
		
	else 
	{
		_client = gcnew CTCPClient(_ip, _port);
					
	}
	_client->getCmd(this->_nomerVesy, "B");
		 }
private: System::Void btnRejim_Click(System::Object^  sender, System::EventArgs^  e) {
	if (_client)
	{
		_client->Setup(_ip, _port);
	}
		
	else 
	{
		_client = gcnew CTCPClient(_ip, _port);
					
	}
	_client->getCmd(this->_nomerVesy, "D");
		 
		 
		 }
private: System::Void btnVibor_Click(System::Object^  sender, System::EventArgs^  e) {
	if (_client)
	{
		_client->Setup(_ip, _port);
	}
		
	else 
	{
		_client = gcnew CTCPClient(_ip, _port);
					
	}
	_client->getCmd(this->_nomerVesy, "H");
		 
		 }
private: System::Void tlStpBtnPoverhVsehOkon_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->TopMost) //если поверх всех
			{
				this->TopMost = false; // то сделать не поверх
				tlStpBtnPoverhVsehOkon->BackColor = toolStripButton1->BackColor;
			} 
			else 
			{// а если не поверх, то сделать поверх
				this->TopMost = true;
				tlStpBtnPoverhVsehOkon->BackColor = Color::Gray ;
			} 
		 }


		 //действие при закрытии формы. тут сохраняются настройки. все те же , что и при кнопке применить при настройке 
		 //удаленного монитора + поверх всех окон или нет + положение + размеры формы
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {


			 
//Сохраняем настойки
				_ip = this->txtBxIpAddress->Text;
				_port = Int32::Parse(this->txtBxPort->Text);
				this->timer1->Interval = Int32::Parse(this->txtBxChastotaOprosa->Text);

				pugi::xml_document doc;

				 ////сохранение настроек соединения
				 pugi::xml_node node = doc.append_child("Connection");
				 ////ip address
				 node.append_attribute("IP_address") = SystemStringToChar(txtBxIpAddress->Text->ToString());
				 ////port
				 node.append_attribute("Port") = SystemStringToChar(txtBxPort->Text->ToString());
				 ////Весоизмеритель
				 if (cmbBxVesoizmeritel->SelectedIndex != -1)
				 {node.append_attribute("Vesoizmeritel") = SystemStringToChar(cmbBxVesoizmeritel->SelectedItem->ToString());}
				 else {node.append_attribute("Vesoizmeritel") = "-1" ;}
				 ////Частота опроса
				 node.append_attribute("Chastota_oprosa") = SystemStringToChar(txtBxChastotaOprosa->Text->ToString());
				
				 pugi::xml_node node1 = doc.append_child("Position");
				 
				 ////во весь экран
				 if (chckBxFullscreen->Checked)
				 {node1.append_attribute("Fullscreen") = "yes";}
				 else {node1.append_attribute("Fullscreen") = "no";}

				 //ширина формы
				 node1.append_attribute("Width") = this->Width ;
				 //высота формы
				 node1.append_attribute("Height") = this->Height ;
				 //положение сверху
				 node1.append_attribute("Top") = this->Top ; 
				 //полложение слева
				 node1.append_attribute("Left") = this->Left ;
				
				 					

					
				 //сохраняем настройку "поверх всех окон"
				 if (this->TopMost)
				 {node1.append_attribute("TopMost") = "yes" ;}
				 else
				 {node1.append_attribute("TopMost") = "no" ;}

								 //Button Control 
					node1 = doc.append_child("ButtonControl");
					node1.append_attribute("Null") = SystemStringToChar( _buttonControl[0].ToString());
					node1.append_attribute("Tara") = SystemStringToChar(_buttonControl[1].ToString());
					node1.append_attribute("Mode") = SystemStringToChar(_buttonControl[2].ToString());
					node1.append_attribute("Select") = SystemStringToChar(_buttonControl[3].ToString());
				
								//Password 
			node1 = doc.append_child("Password");
			node1.append_attribute("Hash") = SystemStringToChar(currentHashPassword);
			
				 ////сохраняем настройки в файл
				 doc.save_file("settings.xml");
			
			
		 }
private: System::Void toolStripSeparator2_Click(System::Object^  sender, System::EventArgs^  e) {
			 lblVes->Text= "8888.888";
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	try{
			 this->Top =(int) (_windowTop);
		this->Left =(int) (_windowLeft);
	}
	catch (Exception ^e) {

	}
	}

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
private: bool ShowInPutPassword(void){
			 //Использование пароля

			InputBox^ input;
			 if (currentHashPassword == getHashSha256("1234"))
			 {
				 input = gcnew RemoteDisplay::InputBox("Доступ ограничен", "Стандартный пароль: 1234");
			 }
			else 
			 {
				input = gcnew RemoteDisplay::InputBox("Доступ ограничен", "Введите пароль");
				
			 }
			 
			 String^ inPutHash;

			if (input->ShowDialog( this ) == RemoteDisplay::DialogResult::OK) 
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


private: System::Void buttonPass_Click(System::Object^  sender, System::EventArgs^  e) {
//

			//
			InputBox^ input;
			input = gcnew RemoteDisplay::InputBox("Новый пароль", "Введите новый пароль");
			String^ inPutHash;
			if (input->ShowDialog( this ) == RemoteDisplay::DialogResult::OK) 
			{
				inPutHash = getHashSha256( input->getValue());
				MessageBox::Show("Новый пароль: " + input->getValue() + ". Будет сохранень при сохранение общих настроек", "Готово",  MessageBoxButtons::OK, MessageBoxIcon::Information);	
				currentHashPassword = inPutHash;
			}

		 }
};
}

