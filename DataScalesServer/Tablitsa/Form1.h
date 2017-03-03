#pragma once
#include "Model.h"
#include "LogCsv.h"
#include "stdlib.h"
#include "Orcl.h"

namespace Tablitsa {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


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
        Form1(CModel^ model, CLogCsv^ lg, String^ weight_name, String^ location, List<bool>^ buttonControl, bool vesKg)
		{

            InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			 _vesKg = vesKg;
             timer1->Enabled = true;
            timer1->Interval = 30;
            mdl = model;
            log = lg;
            _wght_name = weight_name;
            _location = location;
            this->lblName->Text = "Название: " + _wght_name;
            this->lblLocation->Text = "Раположение: " + _location;
            this->lblData->Text = "© ДАТА-Центр Автоматика 2013 г.";
			this->_setButtonControl(buttonControl);
            

			
		}
		void _setButtonControl(List<bool>^ buttonControl){
			btnNol->Enabled = buttonControl[0];
			btnTara->Enabled = buttonControl[1];
			btnRejim->Enabled = buttonControl[2];
			btnVibor->Enabled = buttonControl[3];

		}

		void SetPicMes(System::Drawing::Color color){
			picBoxMESIndicator->BackColor = color;
			
		};

		void SetPicDataTrack(System::Drawing::Color color){
			picBoxDataTrackIndicator->BackColor = color;
			
		};


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			//delete mdl;

            if (components)
			{
				delete components;
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
	private: System::Windows::Forms::Label^  lblVesoizmeritel;
	private: System::Windows::Forms::Label^  lblDataTrack;
	private: System::Windows::Forms::Label^  lblMES;






	private: System::Windows::Forms::PictureBox^  picBoxTindicator;
	private: System::Windows::Forms::PictureBox^  picBoxVesoizmeritelIndicator;
	private: System::Windows::Forms::PictureBox^  picBoxDataTrackIndicator;
	private: System::Windows::Forms::PictureBox^  picBoxMESIndicator;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::ComponentModel::IContainer^  components;
    private: System::Windows::Forms::ToolStripLabel^  lblName;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
    private: System::Windows::Forms::ToolStripLabel^  lblLocation;
    private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripLabel^  lblData;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
    CLogCsv^ log;
    CModel^ mdl;
    String^ _wght_name;
    String^ _location;
	bool _vesKg;
 

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
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());

			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->lblName = (gcnew System::Windows::Forms::ToolStripLabel());
            this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->lblLocation = (gcnew System::Windows::Forms::ToolStripLabel());
            this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->lblData = (gcnew System::Windows::Forms::ToolStripLabel());
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
			this->lblVesoizmeritel = (gcnew System::Windows::Forms::Label());
			this->lblDataTrack = (gcnew System::Windows::Forms::Label());
			this->lblMES = (gcnew System::Windows::Forms::Label());
			this->picBoxVesoizmeritelIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->picBoxDataTrackIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->picBoxMESIndicator = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxVesoizmeritelIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxDataTrackIndicator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxMESIndicator))->BeginInit();
			this->SuspendLayout();
			// 
			// toolStrip1
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->lblName, this->toolStripSeparator1, 
				this->lblLocation, this->toolStripSeparator2, this->lblData});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(476, 25);
			this->toolStrip1->TabIndex = 0;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel3, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel8, 0, 2);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 25);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 59.63855F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 40.36145F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(476, 165);
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
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 89);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 30)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(470, 52);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// btnNol
			// 
			this->btnNol->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnNol.BackgroundImage")));
			this->btnNol->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btnNol->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnNol->Location = System::Drawing::Point(21, 19);
			this->btnNol->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnNol->Name = L"btnNol";
			this->btnNol->Size = System::Drawing::Size(76, 29);
			this->btnNol->TabIndex = 0;
			this->btnNol->UseVisualStyleBackColor = true;
			this->btnNol->Click += gcnew System::EventHandler(this, &Form1::btnNol_Click);
			// 
			// btnTara
			// 
			this->btnTara->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnTara.BackgroundImage")));
			this->btnTara->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnTara->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnTara->Location = System::Drawing::Point(138, 19);
			this->btnTara->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnTara->Name = L"btnTara";
			this->btnTara->Size = System::Drawing::Size(76, 29);
			this->btnTara->TabIndex = 1;
			this->btnTara->UseVisualStyleBackColor = true;
			this->btnTara->Click += gcnew System::EventHandler(this, &Form1::btnTara_Click);
			// 
			// btnRejim
			// 
			this->btnRejim->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnRejim.BackgroundImage")));
			this->btnRejim->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnRejim->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnRejim->Location = System::Drawing::Point(255, 19);
			this->btnRejim->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnRejim->Name = L"btnRejim";
			this->btnRejim->Size = System::Drawing::Size(76, 29);
			this->btnRejim->TabIndex = 2;
			this->btnRejim->UseVisualStyleBackColor = true;
			this->btnRejim->Click += gcnew System::EventHandler(this, &Form1::btnRejim_Click);
			// 
			// btnVibor
			// 
			this->btnVibor->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"btnVibor.BackgroundImage")));
			this->btnVibor->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btnVibor->Dock = System::Windows::Forms::DockStyle::Fill;
			this->btnVibor->Location = System::Drawing::Point(372, 19);
			this->btnVibor->Margin = System::Windows::Forms::Padding(20, 3, 20, 3);
			this->btnVibor->Name = L"btnVibor";
			this->btnVibor->Size = System::Drawing::Size(77, 29);
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
			this->lblNolButton->Size = System::Drawing::Size(110, 14);
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
			this->lblTaraButton->Location = System::Drawing::Point(121, 1);
			this->lblTaraButton->Name = L"lblTaraButton";
			this->lblTaraButton->Size = System::Drawing::Size(110, 14);
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
			this->lblRejimButton->Location = System::Drawing::Point(238, 1);
			this->lblRejimButton->Name = L"lblRejimButton";
			this->lblRejimButton->Size = System::Drawing::Size(110, 14);
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
			this->lblViborButton->Location = System::Drawing::Point(355, 1);
			this->lblViborButton->Name = L"lblViborButton";
			this->lblViborButton->Size = System::Drawing::Size(111, 14);
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
			this->tableLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 1;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(470, 80);
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
			this->tableLayoutPanel4->Size = System::Drawing::Size(91, 74);
			this->tableLayoutPanel4->TabIndex = 0;
			// 
			// picBoxTaraIndicator
			// 
			this->picBoxTaraIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxTaraIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxTaraIndicator->Location = System::Drawing::Point(75, 9);
			this->picBoxTaraIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxTaraIndicator->Name = L"picBoxTaraIndicator";
			this->picBoxTaraIndicator->Size = System::Drawing::Size(12, 7);
			this->picBoxTaraIndicator->TabIndex = 0;
			this->picBoxTaraIndicator->TabStop = false;
			// 
			// picBoxStabilIndicator
			// 
			this->picBoxStabilIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxStabilIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxStabilIndicator->Location = System::Drawing::Point(75, 33);
			this->picBoxStabilIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxStabilIndicator->Name = L"picBoxStabilIndicator";
			this->picBoxStabilIndicator->Size = System::Drawing::Size(12, 7);
			this->picBoxStabilIndicator->TabIndex = 1;
			this->picBoxStabilIndicator->TabStop = false;
			// 
			// picBoxNolIndicator
			// 
			this->picBoxNolIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxNolIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxNolIndicator->Location = System::Drawing::Point(75, 57);
			this->picBoxNolIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxNolIndicator->Name = L"picBoxNolIndicator";
			this->picBoxNolIndicator->Size = System::Drawing::Size(12, 8);
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
			this->lblTara->Size = System::Drawing::Size(64, 23);
			this->lblTara->TabIndex = 3;
			this->lblTara->Text = L"Тара";
			this->lblTara->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblStabil
			// 
			this->lblStabil->AutoSize = true;
			this->lblStabil->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblStabil->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblStabil->Location = System::Drawing::Point(4, 26);
			this->lblStabil->Margin = System::Windows::Forms::Padding(3, 1, 3, 1);
			this->lblStabil->Name = L"lblStabil";
			this->lblStabil->Size = System::Drawing::Size(64, 21);
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
			this->lblNol->Location = System::Drawing::Point(4, 49);
			this->lblNol->Name = L"lblNol";
			this->lblNol->Size = System::Drawing::Size(64, 24);
			this->lblNol->TabIndex = 5;
			this->lblNol->Text = L"Ноль";
			this->lblNol->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblVes
			// 
			this->lblVes->AutoSize = true;
			this->lblVes->BackColor = System::Drawing::SystemColors::ControlText;
			this->lblVes->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblVes->Font = (gcnew System::Drawing::Font(L"1111111", 54.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblVes->ForeColor = System::Drawing::Color::Red;
			this->lblVes->Location = System::Drawing::Point(100, 0);
			this->lblVes->Name = L"lblVes";
			//this->lblVes->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->lblVes->Size = System::Drawing::Size(302, 80);
			this->lblVes->TabIndex = 1;
			this->lblVes->Text = L"8888889";
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
			this->tableLayoutPanel7->Location = System::Drawing::Point(408, 3);
			this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
			this->tableLayoutPanel7->RowCount = 3;
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 33.33333F)));
			this->tableLayoutPanel7->Size = System::Drawing::Size(59, 74);
			this->tableLayoutPanel7->TabIndex = 2;
			// 
			// picBoxShtIndicator
			// 
			this->picBoxShtIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxShtIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxShtIndicator->Location = System::Drawing::Point(4, 57);
			this->picBoxShtIndicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxShtIndicator->Name = L"picBoxShtIndicator";
			this->picBoxShtIndicator->Size = System::Drawing::Size(10, 8);
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
			this->picBoxKgIndicator->Size = System::Drawing::Size(10, 7);
			this->picBoxKgIndicator->TabIndex = 1;
			this->picBoxKgIndicator->TabStop = false;
			// 
			// lblKg
			// 
			this->lblKg->AutoSize = true;
			this->lblKg->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblKg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblKg->Location = System::Drawing::Point(21, 1);
			this->lblKg->Name = L"lblKg";
			this->lblKg->Size = System::Drawing::Size(34, 23);
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
			this->lblT->Location = System::Drawing::Point(21, 25);
			this->lblT->Name = L"lblT";
			this->lblT->Size = System::Drawing::Size(34, 23);
			this->lblT->TabIndex = 5;
			this->lblT->Text = L"Т";
			this->lblT->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblSht
			// 
			this->lblSht->AutoSize = true;
			this->lblSht->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblSht->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblSht->Location = System::Drawing::Point(21, 49);
			this->lblSht->Name = L"lblSht";
			this->lblSht->Size = System::Drawing::Size(34, 24);
			this->lblSht->TabIndex = 6;
			this->lblSht->Text = L"Шт";
			this->lblSht->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// picBoxTindicator
			// 
			this->picBoxTindicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxTindicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxTindicator->Location = System::Drawing::Point(4, 33);
			this->picBoxTindicator->Margin = System::Windows::Forms::Padding(3, 8, 3, 8);
			this->picBoxTindicator->Name = L"picBoxTindicator";
			this->picBoxTindicator->Size = System::Drawing::Size(10, 7);
			this->picBoxTindicator->TabIndex = 7;
			this->picBoxTindicator->TabStop = false;
			// 
			// tableLayoutPanel8
			// 
			this->tableLayoutPanel8->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
			this->tableLayoutPanel8->ColumnCount = 6;
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				20)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				20)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				23)));
			this->tableLayoutPanel8->Controls->Add(this->lblVesoizmeritel, 0, 0);
			this->tableLayoutPanel8->Controls->Add(this->lblDataTrack, 2, 0);
			this->tableLayoutPanel8->Controls->Add(this->lblMES, 4, 0);
			this->tableLayoutPanel8->Controls->Add(this->picBoxVesoizmeritelIndicator, 1, 0);
			this->tableLayoutPanel8->Controls->Add(this->picBoxDataTrackIndicator, 3, 0);
			this->tableLayoutPanel8->Controls->Add(this->picBoxMESIndicator, 5, 0);
			this->tableLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel8->Location = System::Drawing::Point(1, 145);
			this->tableLayoutPanel8->Margin = System::Windows::Forms::Padding(1);
			this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
			this->tableLayoutPanel8->RowCount = 1;
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 18)));
			this->tableLayoutPanel8->Size = System::Drawing::Size(474, 19);
			this->tableLayoutPanel8->TabIndex = 2;
			// 
			// lblVesoizmeritel
			// 
			this->lblVesoizmeritel->AutoSize = true;
			this->lblVesoizmeritel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblVesoizmeritel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblVesoizmeritel->Location = System::Drawing::Point(4, 1);
			this->lblVesoizmeritel->Name = L"lblVesoizmeritel";
			this->lblVesoizmeritel->Size = System::Drawing::Size(128, 17);
			this->lblVesoizmeritel->TabIndex = 0;
			this->lblVesoizmeritel->Text = L"Весоизмеритель";
			this->lblVesoizmeritel->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblDataTrack
			// 
			this->lblDataTrack->AutoSize = true;
			this->lblDataTrack->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblDataTrack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblDataTrack->Location = System::Drawing::Point(160, 1);
			this->lblDataTrack->Name = L"lblDataTrack";
			this->lblDataTrack->Size = System::Drawing::Size(128, 17);
			this->lblDataTrack->TabIndex = 1;
			this->lblDataTrack->Text = L"Дата - Трек";
			this->lblDataTrack->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// lblMES
			// 
			this->lblMES->AutoSize = true;
			this->lblMES->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblMES->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->lblMES->Location = System::Drawing::Point(316, 1);
			this->lblMES->Name = L"lblMES";
			this->lblMES->Size = System::Drawing::Size(128, 17);
			this->lblMES->TabIndex = 2;
			this->lblMES->Text = L"MES";
			this->lblMES->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// picBoxVesoizmeritelIndicator
			// 
			this->picBoxVesoizmeritelIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxVesoizmeritelIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxVesoizmeritelIndicator->Location = System::Drawing::Point(139, 4);
			this->picBoxVesoizmeritelIndicator->Name = L"picBoxVesoizmeritelIndicator";
			this->picBoxVesoizmeritelIndicator->Size = System::Drawing::Size(14, 11);
			this->picBoxVesoizmeritelIndicator->TabIndex = 3;
			this->picBoxVesoizmeritelIndicator->TabStop = false;
			// 
			// picBoxDataTrackIndicator
			// 
			this->picBoxDataTrackIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxDataTrackIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxDataTrackIndicator->Location = System::Drawing::Point(295, 4);
			this->picBoxDataTrackIndicator->Name = L"picBoxDataTrackIndicator";
			this->picBoxDataTrackIndicator->Size = System::Drawing::Size(14, 11);
			this->picBoxDataTrackIndicator->TabIndex = 4;
			this->picBoxDataTrackIndicator->TabStop = false;
			// 
			// picBoxMESIndicator
			// 
			this->picBoxMESIndicator->BackColor = System::Drawing::SystemColors::ControlText;
			this->picBoxMESIndicator->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBoxMESIndicator->Location = System::Drawing::Point(451, 4);
			this->picBoxMESIndicator->Name = L"picBoxMESIndicator";
			this->picBoxMESIndicator->Size = System::Drawing::Size(19, 11);
			this->picBoxMESIndicator->TabIndex = 5;
			this->picBoxMESIndicator->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 

            // lblName
			// 
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(78, 22);
			this->lblName->Text = L"toolStripLabel1";
			// 
			// lblLocation
			// 
			this->lblLocation->Name = L"lblLocation";
			this->lblLocation->Size = System::Drawing::Size(78, 22);
			this->lblLocation->Text = L"toolStripLabel2";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);

			this->toolStripSeparator2->Name = L"toolStripSeparator2";

			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
            this->lblData->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
			this->lblData->Name = L"lblData";
			this->lblData->Size = System::Drawing::Size(78, 22);
			this->lblData->Text = L"toolStripLabel1";

			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 190);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->toolStrip1);
			this->Name = L"Form1";
			this->Text = L"Form1";
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxVesoizmeritelIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxDataTrackIndicator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picBoxMESIndicator))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

           

		}
#pragma endregion
	private: System::Void btnNol_Click(System::Object^  sender, System::EventArgs^  e) {
				 picBoxTaraIndicator->BackColor = Color::Red;
                 // timer1->Enabled = true;

                 mdl->command("A");



			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
             if (Form1::Visible) {
             try{      

        String^ str = mdl->getWeight();
                         
		//try{
		//str = Double::Parse(str).ToString(); 
		//}
		//catch (Exception^ e){

		//}
       //Пример отлова состояния микросима

       // Console::WriteLine(mdl->getInd_null());
 
        //mdl->command("B");
       if (str == "TimeOut")  picBoxVesoizmeritelIndicator->BackColor = Color::Red;
       else if (str == "NoConne") picBoxVesoizmeritelIndicator->BackColor = Color::Red;
       else if (str == "Error") picBoxVesoizmeritelIndicator->BackColor = Color::Red;
       else if (str == "Null")  picBoxVesoizmeritelIndicator->BackColor = Color::Red;
       else picBoxVesoizmeritelIndicator->BackColor = Color::Green;

////
	   if (_vesKg)
	   {
		  // lblKg->BackColor  = Color::Red;
		 //  lblT->BackColor  = Color::Black;
		   picBoxKgIndicator->BackColor  = Color::Red;
		   picBoxTindicator->BackColor  = Color::Black;
	   }
	   else 
	   {
		 //  lblT->BackColor  = Color::Red;
		//	lblKg->BackColor  = Color::Black;
		   picBoxKgIndicator->BackColor  = Color::Black;
		   picBoxTindicator->BackColor  = Color::Red;
	   }


        lblVes->Text = str;
        Form1::Text = str + " © ДАТА-Центр Автоматика";
        if (mdl->getInd_tara()) picBoxTaraIndicator->BackColor = Color::Red;
        else picBoxTaraIndicator->BackColor = Color::Black;

        if (mdl->getInd_null()) picBoxNolIndicator->BackColor = Color::Red;
        else picBoxNolIndicator->BackColor = Color::Black;
            
        if (mdl->getInd_stabil()) picBoxStabilIndicator->BackColor = Color::Red;
        else picBoxStabilIndicator->BackColor = Color::Black;     
             
             }
             catch (System::NullReferenceException ^){lblVes->Text = "Error";}


             }}
private: System::Void btnTara_Click(System::Object^  sender, System::EventArgs^  e) {
                 mdl->command("B");
                 log->ControlDevice(_wght_name, "Тара");
                
		 }
private: System::Void btnRejim_Click(System::Object^  sender, System::EventArgs^  e) {
                 mdl->command("D");
                 log->ControlDevice(_wght_name, "Режим");
		 }
private: System::Void btnVibor_Click(System::Object^  sender, System::EventArgs^  e) {
                 mdl->command("H");
                 log->ControlDevice(_wght_name, "Выбор");
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {


}

private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
            
         
         }
private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
 
         }

};

}