#pragma once
#include "InputBox.h"


namespace Tablitsa {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Oracle::DataAccess::Client;
	using namespace Oracle::DataAccess::Types;
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
	public ref class AdminForm : public System::Windows::Forms::Form
	{
	public:
		AdminForm (List<List<String^>^>^ weight, List<String^>^ orcl, List<List<String^>^>^  data, String^ currentHashPassword, List<bool>^ buttonControl)
		{
			InitializeComponent();

			textBoxSSMIP->Text = "";
			textBoxSSMTime->Text = "";
			textBoxSSMPortMicrosim->Text = "";
			textBoxSSMJaguar->Text = "";
			//
			//TODO: Add the constructor code here
			//
			//Ищем порты 
			array<String^>^ serialPorts = nullptr;
			serialPorts = SerialPort::GetPortNames();
			for each(String^ port in serialPorts)
			{
				this->comboBox1->Items->Add(port);
			}

			currentPassHash = currentHashPassword;
			_data = data;
			this->_setOracleList(orcl);
			this->_setDataList(data);
			this->_setButtonControl(buttonControl);

			//BtnCheckOracle->BackColor = Color::LightGreen;
			comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			cbxParity->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			cbxSpeed->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			cbxStopBits->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;





			//Тестовый пример
			_weight = weight;

			this->_setWeight(_weight);

			try{
				this->toolStripComboBox1->SelectedIndex = 0;
			}
			catch (Exception ^e) {
				//Выключаем кнопки
				this->toolStripComboBox1->Enabled = 0;
				this->btnDel->Enabled = 0;
				this->btnSave->Enabled = 0;

			}

			//переопределим кнопку ОК что бы она сама не выключалась
			this->btnOk->DialogResult = Tablitsa::DialogResult::None;
			this->btnOk->Text = "ПРОВЕРИТЬ";


			//Спросим какие есть варики у модели
			try {
				List<String^> models = DataScalesModel::Model::GetListModel();
				comboBoxModelDll->Items->Clear();
				for (int i = 0; i < models.Count; i++)
				{
					comboBoxModelDll->Items->Add(models[i]);
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}

		}
		List<String^>^ getOracleList()
		{
			List<String^>^ orcl = gcnew List<String^>();
			orcl->Add(this->textBox1->Text);
			orcl->Add(this->textBox2->Text);
			orcl->Add(this->textBox3->Text);
			orcl->Add(this->textBox8->Text);
			orcl->Add(this->toolStripButton1->Checked.ToString());
			return orcl;
		}

		List<List<String^>^>^  getDataTrackList()
		{
			return _data;
		}

		void _setOracleList(List<String^>^ orcl)
		{
			this->textBox1->Text = orcl[0];
			this->textBox2->Text = orcl[1];
			this->textBox3->Text = orcl[2];
			this->textBox8->Text = orcl[3];
			this->toolStripButton1->Checked = bool::Parse(orcl[4]);

			this->BtnCheckOracle->Enabled = toolStripButton1->Checked;
			this->textBox1->Enabled = toolStripButton1->Checked;
			this->textBox2->Enabled = toolStripButton1->Checked;
			this->textBox3->Enabled = toolStripButton1->Checked;
			this->textBox8->Enabled = toolStripButton1->Checked;
			this->label11->Enabled = toolStripButton1->Checked;
			this->label12->Enabled = toolStripButton1->Checked;
			this->label13->Enabled = toolStripButton1->Checked;
			this->label14->Enabled = toolStripButton1->Checked;
			this->label15->Enabled = toolStripButton1->Checked;

			if (toolStripButton1->Checked) 
			{
				BtnCheckOracle->BackColor = Color::LightGreen;
				toolStripButton1->BackColor = Color::LightGreen;
				btnOk->Enabled = false;
			}

			else 
			{
				BtnCheckOracle->BackColor = this->btnCancel->BackColor;
				toolStripButton1->BackColor = Color::Red;
				btnOk->BackColor = Color::LightGreen;
				btnOk->Enabled = true;
			}

		}

		void _setDataList(List<List<String^>^>^  data)
		{

			/*this->textBoxSSMIP->Text = data[0];
			this->textBoxSSMTime->Text = data[1];
			this->textBoxSSMPortMicrosim->Text = data[2];
			this->textBoxSSMJaguar->Text = data[3];
			this->checkDatcTrack->Checked = bool::Parse(data[4]);

			textBoxSSMIP->Enabled = checkDatcTrack->Checked;
			textBoxSSMTime->Enabled = checkDatcTrack->Checked;
			textBoxSSMPortMicrosim->Enabled  = checkDatcTrack->Checked;
			textBoxSSMJaguar->Enabled = checkDatcTrack->Checked;

			if (checkDatcTrack->Checked) 
			{
			checkDatcTrack->BackColor = Color::LightGreen;
			}

			else 
			{
			checkDatcTrack->BackColor = Color::Red;
			}*/

			comboBoxDt->Items->Clear();
			for each (List<String^>^ elem in data){
				comboBoxDt->Items->Add(elem[0]);

			}
		}



		void _setWeight(List<List<String^>^>^ _weight) {
			//выгружаем настройки в интерфейс
			this->toolStripComboBox1->BeginUpdate();
			this->toolStripComboBox1->Items->Clear();
			for each(List<String^>^ elem in _weight ) {
				this->toolStripComboBox1->Items->Add(elem[0]); 
			}
			this->toolStripComboBox1->EndUpdate();

		};

		List<List<String^>^>^ getWeightList()
		{
			List<List<String^>^>^ tmp;
			tmp = _weight;

			return tmp;
		}

		String^ getHashPassword(){
			return currentPassHash;
		}

		void _setButtonControl(List<bool>^ buttonControl)
		{
			checkBoxNull->Checked =  buttonControl[0];
			checkBoxTara->Checked= buttonControl[1];
			checkBoxMode->Checked = buttonControl[2];
			checkBoxSelect->Checked = buttonControl[3];
		}

		List<bool>^ getButtonControl(){
			List<bool>^ tmp = gcnew List<bool>();
			tmp->Add(checkBoxNull->Checked);
			tmp->Add(checkBoxTara->Checked);
			tmp->Add(checkBoxMode->Checked);
			tmp->Add(checkBoxSelect->Checked);
			return tmp;

		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AdminForm ()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButtonPassword ;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<List<String^>^>^ _weight;
		List<List<String^>^>^ _data;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel6;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label22;





	private: System::Windows::Forms::TextBox^  txtBxName;
	private: System::Windows::Forms::TextBox^  txtBxPlace;


	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel8;
	private: System::Windows::Forms::CheckBox^  checkBoxNull;
	private: System::Windows::Forms::CheckBox^  checkBoxTara;
	private: System::Windows::Forms::CheckBox^  checkBoxMode;
	private: System::Windows::Forms::CheckBox^  checkBoxSelect;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel12;
	private: System::Windows::Forms::Label^  label49;
	private: System::Windows::Forms::Label^  label11;

	private: System::Windows::Forms::Label^  label12;

	private: System::Windows::Forms::Label^  label13;


	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  BtnCheckOracle;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel16;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel17;
	private: System::Windows::Forms::Label^  label57;
	private: System::Windows::Forms::TextBox^  textBoxSSMIP;
	private: System::Windows::Forms::Label^  label59;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::CheckBox^  toolStripButton1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Button^  btnOk;
	private: System::Windows::Forms::Label^  label111;
	private: System::Windows::Forms::ComboBox^  toolStripComboBox1;
	private: System::Windows::Forms::TabControl^  tabControlType;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TabPage^  tabPage4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelTypeCom;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel7;
	private: System::Windows::Forms::Button^  btnRefreshPorts;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::ComboBox^  cbxSpeed;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::ComboBox^  cbxParity;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::ComboBox^  cbxStopBits;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  TypeConnect;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnDel;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel5;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxIpMoxa;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxPortMoxa;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxUpdateTCP;
	private: System::Windows::Forms::TextBox^  textBoxSSMTime;

	private: System::Windows::Forms::Label^  label56;

	private: System::Windows::Forms::CheckBox^  checkDatcTrack;


	private: System::Windows::Forms::Label^  lable99;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBoxSSMPortMicrosim;
	private: System::Windows::Forms::TextBox^  textBoxSSMJaguar;
	private: System::Windows::Forms::TabPage^  tabPage5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel9;
	private: System::Windows::Forms::TextBox^  textBoxJaguarUpdate;

	private: System::Windows::Forms::TextBox^  textBoxJaguarPort;

	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textBoxJaguarIP;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::TextBox^  textBoxNomerSSM;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::CheckBox^  checkBoxSendRawData;
	private: System::Windows::Forms::ComboBox^  comboBoxED;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::TextBox^  IpSSM;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel10;
	private: System::Windows::Forms::Button^  buttonDtAdd;
	private: System::Windows::Forms::Button^  buttonDtSave;
	private: System::Windows::Forms::Button^  buttonDTDel;
	private: System::Windows::Forms::ComboBox^  comboBoxDt;
	private: System::Windows::Forms::TabPage^  tabPage6;
	private: System::Windows::Forms::RichTextBox^  MagicTextBox;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  labelModelDll;
	private: System::Windows::Forms::ComboBox^  comboBoxModelDll;


			 String^ currentPassHash;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AdminForm::typeid));
				 this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->toolStripButtonPassword = (gcnew System::Windows::Forms::ToolStripButton());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->btnAdd = (gcnew System::Windows::Forms::Button());
				 this->btnSave = (gcnew System::Windows::Forms::Button());
				 this->btnDel = (gcnew System::Windows::Forms::Button());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->tabControlType = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
				 this->tableLayoutPanelTypeCom = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label28 = (gcnew System::Windows::Forms::Label());
				 this->cbxStopBits = (gcnew System::Windows::Forms::ComboBox());
				 this->label27 = (gcnew System::Windows::Forms::Label());
				 this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label26 = (gcnew System::Windows::Forms::Label());
				 this->cbxParity = (gcnew System::Windows::Forms::ComboBox());
				 this->label25 = (gcnew System::Windows::Forms::Label());
				 this->cbxSpeed = (gcnew System::Windows::Forms::ComboBox());
				 this->label24 = (gcnew System::Windows::Forms::Label());
				 this->tableLayoutPanel7 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->btnRefreshPorts = (gcnew System::Windows::Forms::Button());
				 this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->label23 = (gcnew System::Windows::Forms::Label());
				 this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
				 this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->textBoxIpMoxa = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->textBoxPortMoxa = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->textBoxUpdateTCP = (gcnew System::Windows::Forms::TextBox());
				 this->comboBoxModelDll = (gcnew System::Windows::Forms::ComboBox());
				 this->labelModelDll = (gcnew System::Windows::Forms::Label());
				 this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
				 this->tableLayoutPanel9 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->textBoxJaguarUpdate = (gcnew System::Windows::Forms::TextBox());
				 this->textBoxJaguarPort = (gcnew System::Windows::Forms::TextBox());
				 this->label31 = (gcnew System::Windows::Forms::Label());
				 this->label29 = (gcnew System::Windows::Forms::Label());
				 this->label30 = (gcnew System::Windows::Forms::Label());
				 this->textBoxJaguarIP = (gcnew System::Windows::Forms::TextBox());
				 this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->TypeConnect = (gcnew System::Windows::Forms::ComboBox());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label21 = (gcnew System::Windows::Forms::Label());
				 this->label22 = (gcnew System::Windows::Forms::Label());
				 this->txtBxName = (gcnew System::Windows::Forms::TextBox());
				 this->txtBxPlace = (gcnew System::Windows::Forms::TextBox());
				 this->label34 = (gcnew System::Windows::Forms::Label());
				 this->tableLayoutPanel8 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->checkBoxNull = (gcnew System::Windows::Forms::CheckBox());
				 this->checkBoxTara = (gcnew System::Windows::Forms::CheckBox());
				 this->checkBoxMode = (gcnew System::Windows::Forms::CheckBox());
				 this->checkBoxSelect = (gcnew System::Windows::Forms::CheckBox());
				 this->label111 = (gcnew System::Windows::Forms::Label());
				 this->toolStripComboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->comboBoxED = (gcnew System::Windows::Forms::ComboBox());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->label32 = (gcnew System::Windows::Forms::Label());
				 this->textBoxNomerSSM = (gcnew System::Windows::Forms::TextBox());
				 this->label33 = (gcnew System::Windows::Forms::Label());
				 this->checkBoxSendRawData = (gcnew System::Windows::Forms::CheckBox());
				 this->label35 = (gcnew System::Windows::Forms::Label());
				 this->IpSSM = (gcnew System::Windows::Forms::TextBox());
				 this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
				 this->MagicTextBox = (gcnew System::Windows::Forms::RichTextBox());
				 this->label36 = (gcnew System::Windows::Forms::Label());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->tableLayoutPanel12 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->label56 = (gcnew System::Windows::Forms::Label());
				 this->textBoxSSMTime = (gcnew System::Windows::Forms::TextBox());
				 this->label49 = (gcnew System::Windows::Forms::Label());
				 this->label11 = (gcnew System::Windows::Forms::Label());
				 this->label12 = (gcnew System::Windows::Forms::Label());
				 this->label13 = (gcnew System::Windows::Forms::Label());
				 this->label14 = (gcnew System::Windows::Forms::Label());
				 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
				 this->BtnCheckOracle = (gcnew System::Windows::Forms::Button());
				 this->tableLayoutPanel16 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->textBoxSSMPortMicrosim = (gcnew System::Windows::Forms::TextBox());
				 this->textBoxSSMJaguar = (gcnew System::Windows::Forms::TextBox());
				 this->tableLayoutPanel17 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->lable99 = (gcnew System::Windows::Forms::Label());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->label57 = (gcnew System::Windows::Forms::Label());
				 this->textBoxSSMIP = (gcnew System::Windows::Forms::TextBox());
				 this->label59 = (gcnew System::Windows::Forms::Label());
				 this->label15 = (gcnew System::Windows::Forms::Label());
				 this->textBox8 = (gcnew System::Windows::Forms::TextBox());
				 this->toolStripButton1 = (gcnew System::Windows::Forms::CheckBox());
				 this->checkDatcTrack = (gcnew System::Windows::Forms::CheckBox());
				 this->tableLayoutPanel10 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->buttonDtAdd = (gcnew System::Windows::Forms::Button());
				 this->buttonDtSave = (gcnew System::Windows::Forms::Button());
				 this->buttonDTDel = (gcnew System::Windows::Forms::Button());
				 this->comboBoxDt = (gcnew System::Windows::Forms::ComboBox());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->btnCancel = (gcnew System::Windows::Forms::Button());
				 this->btnOk = (gcnew System::Windows::Forms::Button());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->textBox4 = (gcnew System::Windows::Forms::TextBox());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->textBox5 = (gcnew System::Windows::Forms::TextBox());
				 this->label9 = (gcnew System::Windows::Forms::Label());
				 this->textBox6 = (gcnew System::Windows::Forms::TextBox());
				 this->label10 = (gcnew System::Windows::Forms::Label());
				 this->textBox7 = (gcnew System::Windows::Forms::TextBox());
				 this->label16 = (gcnew System::Windows::Forms::Label());
				 this->textBox9 = (gcnew System::Windows::Forms::TextBox());
				 this->label17 = (gcnew System::Windows::Forms::Label());
				 this->textBox10 = (gcnew System::Windows::Forms::TextBox());
				 this->label18 = (gcnew System::Windows::Forms::Label());
				 this->textBox11 = (gcnew System::Windows::Forms::TextBox());
				 this->label19 = (gcnew System::Windows::Forms::Label());
				 this->textBox12 = (gcnew System::Windows::Forms::TextBox());
				 this->label20 = (gcnew System::Windows::Forms::Label());
				 this->textBox13 = (gcnew System::Windows::Forms::TextBox());
				 this->toolStrip1->SuspendLayout();
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 this->tableLayoutPanel4->SuspendLayout();
				 this->tableLayoutPanel3->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
				 this->tabControlType->SuspendLayout();
				 this->tabPage3->SuspendLayout();
				 this->tableLayoutPanelTypeCom->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
				 this->tableLayoutPanel7->SuspendLayout();
				 this->tabPage4->SuspendLayout();
				 this->tableLayoutPanel5->SuspendLayout();
				 this->tabPage5->SuspendLayout();
				 this->tableLayoutPanel9->SuspendLayout();
				 this->tableLayoutPanel6->SuspendLayout();
				 this->tableLayoutPanel8->SuspendLayout();
				 this->tabPage6->SuspendLayout();
				 this->tabPage2->SuspendLayout();
				 this->tableLayoutPanel12->SuspendLayout();
				 this->tableLayoutPanel16->SuspendLayout();
				 this->tableLayoutPanel17->SuspendLayout();
				 this->tableLayoutPanel10->SuspendLayout();
				 this->tableLayoutPanel1->SuspendLayout();
				 this->tableLayoutPanel2->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // toolStrip1
				 // 
				 this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripSeparator1, 
					 this->toolStripButtonPassword});
				 this->toolStrip1->Location = System::Drawing::Point(0, 0);
				 this->toolStrip1->Name = L"toolStrip1";
				 this->toolStrip1->Size = System::Drawing::Size(839, 25);
				 this->toolStrip1->TabIndex = 0;
				 this->toolStrip1->Text = L"toolStrip1";
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
				 // 
				 // toolStripButtonPassword
				 // 
				 this->toolStripButtonPassword->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
				 this->toolStripButtonPassword->ImageTransparentColor = System::Drawing::Color::Magenta;
				 this->toolStripButtonPassword->Name = L"toolStripButtonPassword";
				 this->toolStripButtonPassword->Size = System::Drawing::Size(108, 22);
				 this->toolStripButtonPassword->Text = L"Изменить пароль";
				 this->toolStripButtonPassword->Click += gcnew System::EventHandler(this, &AdminForm::toolStripButtonPassword_Click);
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage6);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Location = System::Drawing::Point(3, 3);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(833, 598);
				 this->tabControl1->TabIndex = 2;
				 // 
				 // tabPage1
				 // 
				 this->tabPage1->Controls->Add(this->tableLayoutPanel4);
				 this->tabPage1->Controls->Add(this->tabControlType);
				 this->tabPage1->Controls->Add(this->tableLayoutPanel6);
				 this->tabPage1->Location = System::Drawing::Point(4, 22);
				 this->tabPage1->Name = L"tabPage1";
				 this->tabPage1->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage1->Size = System::Drawing::Size(825, 572);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Tag = L"";
				 this->tabPage1->Text = L"Весоизмерители";
				 this->tabPage1->ToolTipText = L"Весоизмерители";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 this->tabPage1->Click += gcnew System::EventHandler(this, &AdminForm::tabPage1_Click);
				 // 
				 // tableLayoutPanel4
				 // 
				 this->tableLayoutPanel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel4->ColumnCount = 2;
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 27.93734F)));
				 this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 72.06266F)));
				 this->tableLayoutPanel4->Controls->Add(this->tableLayoutPanel3, 0, 0);
				 this->tableLayoutPanel4->Controls->Add(this->pictureBox2, 0, 0);
				 this->tableLayoutPanel4->Location = System::Drawing::Point(2, 516);
				 this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
				 this->tableLayoutPanel4->RowCount = 1;
				 this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel4->Size = System::Drawing::Size(814, 50);
				 this->tableLayoutPanel4->TabIndex = 4;
				 // 
				 // tableLayoutPanel3
				 // 
				 this->tableLayoutPanel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel3->ColumnCount = 3;
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 45.84451F)));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 54.15549F)));
				 this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 309)));
				 this->tableLayoutPanel3->Controls->Add(this->btnAdd, 0, 0);
				 this->tableLayoutPanel3->Controls->Add(this->btnSave, 1, 0);
				 this->tableLayoutPanel3->Controls->Add(this->btnDel, 2, 0);
				 this->tableLayoutPanel3->Location = System::Drawing::Point(230, 3);
				 this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
				 this->tableLayoutPanel3->RowCount = 1;
				 this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel3->Size = System::Drawing::Size(581, 44);
				 this->tableLayoutPanel3->TabIndex = 50;
				 // 
				 // btnAdd
				 // 
				 this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->btnAdd->Location = System::Drawing::Point(3, 3);
				 this->btnAdd->Name = L"btnAdd";
				 this->btnAdd->Size = System::Drawing::Size(118, 38);
				 this->btnAdd->TabIndex = 0;
				 this->btnAdd->Text = L"Добавить";
				 this->btnAdd->UseVisualStyleBackColor = true;
				 this->btnAdd->Click += gcnew System::EventHandler(this, &AdminForm::btnAdd_Click_1);
				 // 
				 // btnSave
				 // 
				 this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->btnSave->Location = System::Drawing::Point(127, 3);
				 this->btnSave->Name = L"btnSave";
				 this->btnSave->Size = System::Drawing::Size(141, 38);
				 this->btnSave->TabIndex = 1;
				 this->btnSave->Text = L"Сохранить";
				 this->btnSave->UseVisualStyleBackColor = true;
				 this->btnSave->Click += gcnew System::EventHandler(this, &AdminForm::btnSave_Click_1);
				 // 
				 // btnDel
				 // 
				 this->btnDel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->btnDel->Location = System::Drawing::Point(274, 3);
				 this->btnDel->Name = L"btnDel";
				 this->btnDel->Size = System::Drawing::Size(304, 38);
				 this->btnDel->TabIndex = 2;
				 this->btnDel->Text = L"Удалить";
				 this->btnDel->UseVisualStyleBackColor = true;
				 this->btnDel->Click += gcnew System::EventHandler(this, &AdminForm::btnDel_Click_1);
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.BackgroundImage")));
				 this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
				 this->pictureBox2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox2->Location = System::Drawing::Point(3, 3);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(221, 44);
				 this->pictureBox2->TabIndex = 23;
				 this->pictureBox2->TabStop = false;
				 // 
				 // tabControlType
				 // 
				 this->tabControlType->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tabControlType->Controls->Add(this->tabPage3);
				 this->tabControlType->Controls->Add(this->tabPage4);
				 this->tabControlType->Controls->Add(this->tabPage5);
				 this->tabControlType->Location = System::Drawing::Point(6, 285);
				 this->tabControlType->Name = L"tabControlType";
				 this->tabControlType->SelectedIndex = 0;
				 this->tabControlType->Size = System::Drawing::Size(810, 228);
				 this->tabControlType->TabIndex = 3;
				 this->tabControlType->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &AdminForm::tabControlType_Selecting);
				 // 
				 // tabPage3
				 // 
				 this->tabPage3->Controls->Add(this->tableLayoutPanelTypeCom);
				 this->tabPage3->Location = System::Drawing::Point(4, 22);
				 this->tabPage3->Name = L"tabPage3";
				 this->tabPage3->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage3->Size = System::Drawing::Size(802, 202);
				 this->tabPage3->TabIndex = 0;
				 this->tabPage3->Text = L"COM";
				 this->tabPage3->UseVisualStyleBackColor = true;
				 // 
				 // tableLayoutPanelTypeCom
				 // 
				 this->tableLayoutPanelTypeCom->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanelTypeCom->ColumnCount = 2;
				 this->tableLayoutPanelTypeCom->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 29.14438F)));
				 this->tableLayoutPanelTypeCom->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 70.85562F)));
				 this->tableLayoutPanelTypeCom->Controls->Add(this->numericUpDown1, 1, 5);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label28, 0, 5);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->cbxStopBits, 1, 4);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label27, 0, 4);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->numericUpDown2, 1, 3);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label26, 0, 3);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->cbxParity, 1, 2);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label25, 0, 2);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->cbxSpeed, 1, 1);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label24, 0, 1);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->tableLayoutPanel7, 1, 0);
				 this->tableLayoutPanelTypeCom->Controls->Add(this->label23, 0, 0);
				 this->tableLayoutPanelTypeCom->Location = System::Drawing::Point(0, 12);
				 this->tableLayoutPanelTypeCom->Name = L"tableLayoutPanelTypeCom";
				 this->tableLayoutPanelTypeCom->RowCount = 6;
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
				 this->tableLayoutPanelTypeCom->Size = System::Drawing::Size(796, 184);
				 this->tableLayoutPanelTypeCom->TabIndex = 0;
				 // 
				 // numericUpDown1
				 // 
				 this->numericUpDown1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->numericUpDown1->Location = System::Drawing::Point(234, 162);
				 this->numericUpDown1->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
				 this->numericUpDown1->Name = L"numericUpDown1";
				 this->numericUpDown1->Size = System::Drawing::Size(559, 20);
				 this->numericUpDown1->TabIndex = 27;
				 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {600, 0, 0, 0});
				 // 
				 // label28
				 // 
				 this->label28->AutoSize = true;
				 this->label28->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label28->Location = System::Drawing::Point(3, 157);
				 this->label28->Name = L"label28";
				 this->label28->Size = System::Drawing::Size(225, 28);
				 this->label28->TabIndex = 26;
				 this->label28->Text = L"Интервал обновления (мс)";
				 this->label28->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // cbxStopBits
				 // 
				 this->cbxStopBits->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->cbxStopBits->FormattingEnabled = true;
				 this->cbxStopBits->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"None", L"One", L"OnePointFive", L"Two"});
				 this->cbxStopBits->Location = System::Drawing::Point(234, 133);
				 this->cbxStopBits->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->cbxStopBits->Name = L"cbxStopBits";
				 this->cbxStopBits->Size = System::Drawing::Size(559, 21);
				 this->cbxStopBits->TabIndex = 25;
				 // 
				 // label27
				 // 
				 this->label27->AutoSize = true;
				 this->label27->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label27->Location = System::Drawing::Point(3, 128);
				 this->label27->Name = L"label27";
				 this->label27->Size = System::Drawing::Size(225, 29);
				 this->label27->TabIndex = 24;
				 this->label27->Text = L"Стоповых бит";
				 this->label27->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // numericUpDown2
				 // 
				 this->numericUpDown2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->numericUpDown2->Location = System::Drawing::Point(234, 105);
				 this->numericUpDown2->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->numericUpDown2->Name = L"numericUpDown2";
				 this->numericUpDown2->Size = System::Drawing::Size(559, 20);
				 this->numericUpDown2->TabIndex = 23;
				 this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {8, 0, 0, 0});
				 // 
				 // label26
				 // 
				 this->label26->AutoSize = true;
				 this->label26->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label26->Location = System::Drawing::Point(3, 100);
				 this->label26->Name = L"label26";
				 this->label26->Size = System::Drawing::Size(225, 28);
				 this->label26->TabIndex = 22;
				 this->label26->Text = L"Количество бит";
				 this->label26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // cbxParity
				 // 
				 this->cbxParity->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->cbxParity->FormattingEnabled = true;
				 this->cbxParity->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Even", L"Mark", L"None", L"Odd", L"Space"});
				 this->cbxParity->Location = System::Drawing::Point(234, 76);
				 this->cbxParity->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->cbxParity->Name = L"cbxParity";
				 this->cbxParity->Size = System::Drawing::Size(559, 21);
				 this->cbxParity->TabIndex = 21;
				 // 
				 // label25
				 // 
				 this->label25->AutoSize = true;
				 this->label25->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label25->Location = System::Drawing::Point(3, 71);
				 this->label25->Name = L"label25";
				 this->label25->Size = System::Drawing::Size(225, 29);
				 this->label25->TabIndex = 20;
				 this->label25->Text = L"Parity";
				 this->label25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // cbxSpeed
				 // 
				 this->cbxSpeed->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->cbxSpeed->FormattingEnabled = true;
				 this->cbxSpeed->Items->AddRange(gcnew cli::array< System::Object^  >(13) {L"110", L"300", L"1200", L"2400", L"4800", L"9600", 
					 L"19200", L"38400", L"57600", L"115200", L"230400", L"460800", L"921600"});
				 this->cbxSpeed->Location = System::Drawing::Point(234, 47);
				 this->cbxSpeed->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->cbxSpeed->Name = L"cbxSpeed";
				 this->cbxSpeed->Size = System::Drawing::Size(559, 21);
				 this->cbxSpeed->TabIndex = 19;
				 // 
				 // label24
				 // 
				 this->label24->AutoSize = true;
				 this->label24->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label24->Location = System::Drawing::Point(3, 42);
				 this->label24->Name = L"label24";
				 this->label24->Size = System::Drawing::Size(225, 29);
				 this->label24->TabIndex = 18;
				 this->label24->Text = L"Скорость";
				 this->label24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // tableLayoutPanel7
				 // 
				 this->tableLayoutPanel7->ColumnCount = 2;
				 this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel7->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 194)));
				 this->tableLayoutPanel7->Controls->Add(this->btnRefreshPorts, 0, 0);
				 this->tableLayoutPanel7->Controls->Add(this->comboBox1, 1, 0);
				 this->tableLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel7->Location = System::Drawing::Point(231, 0);
				 this->tableLayoutPanel7->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanel7->Name = L"tableLayoutPanel7";
				 this->tableLayoutPanel7->RowCount = 1;
				 this->tableLayoutPanel7->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel7->Size = System::Drawing::Size(565, 42);
				 this->tableLayoutPanel7->TabIndex = 17;
				 // 
				 // btnRefreshPorts
				 // 
				 this->btnRefreshPorts->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->btnRefreshPorts->Location = System::Drawing::Point(3, 3);
				 this->btnRefreshPorts->Name = L"btnRefreshPorts";
				 this->btnRefreshPorts->Size = System::Drawing::Size(365, 36);
				 this->btnRefreshPorts->TabIndex = 0;
				 this->btnRefreshPorts->Text = L"Обновить список";
				 this->btnRefreshPorts->UseVisualStyleBackColor = true;
				 // 
				 // comboBox1
				 // 
				 this->comboBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->comboBox1->FormattingEnabled = true;
				 this->comboBox1->Location = System::Drawing::Point(374, 5);
				 this->comboBox1->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->comboBox1->Name = L"comboBox1";
				 this->comboBox1->Size = System::Drawing::Size(188, 21);
				 this->comboBox1->TabIndex = 1;
				 // 
				 // label23
				 // 
				 this->label23->AutoSize = true;
				 this->label23->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label23->Location = System::Drawing::Point(3, 0);
				 this->label23->Name = L"label23";
				 this->label23->Size = System::Drawing::Size(225, 42);
				 this->label23->TabIndex = 3;
				 this->label23->Text = L"Порт";
				 this->label23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // tabPage4
				 // 
				 this->tabPage4->Controls->Add(this->tableLayoutPanel5);
				 this->tabPage4->Location = System::Drawing::Point(4, 22);
				 this->tabPage4->Name = L"tabPage4";
				 this->tabPage4->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage4->Size = System::Drawing::Size(802, 202);
				 this->tabPage4->TabIndex = 1;
				 this->tabPage4->Text = L"Ethernet";
				 this->tabPage4->UseVisualStyleBackColor = true;
				 // 
				 // tableLayoutPanel5
				 // 
				 this->tableLayoutPanel5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel5->ColumnCount = 2;
				 this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel5->Controls->Add(this->label2, 0, 0);
				 this->tableLayoutPanel5->Controls->Add(this->textBoxIpMoxa, 1, 0);
				 this->tableLayoutPanel5->Controls->Add(this->label3, 0, 1);
				 this->tableLayoutPanel5->Controls->Add(this->textBoxPortMoxa, 1, 1);
				 this->tableLayoutPanel5->Controls->Add(this->label4, 0, 2);
				 this->tableLayoutPanel5->Controls->Add(this->textBoxUpdateTCP, 1, 2);
				 this->tableLayoutPanel5->Controls->Add(this->comboBoxModelDll, 1, 3);
				 this->tableLayoutPanel5->Controls->Add(this->labelModelDll, 0, 3);
				 this->tableLayoutPanel5->Location = System::Drawing::Point(3, 6);
				 this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
				 this->tableLayoutPanel5->RowCount = 4;
				 this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 34)));
				 this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 41)));
				 this->tableLayoutPanel5->Size = System::Drawing::Size(797, 138);
				 this->tableLayoutPanel5->TabIndex = 0;
				 // 
				 // label2
				 // 
				 this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(3, 9);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(392, 13);
				 this->label2->TabIndex = 0;
				 this->label2->Text = L"IP Адрес";
				 this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->label2->Click += gcnew System::EventHandler(this, &AdminForm::label2_Click);
				 // 
				 // textBoxIpMoxa
				 // 
				 this->textBoxIpMoxa->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxIpMoxa->Location = System::Drawing::Point(401, 5);
				 this->textBoxIpMoxa->Name = L"textBoxIpMoxa";
				 this->textBoxIpMoxa->Size = System::Drawing::Size(393, 20);
				 this->textBoxIpMoxa->TabIndex = 1;
				 // 
				 // label3
				 // 
				 this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(3, 40);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(392, 13);
				 this->label3->TabIndex = 2;
				 this->label3->Text = L"Порт";
				 this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxPortMoxa
				 // 
				 this->textBoxPortMoxa->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxPortMoxa->Location = System::Drawing::Point(401, 36);
				 this->textBoxPortMoxa->Name = L"textBoxPortMoxa";
				 this->textBoxPortMoxa->Size = System::Drawing::Size(393, 20);
				 this->textBoxPortMoxa->TabIndex = 3;
				 // 
				 // label4
				 // 
				 this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(3, 72);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(392, 13);
				 this->label4->TabIndex = 4;
				 this->label4->Text = L"Обновление";
				 this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxUpdateTCP
				 // 
				 this->textBoxUpdateTCP->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxUpdateTCP->Location = System::Drawing::Point(401, 69);
				 this->textBoxUpdateTCP->Name = L"textBoxUpdateTCP";
				 this->textBoxUpdateTCP->Size = System::Drawing::Size(393, 20);
				 this->textBoxUpdateTCP->TabIndex = 5;
				 // 
				 // comboBoxModelDll
				 // 
				 this->comboBoxModelDll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->comboBoxModelDll->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxModelDll->FormattingEnabled = true;
				 this->comboBoxModelDll->Location = System::Drawing::Point(401, 106);
				 this->comboBoxModelDll->Name = L"comboBoxModelDll";
				 this->comboBoxModelDll->Size = System::Drawing::Size(393, 21);
				 this->comboBoxModelDll->TabIndex = 52;
				 this->comboBoxModelDll->Visible = false;
				 // 
				 // labelModelDll
				 // 
				 this->labelModelDll->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->labelModelDll->AutoSize = true;
				 this->labelModelDll->Location = System::Drawing::Point(3, 110);
				 this->labelModelDll->Name = L"labelModelDll";
				 this->labelModelDll->Size = System::Drawing::Size(392, 13);
				 this->labelModelDll->TabIndex = 6;
				 this->labelModelDll->Text = L"Модель DLL";
				 this->labelModelDll->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->labelModelDll->Visible = false;
				 // 
				 // tabPage5
				 // 
				 this->tabPage5->Controls->Add(this->tableLayoutPanel9);
				 this->tabPage5->Location = System::Drawing::Point(4, 22);
				 this->tabPage5->Name = L"tabPage5";
				 this->tabPage5->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage5->Size = System::Drawing::Size(802, 202);
				 this->tabPage5->TabIndex = 2;
				 this->tabPage5->Text = L"Jaguar TCP/IP";
				 this->tabPage5->UseVisualStyleBackColor = true;
				 // 
				 // tableLayoutPanel9
				 // 
				 this->tableLayoutPanel9->ColumnCount = 2;
				 this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 49.87342F)));
				 this->tableLayoutPanel9->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50.12658F)));
				 this->tableLayoutPanel9->Controls->Add(this->textBoxJaguarUpdate, 1, 2);
				 this->tableLayoutPanel9->Controls->Add(this->textBoxJaguarPort, 1, 1);
				 this->tableLayoutPanel9->Controls->Add(this->label31, 0, 2);
				 this->tableLayoutPanel9->Controls->Add(this->label29, 0, 0);
				 this->tableLayoutPanel9->Controls->Add(this->label30, 0, 1);
				 this->tableLayoutPanel9->Controls->Add(this->textBoxJaguarIP, 1, 0);
				 this->tableLayoutPanel9->Location = System::Drawing::Point(6, 6);
				 this->tableLayoutPanel9->Name = L"tableLayoutPanel9";
				 this->tableLayoutPanel9->RowCount = 3;
				 this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel9->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
				 this->tableLayoutPanel9->Size = System::Drawing::Size(790, 91);
				 this->tableLayoutPanel9->TabIndex = 0;
				 // 
				 // textBoxJaguarUpdate
				 // 
				 this->textBoxJaguarUpdate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxJaguarUpdate->Location = System::Drawing::Point(397, 66);
				 this->textBoxJaguarUpdate->Name = L"textBoxJaguarUpdate";
				 this->textBoxJaguarUpdate->Size = System::Drawing::Size(390, 20);
				 this->textBoxJaguarUpdate->TabIndex = 8;
				 this->textBoxJaguarUpdate->Text = L"600";
				 // 
				 // textBoxJaguarPort
				 // 
				 this->textBoxJaguarPort->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxJaguarPort->Location = System::Drawing::Point(397, 36);
				 this->textBoxJaguarPort->Name = L"textBoxJaguarPort";
				 this->textBoxJaguarPort->Size = System::Drawing::Size(390, 20);
				 this->textBoxJaguarPort->TabIndex = 7;
				 this->textBoxJaguarPort->Text = L"12461";
				 // 
				 // label31
				 // 
				 this->label31->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label31->AutoSize = true;
				 this->label31->Location = System::Drawing::Point(3, 70);
				 this->label31->Name = L"label31";
				 this->label31->Size = System::Drawing::Size(388, 13);
				 this->label31->TabIndex = 5;
				 this->label31->Text = L"Обновление";
				 this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label29
				 // 
				 this->label29->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label29->AutoSize = true;
				 this->label29->Location = System::Drawing::Point(3, 9);
				 this->label29->Name = L"label29";
				 this->label29->Size = System::Drawing::Size(388, 13);
				 this->label29->TabIndex = 1;
				 this->label29->Text = L"IP Адрес или DNS";
				 this->label29->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label30
				 // 
				 this->label30->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label30->AutoSize = true;
				 this->label30->Location = System::Drawing::Point(3, 40);
				 this->label30->Name = L"label30";
				 this->label30->Size = System::Drawing::Size(388, 13);
				 this->label30->TabIndex = 3;
				 this->label30->Text = L"Порт";
				 this->label30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxJaguarIP
				 // 
				 this->textBoxJaguarIP->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxJaguarIP->Location = System::Drawing::Point(397, 5);
				 this->textBoxJaguarIP->Name = L"textBoxJaguarIP";
				 this->textBoxJaguarIP->Size = System::Drawing::Size(390, 20);
				 this->textBoxJaguarIP->TabIndex = 6;
				 // 
				 // tableLayoutPanel6
				 // 
				 this->tableLayoutPanel6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel6->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->tableLayoutPanel6->ColumnCount = 2;
				 this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 29.6837F)));
				 this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 70.3163F)));
				 this->tableLayoutPanel6->Controls->Add(this->TypeConnect, 1, 5);
				 this->tableLayoutPanel6->Controls->Add(this->label1, 0, 5);
				 this->tableLayoutPanel6->Controls->Add(this->label21, 0, 2);
				 this->tableLayoutPanel6->Controls->Add(this->label22, 0, 3);
				 this->tableLayoutPanel6->Controls->Add(this->txtBxName, 1, 2);
				 this->tableLayoutPanel6->Controls->Add(this->txtBxPlace, 1, 3);
				 this->tableLayoutPanel6->Controls->Add(this->label34, 0, 1);
				 this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel8, 1, 1);
				 this->tableLayoutPanel6->Controls->Add(this->label111, 0, 0);
				 this->tableLayoutPanel6->Controls->Add(this->toolStripComboBox1, 1, 0);
				 this->tableLayoutPanel6->Controls->Add(this->comboBoxED, 1, 4);
				 this->tableLayoutPanel6->Controls->Add(this->label5, 0, 4);
				 this->tableLayoutPanel6->Controls->Add(this->label32, 0, 6);
				 this->tableLayoutPanel6->Controls->Add(this->textBoxNomerSSM, 1, 6);
				 this->tableLayoutPanel6->Controls->Add(this->label33, 0, 8);
				 this->tableLayoutPanel6->Controls->Add(this->checkBoxSendRawData, 1, 8);
				 this->tableLayoutPanel6->Controls->Add(this->label35, 0, 7);
				 this->tableLayoutPanel6->Controls->Add(this->IpSSM, 1, 7);
				 this->tableLayoutPanel6->Location = System::Drawing::Point(5, 3);
				 this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
				 this->tableLayoutPanel6->RowCount = 9;
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 31)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 14.70588F)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 23.52941F)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 24.26471F)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 37.5F)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 36)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 31)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 42)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				 this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
				 this->tableLayoutPanel6->Size = System::Drawing::Size(814, 276);
				 this->tableLayoutPanel6->TabIndex = 2;
				 this->tableLayoutPanel6->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &AdminForm::tableLayoutPanel6_Paint);
				 // 
				 // TypeConnect
				 // 
				 this->TypeConnect->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->TypeConnect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->TypeConnect->FormattingEnabled = true;
				 this->TypeConnect->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"Microsim - RC232 (COM)", L"Microsim - Ethernet Client (TCP/IP)", 
					 L"Jaguar - Ethernet Client (TCP/IP)", L"WE2120_ST - Ethernet Client (TCP/IP)", L"DEFAULT-Ethernet Client (TCP/IP)", L"WE2120_ALT - Ethernet Client (TCP/IP)", 
					 L"INTECONT_OPUS_ST - Ethernet Client (TCP/IP", L"DISOMAT_SATUS - Ethernet Client (TCP/IP)", L"DATASCALES_REPEATER - Ethernet Client (TCP/IP)", 
					 L"DATASCALES_DLL - Ethernet Client (TCP/IP)"});
				 this->TypeConnect->Location = System::Drawing::Point(245, 147);
				 this->TypeConnect->Name = L"TypeConnect";
				 this->TypeConnect->Size = System::Drawing::Size(565, 21);
				 this->TypeConnect->TabIndex = 51;
				 this->TypeConnect->SelectedIndexChanged += gcnew System::EventHandler(this, &AdminForm::TypeConnect_SelectedIndexChanged_1);
				 // 
				 // label1
				 // 
				 this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(4, 151);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(234, 13);
				 this->label1->TabIndex = 50;
				 this->label1->Text = L"Тип весов";
				 this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label21
				 // 
				 this->label21->AutoSize = true;
				 this->label21->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label21->Location = System::Drawing::Point(4, 49);
				 this->label21->Name = L"label21";
				 this->label21->Size = System::Drawing::Size(234, 24);
				 this->label21->TabIndex = 0;
				 this->label21->Text = L"Номер";
				 this->label21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label22
				 // 
				 this->label22->AutoSize = true;
				 this->label22->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label22->Location = System::Drawing::Point(4, 74);
				 this->label22->Name = L"label22";
				 this->label22->Size = System::Drawing::Size(234, 25);
				 this->label22->TabIndex = 1;
				 this->label22->Text = L"Местоположение";
				 this->label22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // txtBxName
				 // 
				 this->txtBxName->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->txtBxName->Location = System::Drawing::Point(245, 52);
				 this->txtBxName->MaxLength = 3;
				 this->txtBxName->Name = L"txtBxName";
				 this->txtBxName->Size = System::Drawing::Size(565, 20);
				 this->txtBxName->TabIndex = 8;
				 // 
				 // txtBxPlace
				 // 
				 this->txtBxPlace->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->txtBxPlace->Location = System::Drawing::Point(245, 79);
				 this->txtBxPlace->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->txtBxPlace->Name = L"txtBxPlace";
				 this->txtBxPlace->Size = System::Drawing::Size(565, 20);
				 this->txtBxPlace->TabIndex = 9;
				 // 
				 // label34
				 // 
				 this->label34->AutoSize = true;
				 this->label34->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(204)));
				 this->label34->Location = System::Drawing::Point(4, 33);
				 this->label34->Name = L"label34";
				 this->label34->Size = System::Drawing::Size(234, 15);
				 this->label34->TabIndex = 23;
				 this->label34->Text = L"Управление";
				 this->label34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // tableLayoutPanel8
				 // 
				 this->tableLayoutPanel8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel8->ColumnCount = 4;
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 45.65217F)));
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 54.34783F)));
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 73)));
				 this->tableLayoutPanel8->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 62)));
				 this->tableLayoutPanel8->Controls->Add(this->checkBoxNull, 0, 0);
				 this->tableLayoutPanel8->Controls->Add(this->checkBoxTara, 1, 0);
				 this->tableLayoutPanel8->Controls->Add(this->checkBoxMode, 2, 0);
				 this->tableLayoutPanel8->Controls->Add(this->checkBoxSelect, 3, 0);
				 this->tableLayoutPanel8->Location = System::Drawing::Point(245, 36);
				 this->tableLayoutPanel8->Name = L"tableLayoutPanel8";
				 this->tableLayoutPanel8->RowCount = 1;
				 this->tableLayoutPanel8->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel8->Size = System::Drawing::Size(565, 1);
				 this->tableLayoutPanel8->TabIndex = 46;
				 // 
				 // checkBoxNull
				 // 
				 this->checkBoxNull->AutoSize = true;
				 this->checkBoxNull->Location = System::Drawing::Point(3, 3);
				 this->checkBoxNull->Name = L"checkBoxNull";
				 this->checkBoxNull->Size = System::Drawing::Size(52, 1);
				 this->checkBoxNull->TabIndex = 0;
				 this->checkBoxNull->Text = L"Ноль";
				 this->checkBoxNull->UseVisualStyleBackColor = true;
				 // 
				 // checkBoxTara
				 // 
				 this->checkBoxTara->AutoSize = true;
				 this->checkBoxTara->Location = System::Drawing::Point(112, 3);
				 this->checkBoxTara->Name = L"checkBoxTara";
				 this->checkBoxTara->Size = System::Drawing::Size(51, 1);
				 this->checkBoxTara->TabIndex = 1;
				 this->checkBoxTara->Text = L"Тара";
				 this->checkBoxTara->UseVisualStyleBackColor = true;
				 // 
				 // checkBoxMode
				 // 
				 this->checkBoxMode->AutoSize = true;
				 this->checkBoxMode->Location = System::Drawing::Point(242, 3);
				 this->checkBoxMode->Name = L"checkBoxMode";
				 this->checkBoxMode->Size = System::Drawing::Size(61, 1);
				 this->checkBoxMode->TabIndex = 2;
				 this->checkBoxMode->Text = L"Режим";
				 this->checkBoxMode->UseVisualStyleBackColor = true;
				 // 
				 // checkBoxSelect
				 // 
				 this->checkBoxSelect->AutoSize = true;
				 this->checkBoxSelect->Location = System::Drawing::Point(417, 3);
				 this->checkBoxSelect->Name = L"checkBoxSelect";
				 this->checkBoxSelect->Size = System::Drawing::Size(59, 1);
				 this->checkBoxSelect->TabIndex = 3;
				 this->checkBoxSelect->Text = L"Выбор";
				 this->checkBoxSelect->UseVisualStyleBackColor = true;
				 // 
				 // label111
				 // 
				 this->label111->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->label111->AutoSize = true;
				 this->label111->Location = System::Drawing::Point(4, 1);
				 this->label111->Name = L"label111";
				 this->label111->Size = System::Drawing::Size(234, 31);
				 this->label111->TabIndex = 47;
				 this->label111->Text = L"Весоизмеритель";
				 // 
				 // toolStripComboBox1
				 // 
				 this->toolStripComboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->toolStripComboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->toolStripComboBox1->FormattingEnabled = true;
				 this->toolStripComboBox1->Location = System::Drawing::Point(245, 4);
				 this->toolStripComboBox1->Name = L"toolStripComboBox1";
				 this->toolStripComboBox1->Size = System::Drawing::Size(565, 21);
				 this->toolStripComboBox1->TabIndex = 48;
				 this->toolStripComboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &AdminForm::toolStripComboBox1_SelectedIndexChanged_1);
				 // 
				 // comboBoxED
				 // 
				 this->comboBoxED->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->comboBoxED->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxED->FormattingEnabled = true;
				 this->comboBoxED->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"КГ", L"Т"});
				 this->comboBoxED->Location = System::Drawing::Point(245, 109);
				 this->comboBoxED->Name = L"comboBoxED";
				 this->comboBoxED->Size = System::Drawing::Size(565, 21);
				 this->comboBoxED->TabIndex = 52;
				 // 
				 // label5
				 // 
				 this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(4, 113);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(234, 13);
				 this->label5->TabIndex = 53;
				 this->label5->Text = L"Еденицы измерения";
				 this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label32
				 // 
				 this->label32->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label32->AutoSize = true;
				 this->label32->Location = System::Drawing::Point(4, 186);
				 this->label32->Name = L"label32";
				 this->label32->Size = System::Drawing::Size(234, 13);
				 this->label32->TabIndex = 54;
				 this->label32->Text = L"Номер в посылке ССМ";
				 this->label32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxNomerSSM
				 // 
				 this->textBoxNomerSSM->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxNomerSSM->Location = System::Drawing::Point(245, 182);
				 this->textBoxNomerSSM->MaxLength = 2;
				 this->textBoxNomerSSM->Name = L"textBoxNomerSSM";
				 this->textBoxNomerSSM->Size = System::Drawing::Size(565, 20);
				 this->textBoxNomerSSM->TabIndex = 55;
				 // 
				 // label33
				 // 
				 this->label33->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label33->AutoSize = true;
				 this->label33->Location = System::Drawing::Point(4, 257);
				 this->label33->Name = L"label33";
				 this->label33->Size = System::Drawing::Size(234, 13);
				 this->label33->TabIndex = 56;
				 this->label33->Text = L"Отправка RAW данных";
				 this->label33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // checkBoxSendRawData
				 // 
				 this->checkBoxSendRawData->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->checkBoxSendRawData->AutoSize = true;
				 this->checkBoxSendRawData->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 this->checkBoxSendRawData->Location = System::Drawing::Point(245, 256);
				 this->checkBoxSendRawData->Name = L"checkBoxSendRawData";
				 this->checkBoxSendRawData->Size = System::Drawing::Size(565, 14);
				 this->checkBoxSendRawData->TabIndex = 57;
				 this->checkBoxSendRawData->UseVisualStyleBackColor = true;
				 // 
				 // label35
				 // 
				 this->label35->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label35->AutoSize = true;
				 this->label35->Location = System::Drawing::Point(4, 223);
				 this->label35->Name = L"label35";
				 this->label35->Size = System::Drawing::Size(234, 13);
				 this->label35->TabIndex = 58;
				 this->label35->Text = L"IP ССМ";
				 this->label35->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // IpSSM
				 // 
				 this->IpSSM->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->IpSSM->Location = System::Drawing::Point(245, 220);
				 this->IpSSM->Name = L"IpSSM";
				 this->IpSSM->Size = System::Drawing::Size(565, 20);
				 this->IpSSM->TabIndex = 59;
				 // 
				 // tabPage6
				 // 
				 this->tabPage6->Controls->Add(this->MagicTextBox);
				 this->tabPage6->Controls->Add(this->label36);
				 this->tabPage6->Location = System::Drawing::Point(4, 22);
				 this->tabPage6->Name = L"tabPage6";
				 this->tabPage6->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage6->Size = System::Drawing::Size(825, 572);
				 this->tabPage6->TabIndex = 2;
				 this->tabPage6->Text = L"Доп. настройки";
				 this->tabPage6->UseVisualStyleBackColor = true;
				 // 
				 // MagicTextBox
				 // 
				 this->MagicTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->MagicTextBox->Location = System::Drawing::Point(8, 28);
				 this->MagicTextBox->Name = L"MagicTextBox";
				 this->MagicTextBox->Size = System::Drawing::Size(798, 87);
				 this->MagicTextBox->TabIndex = 1;
				 this->MagicTextBox->Text = L"";
				 // 
				 // label36
				 // 
				 this->label36->AutoSize = true;
				 this->label36->Location = System::Drawing::Point(5, 3);
				 this->label36->Name = L"label36";
				 this->label36->Size = System::Drawing::Size(66, 13);
				 this->label36->TabIndex = 0;
				 this->label36->Text = L"Magic String";
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->tableLayoutPanel12);
				 this->tabPage2->Location = System::Drawing::Point(4, 22);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(825, 572);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Внешние соединения";
				 this->tabPage2->ToolTipText = L"Внешние соединения";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // tableLayoutPanel12
				 // 
				 this->tableLayoutPanel12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel12->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->tableLayoutPanel12->ColumnCount = 2;
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 103)));
				 this->tableLayoutPanel12->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 785)));
				 this->tableLayoutPanel12->Controls->Add(this->label56, 0, 8);
				 this->tableLayoutPanel12->Controls->Add(this->textBoxSSMTime, 1, 8);
				 this->tableLayoutPanel12->Controls->Add(this->label49, 0, 0);
				 this->tableLayoutPanel12->Controls->Add(this->label11, 0, 1);
				 this->tableLayoutPanel12->Controls->Add(this->label12, 0, 2);
				 this->tableLayoutPanel12->Controls->Add(this->label13, 0, 3);
				 this->tableLayoutPanel12->Controls->Add(this->label14, 0, 4);
				 this->tableLayoutPanel12->Controls->Add(this->textBox1, 1, 2);
				 this->tableLayoutPanel12->Controls->Add(this->textBox2, 1, 3);
				 this->tableLayoutPanel12->Controls->Add(this->textBox3, 1, 4);
				 this->tableLayoutPanel12->Controls->Add(this->BtnCheckOracle, 1, 1);
				 this->tableLayoutPanel12->Controls->Add(this->tableLayoutPanel16, 1, 9);
				 this->tableLayoutPanel12->Controls->Add(this->tableLayoutPanel17, 0, 9);
				 this->tableLayoutPanel12->Controls->Add(this->label57, 0, 7);
				 this->tableLayoutPanel12->Controls->Add(this->textBoxSSMIP, 1, 7);
				 this->tableLayoutPanel12->Controls->Add(this->label59, 0, 6);
				 this->tableLayoutPanel12->Controls->Add(this->label15, 0, 5);
				 this->tableLayoutPanel12->Controls->Add(this->textBox8, 1, 5);
				 this->tableLayoutPanel12->Controls->Add(this->toolStripButton1, 1, 0);
				 this->tableLayoutPanel12->Controls->Add(this->checkDatcTrack, 1, 10);
				 this->tableLayoutPanel12->Controls->Add(this->tableLayoutPanel10, 1, 6);
				 this->tableLayoutPanel12->Location = System::Drawing::Point(6, 6);
				 this->tableLayoutPanel12->Name = L"tableLayoutPanel12";
				 this->tableLayoutPanel12->RowCount = 11;
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 
					 29)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 12.5F)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 
					 58)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 
					 20)));
				 this->tableLayoutPanel12->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 
					 20)));
				 this->tableLayoutPanel12->Size = System::Drawing::Size(813, 379);
				 this->tableLayoutPanel12->TabIndex = 2;
				 // 
				 // label56
				 // 
				 this->label56->AutoSize = true;
				 this->label56->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label56->Location = System::Drawing::Point(4, 262);
				 this->label56->Name = L"label56";
				 this->label56->Size = System::Drawing::Size(97, 32);
				 this->label56->TabIndex = 48;
				 this->label56->Text = L"Интервал отправки (мс)";
				 this->label56->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxSSMTime
				 // 
				 this->textBoxSSMTime->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxSSMTime->Location = System::Drawing::Point(108, 268);
				 this->textBoxSSMTime->Name = L"textBoxSSMTime";
				 this->textBoxSSMTime->Size = System::Drawing::Size(779, 20);
				 this->textBoxSSMTime->TabIndex = 47;
				 this->textBoxSSMTime->Text = L"500";
				 // 
				 // label49
				 // 
				 this->label49->AutoSize = true;
				 this->label49->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(204)));
				 this->label49->Location = System::Drawing::Point(4, 1);
				 this->label49->Name = L"label49";
				 this->label49->Size = System::Drawing::Size(97, 29);
				 this->label49->TabIndex = 24;
				 this->label49->Text = L"Внешнее";
				 this->label49->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label11
				 // 
				 this->label11->AutoSize = true;
				 this->label11->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(204)));
				 this->label11->Location = System::Drawing::Point(4, 31);
				 this->label11->Name = L"label11";
				 this->label11->Size = System::Drawing::Size(97, 32);
				 this->label11->TabIndex = 25;
				 this->label11->Text = L"Oracle";
				 this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label12
				 // 
				 this->label12->AutoSize = true;
				 this->label12->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label12->Location = System::Drawing::Point(4, 64);
				 this->label12->Name = L"label12";
				 this->label12->Size = System::Drawing::Size(97, 32);
				 this->label12->TabIndex = 26;
				 this->label12->Text = L"Data source";
				 this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label13
				 // 
				 this->label13->AutoSize = true;
				 this->label13->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label13->Location = System::Drawing::Point(4, 97);
				 this->label13->Name = L"label13";
				 this->label13->Size = System::Drawing::Size(97, 32);
				 this->label13->TabIndex = 27;
				 this->label13->Text = L"User";
				 this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label14
				 // 
				 this->label14->AutoSize = true;
				 this->label14->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label14->Location = System::Drawing::Point(4, 130);
				 this->label14->Name = L"label14";
				 this->label14->Size = System::Drawing::Size(97, 32);
				 this->label14->TabIndex = 28;
				 this->label14->Text = L"Password";
				 this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox1
				 // 
				 this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBox1->Location = System::Drawing::Point(108, 67);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(779, 20);
				 this->textBox1->TabIndex = 29;
				 // 
				 // textBox2
				 // 
				 this->textBox2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBox2->Location = System::Drawing::Point(108, 100);
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(779, 20);
				 this->textBox2->TabIndex = 30;
				 this->textBox2->Text = L"MTS_SCALES";
				 // 
				 // textBox3
				 // 
				 this->textBox3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBox3->Location = System::Drawing::Point(108, 133);
				 this->textBox3->Name = L"textBox3";
				 this->textBox3->Size = System::Drawing::Size(779, 20);
				 this->textBox3->TabIndex = 31;
				 this->textBox3->UseSystemPasswordChar = true;
				 // 
				 // BtnCheckOracle
				 // 
				 this->BtnCheckOracle->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->BtnCheckOracle->Location = System::Drawing::Point(108, 34);
				 this->BtnCheckOracle->Name = L"BtnCheckOracle";
				 this->BtnCheckOracle->Size = System::Drawing::Size(779, 26);
				 this->BtnCheckOracle->TabIndex = 40;
				 this->BtnCheckOracle->Text = L"Проверить соединение";
				 this->BtnCheckOracle->UseVisualStyleBackColor = true;
				 this->BtnCheckOracle->Click += gcnew System::EventHandler(this, &AdminForm::BtnCheckOracle_Click_1);
				 // 
				 // tableLayoutPanel16
				 // 
				 this->tableLayoutPanel16->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->tableLayoutPanel16->ColumnCount = 1;
				 this->tableLayoutPanel16->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel16->Controls->Add(this->textBoxSSMPortMicrosim, 0, 0);
				 this->tableLayoutPanel16->Controls->Add(this->textBoxSSMJaguar, 0, 1);
				 this->tableLayoutPanel16->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel16->Location = System::Drawing::Point(105, 295);
				 this->tableLayoutPanel16->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanel16->Name = L"tableLayoutPanel16";
				 this->tableLayoutPanel16->RowCount = 2;
				 this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel16->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel16->Size = System::Drawing::Size(785, 58);
				 this->tableLayoutPanel16->TabIndex = 42;
				 // 
				 // textBoxSSMPortMicrosim
				 // 
				 this->textBoxSSMPortMicrosim->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxSSMPortMicrosim->Location = System::Drawing::Point(4, 4);
				 this->textBoxSSMPortMicrosim->Name = L"textBoxSSMPortMicrosim";
				 this->textBoxSSMPortMicrosim->Size = System::Drawing::Size(777, 20);
				 this->textBoxSSMPortMicrosim->TabIndex = 0;
				 this->textBoxSSMPortMicrosim->Text = L"1106";
				 // 
				 // textBoxSSMJaguar
				 // 
				 this->textBoxSSMJaguar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBoxSSMJaguar->Location = System::Drawing::Point(4, 33);
				 this->textBoxSSMJaguar->Name = L"textBoxSSMJaguar";
				 this->textBoxSSMJaguar->Size = System::Drawing::Size(777, 20);
				 this->textBoxSSMJaguar->TabIndex = 1;
				 this->textBoxSSMJaguar->Text = L"1105";
				 // 
				 // tableLayoutPanel17
				 // 
				 this->tableLayoutPanel17->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
				 this->tableLayoutPanel17->ColumnCount = 1;
				 this->tableLayoutPanel17->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel17->Controls->Add(this->lable99, 0, 0);
				 this->tableLayoutPanel17->Controls->Add(this->label6, 0, 1);
				 this->tableLayoutPanel17->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->tableLayoutPanel17->Location = System::Drawing::Point(1, 295);
				 this->tableLayoutPanel17->Margin = System::Windows::Forms::Padding(0);
				 this->tableLayoutPanel17->Name = L"tableLayoutPanel17";
				 this->tableLayoutPanel17->RowCount = 2;
				 this->tableLayoutPanel17->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel17->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel17->Size = System::Drawing::Size(103, 58);
				 this->tableLayoutPanel17->TabIndex = 43;
				 // 
				 // lable99
				 // 
				 this->lable99->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->lable99->AutoSize = true;
				 this->lable99->Location = System::Drawing::Point(4, 8);
				 this->lable99->Name = L"lable99";
				 this->lable99->Size = System::Drawing::Size(95, 13);
				 this->lable99->TabIndex = 0;
				 this->lable99->Text = L"Порт Microsim";
				 this->lable99->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label6
				 // 
				 this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(4, 36);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(95, 13);
				 this->label6->TabIndex = 1;
				 this->label6->Text = L"Порт Jaguar";
				 this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label57
				 // 
				 this->label57->AutoSize = true;
				 this->label57->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label57->Location = System::Drawing::Point(4, 229);
				 this->label57->Name = L"label57";
				 this->label57->Size = System::Drawing::Size(97, 32);
				 this->label57->TabIndex = 35;
				 this->label57->Text = L"IP";
				 this->label57->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBoxSSMIP
				 // 
				 this->textBoxSSMIP->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBoxSSMIP->Location = System::Drawing::Point(108, 234);
				 this->textBoxSSMIP->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->textBoxSSMIP->Name = L"textBoxSSMIP";
				 this->textBoxSSMIP->Size = System::Drawing::Size(779, 20);
				 this->textBoxSSMIP->TabIndex = 38;
				 this->textBoxSSMIP->Text = L"127.0.0.1";
				 // 
				 // label59
				 // 
				 this->label59->AutoSize = true;
				 this->label59->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label59->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
					 static_cast<System::Byte>(204)));
				 this->label59->Location = System::Drawing::Point(4, 196);
				 this->label59->Name = L"label59";
				 this->label59->Size = System::Drawing::Size(97, 32);
				 this->label59->TabIndex = 33;
				 this->label59->Text = L"Data Track";
				 this->label59->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // label15
				 // 
				 this->label15->AutoSize = true;
				 this->label15->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->label15->Location = System::Drawing::Point(4, 163);
				 this->label15->Name = L"label15";
				 this->label15->Size = System::Drawing::Size(97, 32);
				 this->label15->TabIndex = 44;
				 this->label15->Text = L"Интервал отправки (мс)";
				 this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox8
				 // 
				 this->textBox8->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->textBox8->Location = System::Drawing::Point(108, 168);
				 this->textBox8->Margin = System::Windows::Forms::Padding(3, 5, 3, 3);
				 this->textBox8->Name = L"textBox8";
				 this->textBox8->Size = System::Drawing::Size(779, 20);
				 this->textBox8->TabIndex = 45;
				 this->textBox8->Text = L"500";
				 // 
				 // toolStripButton1
				 // 
				 this->toolStripButton1->AutoSize = true;
				 this->toolStripButton1->Location = System::Drawing::Point(108, 4);
				 this->toolStripButton1->Name = L"toolStripButton1";
				 this->toolStripButton1->Size = System::Drawing::Size(118, 17);
				 this->toolStripButton1->TabIndex = 46;
				 this->toolStripButton1->Text = L"Передача в Oracle";
				 this->toolStripButton1->UseVisualStyleBackColor = true;
				 this->toolStripButton1->Click += gcnew System::EventHandler(this, &AdminForm::checkBox5_Click);
				 // 
				 // checkDatcTrack
				 // 
				 this->checkDatcTrack->AutoSize = true;
				 this->checkDatcTrack->Location = System::Drawing::Point(108, 357);
				 this->checkDatcTrack->Name = L"checkDatcTrack";
				 this->checkDatcTrack->Size = System::Drawing::Size(150, 17);
				 this->checkDatcTrack->TabIndex = 49;
				 this->checkDatcTrack->Text = L"Передача данных в CCM";
				 this->checkDatcTrack->UseVisualStyleBackColor = true;
				 this->checkDatcTrack->Click += gcnew System::EventHandler(this, &AdminForm::checkDatcTrack_Click);
				 // 
				 // tableLayoutPanel10
				 // 
				 this->tableLayoutPanel10->Anchor = System::Windows::Forms::AnchorStyles::Left;
				 this->tableLayoutPanel10->ColumnCount = 4;
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 63.32047F)));
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 36.67953F)));
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 84)));
				 this->tableLayoutPanel10->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
					 124)));
				 this->tableLayoutPanel10->Controls->Add(this->buttonDtAdd, 1, 0);
				 this->tableLayoutPanel10->Controls->Add(this->buttonDtSave, 2, 0);
				 this->tableLayoutPanel10->Controls->Add(this->buttonDTDel, 3, 0);
				 this->tableLayoutPanel10->Controls->Add(this->comboBoxDt, 0, 0);
				 this->tableLayoutPanel10->Location = System::Drawing::Point(108, 199);
				 this->tableLayoutPanel10->Name = L"tableLayoutPanel10";
				 this->tableLayoutPanel10->RowCount = 1;
				 this->tableLayoutPanel10->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel10->Size = System::Drawing::Size(458, 26);
				 this->tableLayoutPanel10->TabIndex = 50;
				 // 
				 // buttonDtAdd
				 // 
				 this->buttonDtAdd->Location = System::Drawing::Point(161, 3);
				 this->buttonDtAdd->Name = L"buttonDtAdd";
				 this->buttonDtAdd->Size = System::Drawing::Size(75, 20);
				 this->buttonDtAdd->TabIndex = 0;
				 this->buttonDtAdd->Text = L"Add";
				 this->buttonDtAdd->UseVisualStyleBackColor = true;
				 this->buttonDtAdd->Click += gcnew System::EventHandler(this, &AdminForm::buttonDtAdd_Click);
				 // 
				 // buttonDtSave
				 // 
				 this->buttonDtSave->Location = System::Drawing::Point(252, 3);
				 this->buttonDtSave->Name = L"buttonDtSave";
				 this->buttonDtSave->Size = System::Drawing::Size(75, 20);
				 this->buttonDtSave->TabIndex = 1;
				 this->buttonDtSave->Text = L"Save";
				 this->buttonDtSave->UseVisualStyleBackColor = true;
				 this->buttonDtSave->Click += gcnew System::EventHandler(this, &AdminForm::buttonDtSave_Click);
				 // 
				 // buttonDTDel
				 // 
				 this->buttonDTDel->Location = System::Drawing::Point(336, 3);
				 this->buttonDTDel->Name = L"buttonDTDel";
				 this->buttonDTDel->Size = System::Drawing::Size(75, 20);
				 this->buttonDTDel->TabIndex = 2;
				 this->buttonDTDel->Text = L"Del";
				 this->buttonDTDel->UseVisualStyleBackColor = true;
				 this->buttonDTDel->Click += gcnew System::EventHandler(this, &AdminForm::buttonDTDel_Click);
				 // 
				 // comboBoxDt
				 // 
				 this->comboBoxDt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->comboBoxDt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
				 this->comboBoxDt->FormattingEnabled = true;
				 this->comboBoxDt->Location = System::Drawing::Point(3, 3);
				 this->comboBoxDt->Name = L"comboBoxDt";
				 this->comboBoxDt->Size = System::Drawing::Size(152, 21);
				 this->comboBoxDt->TabIndex = 3;
				 this->comboBoxDt->SelectedIndexChanged += gcnew System::EventHandler(this, &AdminForm::comboBoxDt_SelectedIndexChanged);
				 // 
				 // tableLayoutPanel1
				 // 
				 this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel1->ColumnCount = 1;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel1->Controls->Add(this->tabControl1, 0, 0);
				 this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
				 this->tableLayoutPanel1->Location = System::Drawing::Point(0, 28);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 2;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 54)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(839, 658);
				 this->tableLayoutPanel1->TabIndex = 3;
				 // 
				 // tableLayoutPanel2
				 // 
				 this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
					 | System::Windows::Forms::AnchorStyles::Left) 
					 | System::Windows::Forms::AnchorStyles::Right));
				 this->tableLayoutPanel2->ColumnCount = 2;
				 this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
					 50)));
				 this->tableLayoutPanel2->Controls->Add(this->btnCancel, 0, 0);
				 this->tableLayoutPanel2->Controls->Add(this->btnOk, 0, 0);
				 this->tableLayoutPanel2->Location = System::Drawing::Point(3, 607);
				 this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
				 this->tableLayoutPanel2->RowCount = 1;
				 this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel2->Size = System::Drawing::Size(833, 48);
				 this->tableLayoutPanel2->TabIndex = 3;
				 // 
				 // btnCancel
				 // 
				 this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
				 this->btnCancel->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->btnCancel->Location = System::Drawing::Point(419, 3);
				 this->btnCancel->Name = L"btnCancel";
				 this->btnCancel->Size = System::Drawing::Size(411, 42);
				 this->btnCancel->TabIndex = 2;
				 this->btnCancel->Text = L"Cancel";
				 this->btnCancel->UseVisualStyleBackColor = true;
				 // 
				 // btnOk
				 // 
				 this->btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
				 this->btnOk->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->btnOk->Enabled = false;
				 this->btnOk->Location = System::Drawing::Point(3, 3);
				 this->btnOk->Name = L"btnOk";
				 this->btnOk->Size = System::Drawing::Size(410, 42);
				 this->btnOk->TabIndex = 1;
				 this->btnOk->Text = L"OK";
				 this->btnOk->UseVisualStyleBackColor = true;
				 this->btnOk->Click += gcnew System::EventHandler(this, &AdminForm::btnOk_Click_1);
				 // 
				 // label7
				 // 
				 this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(3, 10);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(392, 13);
				 this->label7->TabIndex = 0;
				 this->label7->Text = L"IP Адрес";
				 this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox4
				 // 
				 this->textBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox4->Location = System::Drawing::Point(401, 7);
				 this->textBox4->Name = L"textBox4";
				 this->textBox4->Size = System::Drawing::Size(393, 20);
				 this->textBox4->TabIndex = 1;
				 // 
				 // label8
				 // 
				 this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(3, 44);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(392, 13);
				 this->label8->TabIndex = 2;
				 this->label8->Text = L"Порт";
				 this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox5
				 // 
				 this->textBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox5->Location = System::Drawing::Point(401, 41);
				 this->textBox5->Name = L"textBox5";
				 this->textBox5->Size = System::Drawing::Size(393, 20);
				 this->textBox5->TabIndex = 3;
				 // 
				 // label9
				 // 
				 this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label9->AutoSize = true;
				 this->label9->Location = System::Drawing::Point(3, 77);
				 this->label9->Name = L"label9";
				 this->label9->Size = System::Drawing::Size(392, 13);
				 this->label9->TabIndex = 4;
				 this->label9->Text = L"Обновление";
				 this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox6
				 // 
				 this->textBox6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox6->Location = System::Drawing::Point(401, 74);
				 this->textBox6->Name = L"textBox6";
				 this->textBox6->Size = System::Drawing::Size(393, 20);
				 this->textBox6->TabIndex = 5;
				 // 
				 // label10
				 // 
				 this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label10->AutoSize = true;
				 this->label10->Location = System::Drawing::Point(3, 10);
				 this->label10->Name = L"label10";
				 this->label10->Size = System::Drawing::Size(392, 13);
				 this->label10->TabIndex = 0;
				 this->label10->Text = L"IP Адрес";
				 this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox7
				 // 
				 this->textBox7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox7->Location = System::Drawing::Point(401, 7);
				 this->textBox7->Name = L"textBox7";
				 this->textBox7->Size = System::Drawing::Size(393, 20);
				 this->textBox7->TabIndex = 1;
				 // 
				 // label16
				 // 
				 this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label16->AutoSize = true;
				 this->label16->Location = System::Drawing::Point(3, 44);
				 this->label16->Name = L"label16";
				 this->label16->Size = System::Drawing::Size(392, 13);
				 this->label16->TabIndex = 2;
				 this->label16->Text = L"Порт";
				 this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox9
				 // 
				 this->textBox9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox9->Location = System::Drawing::Point(401, 41);
				 this->textBox9->Name = L"textBox9";
				 this->textBox9->Size = System::Drawing::Size(393, 20);
				 this->textBox9->TabIndex = 3;
				 // 
				 // label17
				 // 
				 this->label17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label17->AutoSize = true;
				 this->label17->Location = System::Drawing::Point(3, 77);
				 this->label17->Name = L"label17";
				 this->label17->Size = System::Drawing::Size(392, 13);
				 this->label17->TabIndex = 4;
				 this->label17->Text = L"Обновление";
				 this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox10
				 // 
				 this->textBox10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox10->Location = System::Drawing::Point(401, 74);
				 this->textBox10->Name = L"textBox10";
				 this->textBox10->Size = System::Drawing::Size(393, 20);
				 this->textBox10->TabIndex = 5;
				 // 
				 // label18
				 // 
				 this->label18->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label18->AutoSize = true;
				 this->label18->Location = System::Drawing::Point(3, 10);
				 this->label18->Name = L"label18";
				 this->label18->Size = System::Drawing::Size(392, 13);
				 this->label18->TabIndex = 0;
				 this->label18->Text = L"IP Адрес";
				 this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox11
				 // 
				 this->textBox11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox11->Location = System::Drawing::Point(401, 7);
				 this->textBox11->Name = L"textBox11";
				 this->textBox11->Size = System::Drawing::Size(393, 20);
				 this->textBox11->TabIndex = 1;
				 // 
				 // label19
				 // 
				 this->label19->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label19->AutoSize = true;
				 this->label19->Location = System::Drawing::Point(3, 44);
				 this->label19->Name = L"label19";
				 this->label19->Size = System::Drawing::Size(392, 13);
				 this->label19->TabIndex = 2;
				 this->label19->Text = L"Порт";
				 this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox12
				 // 
				 this->textBox12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox12->Location = System::Drawing::Point(401, 41);
				 this->textBox12->Name = L"textBox12";
				 this->textBox12->Size = System::Drawing::Size(393, 20);
				 this->textBox12->TabIndex = 3;
				 // 
				 // label20
				 // 
				 this->label20->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->label20->AutoSize = true;
				 this->label20->Location = System::Drawing::Point(3, 77);
				 this->label20->Name = L"label20";
				 this->label20->Size = System::Drawing::Size(392, 13);
				 this->label20->TabIndex = 4;
				 this->label20->Text = L"Обновление";
				 this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 // 
				 // textBox13
				 // 
				 this->textBox13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
				 this->textBox13->Location = System::Drawing::Point(401, 74);
				 this->textBox13->Name = L"textBox13";
				 this->textBox13->Size = System::Drawing::Size(393, 20);
				 this->textBox13->TabIndex = 5;
				 // 
				 // AdminForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->AutoSize = true;
				 this->ClientSize = System::Drawing::Size(839, 698);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->Controls->Add(this->toolStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
				 this->Location = System::Drawing::Point(137, 202);
				 this->Name = L"AdminForm";
				 this->Text = L"AdminForm ";
				 this->Load += gcnew System::EventHandler(this, &AdminForm::AdminForm_Load);
				 this->toolStrip1->ResumeLayout(false);
				 this->toolStrip1->PerformLayout();
				 this->tabControl1->ResumeLayout(false);
				 this->tabPage1->ResumeLayout(false);
				 this->tableLayoutPanel4->ResumeLayout(false);
				 this->tableLayoutPanel3->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
				 this->tabControlType->ResumeLayout(false);
				 this->tabPage3->ResumeLayout(false);
				 this->tableLayoutPanelTypeCom->ResumeLayout(false);
				 this->tableLayoutPanelTypeCom->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
				 this->tableLayoutPanel7->ResumeLayout(false);
				 this->tabPage4->ResumeLayout(false);
				 this->tableLayoutPanel5->ResumeLayout(false);
				 this->tableLayoutPanel5->PerformLayout();
				 this->tabPage5->ResumeLayout(false);
				 this->tableLayoutPanel9->ResumeLayout(false);
				 this->tableLayoutPanel9->PerformLayout();
				 this->tableLayoutPanel6->ResumeLayout(false);
				 this->tableLayoutPanel6->PerformLayout();
				 this->tableLayoutPanel8->ResumeLayout(false);
				 this->tableLayoutPanel8->PerformLayout();
				 this->tabPage6->ResumeLayout(false);
				 this->tabPage6->PerformLayout();
				 this->tabPage2->ResumeLayout(false);
				 this->tableLayoutPanel12->ResumeLayout(false);
				 this->tableLayoutPanel12->PerformLayout();
				 this->tableLayoutPanel16->ResumeLayout(false);
				 this->tableLayoutPanel16->PerformLayout();
				 this->tableLayoutPanel17->ResumeLayout(false);
				 this->tableLayoutPanel17->PerformLayout();
				 this->tableLayoutPanel10->ResumeLayout(false);
				 this->tableLayoutPanel1->ResumeLayout(false);
				 this->tableLayoutPanel2->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion




	private: System::Void AdminForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 cbxSpeed->SelectedIndex = 5 ;
				 cbxParity->SelectedIndex = 2 ;
				 cbxStopBits->SelectedIndex = 1 ;



			 }
	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

				}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void btnSave_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Сохраняем текущий элемент

				 for each(List<String^>^ elem in _weight ) {
					 if (this->toolStripComboBox1->SelectedItem->ToString() == elem[0])
					 {
						 elem[0] = this->txtBxName->Text;
						 elem[1] = this->txtBxPlace->Text;
						 elem[2] = this->comboBox1->SelectedItem->ToString() ;
						 elem[3] = this->cbxSpeed->SelectedItem->ToString() ;
						 elem[4] = this->cbxParity->SelectedItem->ToString() ;
						 elem[5] = this->numericUpDown2->Value.ToString();
						 elem[6] = this->cbxStopBits->SelectedItem->ToString() ;
						 elem[7] = this->numericUpDown1->Value.ToString();
						 MessageBox::Show("Настройки для: " + this->txtBxName->Text + " сохранены успешно", "Сохранение", MessageBoxButtons::OK,MessageBoxIcon::Information); 
					 }

				 }


			 }
	private: System::Void btnDel_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Удаление элементов из списка
				 List<List<String^>^>^ _temp = gcnew List<List<String^>^>();
				 for each(List<String^>^ elem in _weight ) 
				 {
					 if (this->toolStripComboBox1->SelectedItem->ToString() != elem[0])
					 {//Если не равно добавляем в новый список
						 _temp->Add(elem);
					 }

				 }

				 MessageBox::Show("Весоизмеритель удален", "Удаление", MessageBoxButtons::OK,MessageBoxIcon::Information );
				 _weight = _temp;
				 this->_setWeight(_weight);
				 try{
					 this->toolStripComboBox1->SelectedIndex = 0;
				 }
				 catch (Exception ^e) {
					 //Выключаем кнопки
					 this->toolStripComboBox1->Enabled = 0;
					 this->btnDel->Enabled = 0;
					 this->btnSave->Enabled = 0;
				 }
			 }
	private: System::Void toolStripComboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->txtBxName->Clear();
				 this->txtBxPlace->Clear();
				 this->numericUpDown1->Value = 0;
				 this->numericUpDown2->Value = 0;

				 int selectedIndex = this->toolStripComboBox1->SelectedIndex;
				 Object^ selectedItem = this->toolStripComboBox1->SelectedItem;

				 for each(List<String^>^ elem in _weight ) {
					 if (selectedItem->ToString() == elem[0])
					 {
						 this->txtBxName->Text = elem[0];
						 this->txtBxPlace->Text = elem[1];
						 this->comboBox1->SelectedItem  = elem[2];
						 this->cbxSpeed->SelectedItem  = elem[3];
						 this->cbxParity->SelectedItem  = elem[4];
						 this->numericUpDown2->Value = int::Parse(elem[5]);
						 this->cbxStopBits->SelectedItem  = elem[6];
						 this->numericUpDown1->Value = int::Parse(elem[7]);
					 }

				 }
			 }
	private: System::Void toolStripComboBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Добавляем новый
				 int selectedIndex = this->comboBox1->SelectedIndex;
				 Object^ selectedItem = this->comboBox1->SelectedItem;

				 //Проверим номер весоизмерителя на цифры
				 try{
					 Int32::Parse(this->txtBxName->Text);
				 }
				 catch (Exception ^e){
					 MessageBox::Show("Номер весоизмерителя не число", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Warning );
					 return;
				 }


				 int count = 0;
				 for each(List<String^>^ elem in _weight ) {
					 if (this->txtBxName->Text == elem[0]) count++;

				 }
				 if (count) {
					 MessageBox::Show("Не уникальный номер весоизмерителя", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Warning );
				 }

				 else if (selectedIndex.ToString() != "-1" ){
					 List<String^>^ w1= gcnew List<String^>();
					 w1->Add(this->txtBxName->Text);  //Номер
					 w1->Add(this->txtBxPlace->Text); //местоположение
					 w1->Add(selectedItem->ToString()); //порт
					 w1->Add(this->cbxSpeed->SelectedItem->ToString()); // скорость
					 w1->Add(this->cbxParity->SelectedItem->ToString()); // parity
					 w1->Add(this->numericUpDown2->Value.ToString()); //количество бит
					 w1->Add(this->cbxStopBits->SelectedItem->ToString()); //стоповые биты
					 w1->Add(this->numericUpDown1->Value.ToString()); //интервал обноления
					 _weight->Add(w1);

					 MessageBox::Show("Весоизмеритель: " + this->txtBxName->Text + " добавлен успешно", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Information);
					 this->_setWeight(_weight);

					 //Выбираем нужный в combobox'e
					 int index = this->toolStripComboBox1->FindString( this->txtBxName->Text);
					 this->toolStripComboBox1->SelectedIndex = index;
					 this->toolStripComboBox1->Enabled = 1;
					 this->btnDel->Enabled = 1;
					 this->btnSave->Enabled = 1;
				 }
				 else {
					 MessageBox::Show("Не сохранено, проверьте настройки", "Добавление", MessageBoxButtons::OK, MessageBoxIcon::Error );
				 }



			 }
	private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void BtnCheckOracle_Click(System::Object^  sender, System::EventArgs^  e) {
				 ////	Проверяем подключеник к Оракл

				 String^ ConnectionString ="Data Source="+ this->textBox1->Text +";User ID="+ this->textBox2->Text +";Password="+ this->textBox3->Text +"";
				 OracleConnection^ OC = gcnew OracleConnection(ConnectionString);
				 try
				 {
					 OC->Open();
					 MessageBox::Show("Подключение к Oracle успешно", "Oracle", MessageBoxButtons::OK,MessageBoxIcon::Information); 
					 this->btnOk->Enabled = 1;
					 this->btnOk->BackColor = Color::LightGreen;
					 this->BtnCheckOracle->BackColor = this->btnSave->BackColor;
				 }
				 catch (Oracle::DataAccess::Types::OracleTypeException::Exception ^e)
				 { 
					 System::Windows::Forms::MessageBox::Show(e->ToString(), "Oracle",MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
				 finally
				 {
					 OC->Close(); 

				 }

			 }
	private: System::Void btnRefreshPorts_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Ищем порты 
				 this->comboBox1->Items->Clear();
				 array<String^>^ serialPorts = nullptr;
				 serialPorts = SerialPort::GetPortNames();
				 for each(String^ port in serialPorts)
				 {
					 this->comboBox1->Items->Add(port);
				 }
				 MessageBox::Show("Список портов обновлен", "Serial Port", MessageBoxButtons::OK, MessageBoxIcon::Information); 

			 }
	private: System::Void btnOk_Click(System::Object^  sender, System::EventArgs^  e) {
				 //

				 try {

					 if (this->toolStripButton1->Checked)
						 Int32::Parse(this->textBox8->Text);
					 else (this->textBox8->Text = "600");
					 // Int32::Parse(this->textBox7->Text);
					 // IPAddress::Parse(this->textBox5->Text);

					 if (this->btnOk->DialogResult == Tablitsa::DialogResult::None){
						 this->btnOk->DialogResult = Tablitsa::DialogResult::OK;
						 this->btnOk->Text = "ОК";
						 MessageBox::Show("Настройки внешних соединений верные", "Administrator", MessageBoxButtons::OK,MessageBoxIcon::Information); 

					 }

				 }
				 catch (Exception ^e) {
					 MessageBox::Show("Проверьте настройки внешних соединений", "Administrator", MessageBoxButtons::OK,MessageBoxIcon::Error);

				 }


			 }
	private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 }


	private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {//Включение выключенеи Oracle
				 //
				 this->BtnCheckOracle->Enabled = toolStripButton1->Checked;
				 this->textBox1->Enabled = toolStripButton1->Checked;
				 this->textBox2->Enabled = toolStripButton1->Checked;
				 this->textBox3->Enabled = toolStripButton1->Checked;
				 this->textBox8->Enabled = toolStripButton1->Checked;
				 this->label11->Enabled = toolStripButton1->Checked;
				 this->label12->Enabled = toolStripButton1->Checked;
				 this->label13->Enabled = toolStripButton1->Checked;
				 this->label14->Enabled = toolStripButton1->Checked;
				 this->label15->Enabled = toolStripButton1->Checked;

				 if (toolStripButton1->Checked) 
				 {
					 toolStripButton1->BackColor = Color::LightGreen;
					 BtnCheckOracle->BackColor = Color::LightGreen;
					 btnOk->BackColor =  this->btnCancel->BackColor;	
					 btnOk->Enabled = false;
				 }

				 else 
				 {
					 toolStripButton1->BackColor = Color::Red;
					 BtnCheckOracle->BackColor = this->btnCancel->BackColor;	
					 btnOk->BackColor = Color::LightGreen;
					 btnOk->Enabled = true;
				 }

			 }

	private: System::Void toolStripButtonPassword_Click(System::Object^  sender, System::EventArgs^  e) {
				 //
				 InputBox^ input;
				 input = gcnew Tablitsa::InputBox("Новый пароль", "Введите новый пароль");
				 String^ inPutHash;
				 if (input->ShowDialog( this ) == Tablitsa::DialogResult::OK) 
				 {
					 inPutHash = getHashSha256( input->getValue());
					 MessageBox::Show("Новый пароль: " + input->getValue() + ". Будет сохранень при сохранение общих настроек", "Готово",  MessageBoxButtons::OK, MessageBoxIcon::Information);	
					 currentPassHash = inPutHash;
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

	private: System::Void checkBox5_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Включение выключенеи Oracle
				 //
				 this->BtnCheckOracle->Enabled = toolStripButton1->Checked;
				 this->textBox1->Enabled = toolStripButton1->Checked;
				 this->textBox2->Enabled = toolStripButton1->Checked;
				 this->textBox3->Enabled = toolStripButton1->Checked;
				 this->textBox8->Enabled = toolStripButton1->Checked;
				 this->label11->Enabled = toolStripButton1->Checked;
				 this->label12->Enabled = toolStripButton1->Checked;
				 this->label13->Enabled = toolStripButton1->Checked;
				 this->label14->Enabled = toolStripButton1->Checked;
				 this->label15->Enabled = toolStripButton1->Checked;

				 if (toolStripButton1->Checked) 
				 {
					 toolStripButton1->BackColor = Color::LightGreen;
					 BtnCheckOracle->BackColor = Color::LightGreen;
					 btnOk->BackColor =  this->btnCancel->BackColor;	
					 btnOk->Enabled = false;
				 }

				 else 
				 {
					 toolStripButton1->BackColor = Color::Red;
					 BtnCheckOracle->BackColor = this->btnCancel->BackColor;	
					 btnOk->BackColor = Color::LightGreen;
					 btnOk->Enabled = true;
				 }
			 }
	private: System::Void btnOk_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 try {

					 if (this->toolStripButton1->Checked) // если Оракл включен
						 Int32::Parse(this->textBox8->Text);
					 else (this->textBox8->Text = "600");

					 if (this->checkDatcTrack->Checked) // если включен ССМ
					 {
						 Int32::Parse(this->textBoxSSMJaguar->Text);
						 IPAddress::Parse(this->textBoxSSMIP->Text);
						 Int32::Parse(this->textBoxSSMPortMicrosim->Text);
						 Int32::Parse(this->textBoxSSMTime->Text);
					 }

					 if (this->btnOk->DialogResult == Tablitsa::DialogResult::None){
						 this->btnOk->DialogResult = Tablitsa::DialogResult::OK;
						 this->btnOk->Text = "ОК";
						 MessageBox::Show("Настройки внешних соединений верные", "Administrator", MessageBoxButtons::OK,MessageBoxIcon::Information); 

					 }

				 }
				 catch (Exception ^e) {
					 MessageBox::Show("Проверьте настройки внешних соединений", "Administrator", MessageBoxButtons::OK,MessageBoxIcon::Error);

				 }



			 }
	private: System::Void BtnCheckOracle_Click_1(System::Object^  sender, System::EventArgs^  e) {

				 ////	Проверяем подключеник к Оракл

				 String^ ConnectionString ="Data Source="+ this->textBox1->Text +";User ID="+ this->textBox2->Text +";Password="+ this->textBox3->Text +"";
				 OracleConnection^ OC = gcnew OracleConnection(ConnectionString);
				 try
				 {
					 OC->Open();
					 MessageBox::Show("Подключение к Oracle успешно", "Oracle", MessageBoxButtons::OK,MessageBoxIcon::Information); 
					 this->btnOk->Enabled = 1;
					 this->btnOk->BackColor = Color::LightGreen;
					 this->BtnCheckOracle->BackColor = this->btnSave->BackColor;
				 }
				 catch (Oracle::DataAccess::Types::OracleTypeException::Exception ^e)
				 { 
					 System::Windows::Forms::MessageBox::Show(e->ToString(), "Oracle",MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
				 finally
				 {
					 OC->Close(); 

				 }
			 }
	private: System::Void toolStripComboBox1_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
				 this->txtBxName->Clear();
				 this->txtBxPlace->Clear();
				 this->numericUpDown1->Value = 0;
				 this->numericUpDown2->Value = 0;
				 labelModelDll->Visible = false;
				 comboBoxModelDll->Visible = false;
				 int selectedIndex = this->toolStripComboBox1->SelectedIndex;
				 Object^ selectedItem = this->toolStripComboBox1->SelectedItem;

				 for each(List<String^>^ elem in _weight ) {
					 if (selectedItem->ToString() == elem[0])
					 {
						 this->txtBxName->Text = elem[0];
						 this->txtBxPlace->Text = elem[1];
						 this->comboBoxED->SelectedItem = elem[12];
						 this->textBoxNomerSSM->Text = elem[13];
						 checkBoxSendRawData->Checked = bool::Parse(elem[14]);
						 if (elem[2] == "com") {
							 this->TypeConnect->SelectedIndex = 0;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = int::Parse(elem[6]);
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = int::Parse(elem[8]);
							 this->textBoxIpMoxa->Text = "";
							 this->textBoxPortMoxa->Text = "";
							 this->textBoxUpdateTCP->Text = "";
							 this->comboBoxED->SelectedItem = elem[12];

						 }

						 else if (elem[2] == "Microsim/TCPIP") {
							 this->TypeConnect->SelectedIndex = 1;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }

						 else if (elem[2] == "WE2120_ST/TCPIP") {
							 this->TypeConnect->SelectedIndex = 3;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }
						 else if (elem[2] == "WE2120_ALT/TCPIP") {
							 this->TypeConnect->SelectedIndex = 5;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }

						 else if (elem[2] == "INTECONT_OPUS_ST/TCPIP") {
							 this->TypeConnect->SelectedIndex = 6;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }
						 else if (elem[2] == "DISOMAT_SATUS/TCPIP") {
							 this->TypeConnect->SelectedIndex = 7;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }


						 else if (elem[2] == "DEFAULT/TCPIP") {
							 this->TypeConnect->SelectedIndex = 4;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }
						 //DATASCALES_REPEATER
						 else if (elem[2] == "DATASCALES_REPEATER") {
							 this->TypeConnect->SelectedIndex = 8;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];

						 }

						 //DATASCALES_DLL
						 else if (elem[2] == "DATASCALES_DLL") {
							 this->TypeConnect->SelectedIndex = 9;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxIpMoxa->Text = elem[9];
							 this->textBoxPortMoxa->Text = elem[10];
							 this->textBoxUpdateTCP->Text = elem[11];
							 this->comboBoxED->SelectedItem = elem[12];
							 labelModelDll->Visible = true;
							 comboBoxModelDll->Visible = true;
							 this->comboBoxModelDll->SelectedItem  = elem[17];
						 }

						 else if (elem[2] == "jaguar") {
							 this->TypeConnect->SelectedIndex = 2;
							 this->comboBox1->SelectedItem  = elem[3];
							 this->cbxSpeed->SelectedItem  = elem[4];
							 this->cbxParity->SelectedItem  = elem[5];
							 this->numericUpDown2->Value = 0;
							 this->cbxStopBits->SelectedItem  = elem[7];
							 this->numericUpDown1->Value = 0;
							 this->textBoxJaguarIP->Text = elem[9];
							 this->textBoxJaguarPort->Text = elem[10];
							 this->textBoxJaguarUpdate->Text = elem[11];

						 }
						 this->IpSSM ->Text = elem[15];
						 this->MagicTextBox->Text = elem[16];

					 }

				 }

			 }
	private: System::Void TypeConnect_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void TypeConnect_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
				 //Выбор типа подключения

				 if (TypeConnect->SelectedIndex == 0) {
					 //Выбран тип Microsim COM
					 tabControlType->SelectTab(0);
				 }
				 else if (TypeConnect->SelectedIndex == 1) {
					 //Выбран тип Microsim Ethernet
					 tabControlType->SelectTab(1);
				 }

				 else if (TypeConnect->SelectedIndex == 2) {
					 //Выбран тип Ягуар
					 tabControlType->SelectTab(2);
				 }

				 else if (TypeConnect->SelectedIndex == 9) {
					 //Выбран тип Модель
					 tabControlType->SelectTab(1);
					 labelModelDll->Visible = true;
					 comboBoxModelDll->Visible = true;
				 }

				 else {
					 labelModelDll->Visible = false;
					 comboBoxModelDll->Visible = false;

				 }
			 }
	private: System::Void tabControlType_Selecting(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^  e) {
				 //e->Cancel = true;
			 }
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void btnAdd_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 //Добавляем новый
				 int selectedIndex = this->comboBox1->SelectedIndex;
				 Object^ selectedItem = this->comboBox1->SelectedItem;

				 //Проверим номер весоизмерителя на цифры
				 try{
					 Int32::Parse(this->txtBxName->Text);
				 }
				 catch (Exception ^e){
					 MessageBox::Show("Номер весоизмерителя не число", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Warning );
					 return;
				 }


				 int count = 0;
				 for each(List<String^>^ elem in _weight ) {
					 if (this->txtBxName->Text == elem[0]) count++;

				 }
				 if (count) {
					 MessageBox::Show("Не уникальный номер весоизмерителя", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Warning );
				 }

				 else if ((selectedIndex.ToString() != "-1" ) || (TypeConnect->SelectedIndex != 0) ){
					 List<String^>^ w1= gcnew List<String^>();
					 w1->Add(this->txtBxName->Text);  //Номер
					 w1->Add(this->txtBxPlace->Text); //местоположение

					 if (TypeConnect->SelectedIndex == 0) {
						 w1->Add("com"); //тип подключения
						 w1->Add(selectedItem->ToString()); //порт
						 w1->Add(this->cbxSpeed->SelectedItem->ToString()); // скорость
						 w1->Add(this->cbxParity->SelectedItem->ToString()); // parity
						 w1->Add(this->numericUpDown2->Value.ToString()); //количество бит
						 w1->Add(this->cbxStopBits->SelectedItem->ToString()); //стоповые биты
						 w1->Add(this->numericUpDown1->Value.ToString()); //интервал обноления
						 w1->Add(""); //пустые поля
						 w1->Add(""); //пустые поля
						 w1->Add(""); //пустые поля
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц
					 }

					 else if (TypeConnect->SelectedIndex == 1) {
						 w1->Add("Microsim/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }

					 else if (TypeConnect->SelectedIndex == 3) {
						 w1->Add("WE2120_ST/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }
					 else if (TypeConnect->SelectedIndex == 4) {
						 w1->Add("DEFAULT/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }

					 else if (TypeConnect->SelectedIndex == 5) {
						 w1->Add("WE2120_ALT/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }

					 else if (TypeConnect->SelectedIndex == 6) {
						 w1->Add("INTECONT_OPUS_ST/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }
					 else if (TypeConnect->SelectedIndex == 7) {
						 w1->Add("DISOMAT_SATUS/TCPIP"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }

					 else if (TypeConnect->SelectedIndex == 8) {
						 w1->Add("DATASCALES_REPEATER"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц
					 }
					 else if (TypeConnect->SelectedIndex == 9) {
						 w1->Add("DATASCALES_DLL"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxIpMoxa->Text); //IP
						 w1->Add(textBoxPortMoxa->Text); //порт
						 w1->Add(textBoxUpdateTCP->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }
					 else if (TypeConnect->SelectedIndex == 2) {
						 //Ягуар
						 w1->Add("jaguar"); //тип подключения
						 w1->Add(""); //порт
						 w1->Add(""); // скорость
						 w1->Add(""); // parity
						 w1->Add(""); //количество бит
						 w1->Add(""); //стоповые биты
						 w1->Add(""); //интервал обноления
						 w1->Add(textBoxJaguarIP->Text); //IP
						 w1->Add(textBoxJaguarPort->Text); //порт
						 w1->Add(textBoxJaguarUpdate->Text); //обновление
						 w1->Add(this->comboBoxED->SelectedItem->ToString()); //тип едениц

					 }

					 w1->Add(this->textBoxNomerSSM->Text); //Номер в посылке пре передаче данных в ССМ, номер уникален
					 w1->Add(checkBoxSendRawData->Checked.ToString());
					 w1->Add(this->IpSSM->Text);
					 //w1->Add("False");
					 w1->Add(this->MagicTextBox->Text);

					 if (TypeConnect->SelectedIndex == 9 ) 
						 w1->Add(this->comboBoxModelDll->SelectedItem->ToString());
					 else 
						 w1->Add("-");

					 _weight->Add(w1);

					 MessageBox::Show("Весоизмеритель: " + this->txtBxName->Text + " добавлен успешно", "Добавление", MessageBoxButtons::OK,MessageBoxIcon::Information);
					 this->_setWeight(_weight);

					 //Выбираем нужный в combobox'e
					 int index = this->toolStripComboBox1->FindString( this->txtBxName->Text);
					 this->toolStripComboBox1->SelectedIndex = index;
					 this->toolStripComboBox1->Enabled = 1;
					 this->btnDel->Enabled = 1;
					 this->btnSave->Enabled = 1;
				 }
				 else {
					 MessageBox::Show("Не сохранено, проверьте настройки", "Добавление", MessageBoxButtons::OK, MessageBoxIcon::Error );
				 }


			 }
	private: System::Void btnSave_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 //Сохраняем текущий элемент

				 for each(List<String^>^ elem in _weight ) {
					 if (this->toolStripComboBox1->SelectedItem->ToString() == elem[0])
					 {
						 elem[0] = this->txtBxName->Text;
						 elem[1] = this->txtBxPlace->Text;

						 if (TypeConnect->SelectedIndex == 0) {
							 elem[2] = "com"; //тип подключения
							 elem[3] = this->comboBox1->SelectedItem->ToString(); //порт
							 elem[4] = this->cbxSpeed->SelectedItem->ToString(); // скорость
							 elem[5] =this->cbxParity->SelectedItem->ToString(); // parity
							 elem[6] =this->numericUpDown2->Value.ToString(); //количество бит
							 elem[7] =this->cbxStopBits->SelectedItem->ToString(); //стоповые биты
							 elem[8] =this->numericUpDown1->Value.ToString(); //интервал обноления
							 elem[9] =""; //пустые поля
							 elem[10] =""; //пустые поля
							 elem[11] =""; //пустые поля
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерения
						 }

						 else if (TypeConnect->SelectedIndex == 1) {
							 elem[2] = "Microsim/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени

						 }
						 else if (TypeConnect->SelectedIndex == 3) {

							 elem[2] = "WE2120_ST/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 4) {

							 elem[2] = "DEFAULT/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 5) {

							 elem[2] = "WE2120_ALT/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 6) {

							 elem[2] = "INTECONT_OPUS_ST/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }
						 else if (TypeConnect->SelectedIndex == 7) {

							 elem[2] = "DISOMAT_SATUS/TCPIP"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 8) {

							 elem[2] = "DATASCALES_REPEATER"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 9) {

							 elem[2] = "DATASCALES_DLL"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxIpMoxa->Text; //IP
							 elem[10] = textBoxPortMoxa->Text; //порт
							 elem[11] = textBoxUpdateTCP->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }

						 else if (TypeConnect->SelectedIndex == 2) {
							 elem[2] = "jaguar"; //тип подключения
							 elem[3] = ""; //порт
							 elem[4] = ""; // скорость
							 elem[5] = ""; // parity
							 elem[6] = ""; //количество бит
							 elem[7] = ""; //стоповые биты
							 elem[8] = ""; //интервал обноления
							 elem[9] = textBoxJaguarIP->Text; //IP
							 elem[10] = textBoxJaguarPort->Text; //апдейт
							 elem[11] = textBoxJaguarUpdate->Text; //обновление
							 elem[12] = this->comboBoxED->SelectedItem->ToString(); //Едегницы измерени
						 }
						 elem[13] = this->textBoxNomerSSM->Text; //Номер в посылке пре передаче данных в ССМ, номер уникален
						 elem[14] = checkBoxSendRawData->Checked.ToString();
						 elem[15] = this->IpSSM->Text;
						 elem[16] = this->MagicTextBox->Text;

						 if (TypeConnect->SelectedIndex == 9 ) 
							 elem[17]=  this->comboBoxModelDll->SelectedItem->ToString();
						 else 
							 elem[17] = "-";

						 MessageBox::Show("Настройки для: " + this->txtBxName->Text + " сохранены успешно", "Сохранение", MessageBoxButtons::OK,MessageBoxIcon::Information); 
					 }

				 }
			 }
	private: System::Void btnDel_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 //Удаление элементов из списка
				 List<List<String^>^>^ _temp = gcnew List<List<String^>^>();
				 for each(List<String^>^ elem in _weight ) 
				 {
					 if (this->toolStripComboBox1->SelectedItem->ToString() != elem[0])
					 {//Если не равно добавляем в новый список
						 _temp->Add(elem);
					 }

				 }

				 MessageBox::Show("Весоизмеритель удален", "Удаление", MessageBoxButtons::OK,MessageBoxIcon::Information );
				 _weight = _temp;
				 this->_setWeight(_weight);
				 try{
					 this->toolStripComboBox1->SelectedIndex = 0;
				 }
				 catch (Exception ^e) {
					 //Выключаем кнопки
					 this->toolStripComboBox1->Enabled = 0;
					 this->btnDel->Enabled = 0;
					 this->btnSave->Enabled = 0;
				 }
			 }
	private: System::Void checkDatcTrack_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Включение отлючение передачи данных ССМ

				 //
				 textBoxSSMIP->Enabled = checkDatcTrack->Checked;
				 textBoxSSMTime->Enabled = checkDatcTrack->Checked;
				 textBoxSSMPortMicrosim->Enabled  = checkDatcTrack->Checked;
				 textBoxSSMJaguar->Enabled = checkDatcTrack->Checked;

				 if (checkDatcTrack->Checked) 
				 {
					 checkDatcTrack->BackColor = Color::LightGreen;
				 }

				 else 
				 {
					 checkDatcTrack->BackColor = Color::Red;
				 }



			 }
	private: System::Void tableLayoutPanel6_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 }

	private: System::Void comboBoxDt_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 ////
				 for each (List<String^>^ elem in _data)
				 {
					 if (elem[0] == this->comboBoxDt->SelectedItem->ToString()){
						 //Выводим то что нужно
						 textBoxSSMIP->Text = elem[0];
						 textBoxSSMTime->Text = elem[1];
						 textBoxSSMPortMicrosim->Text = elem[2];
						 textBoxSSMJaguar->Text = elem[3];

						 if (bool::Parse(elem[4]))
							 checkDatcTrack->Checked = 1;
						 else checkDatcTrack->Checked = 0;
					 }

				 }


			 }
	private: System::Void buttonDtAdd_Click(System::Object^  sender, System::EventArgs^  e) {
				 //AddDataTrack
				 try{
					 IPAddress::Parse(textBoxSSMIP->Text);
				 }

				 catch (Exception^){
					 MessageBox::Show("Введите корректный IP");

				 }

				 for each (List<String^>^ elem in _data)
				 {
					 if (elem[0] == textBoxSSMIP->Text){
						 MessageBox::Show("Такой IP уже существует");
						 return;
					 }

				 }

				 List<String^>^ dt = gcnew List<String^>();
				 dt->Add(textBoxSSMIP->Text);
				 dt->Add(textBoxSSMTime->Text);
				 dt->Add(textBoxSSMPortMicrosim->Text);
				 dt->Add(textBoxSSMJaguar->Text);
				 dt->Add(checkDatcTrack->Checked.ToString());
				 _data->Add(dt);

				 this->_setDataList(_data);
			 }
	private: System::Void buttonDTDel_Click(System::Object^  sender, System::EventArgs^  e) {

				 ///DT Del

				 for each (List<String^>^ elem in _data)
				 {
					 if (elem[0] == textBoxSSMIP->Text){
						 _data->Remove(elem);
						 break;
					 }

				 }
				 this->_setDataList(_data);
			 }
	private: System::Void buttonDtSave_Click(System::Object^  sender, System::EventArgs^  e) {
				 ///DT Save

				 try{
					 IPAddress::Parse(textBoxSSMIP->Text);
				 }

				 catch (Exception^){
					 MessageBox::Show("Введите корректный IP");

				 }

				 for each (List<String^>^ elem in _data)
				 {
					 if (elem[0] == textBoxSSMIP->Text){
						 elem[1] =textBoxSSMTime->Text;
						 elem[2] =textBoxSSMPortMicrosim->Text;
						 elem[3] =textBoxSSMJaguar->Text;
						 elem[4] =checkDatcTrack->Checked.ToString();
					 }

				 }



				 this->_setDataList(_data);
			 }
	};
}

