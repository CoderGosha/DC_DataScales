#include "StdAfx.h"
#include "Model.h"
#include "Orcl.h"

using namespace System;
using namespace System::Globalization;

CModel::CModel(String^ portName, int baudRate, Parity parity, int dataBits, StopBits stopBits, Int32 timeRead, bool vesKg, CLogCsv^ log){
	_weight = "Null";
	Weigth_Hour= "";
	vesFixed = false;
	_work = 1;
	error = "";
	_log = log;
	//������ ����� ���� ���������
	_vesKg = vesKg;
	_vesMicrosim = 0;
	typeConnect = "com";
	_port = gcnew CPort(portName, baudRate, parity, dataBits, stopBits, timeRead);
	_connectionJaguar = 0;
	readThread = gcnew Thread(gcnew ThreadStart(this, &CModel::_parsing));
	readThread->Start();
	// readThread->Join();
}

CModel::CModel(String^ ip, String^ port, Int32 timeRead, bool vesKg, CLogCsv^ log, String^ MagicString){
	_weight = "Null";
	Weigth_Hour = "";
	_work = 1;
	typeConnect = "tcp";
	_timeOut = timeRead;
	_moxa = gcnew CMoxaTCP(ip, port, timeRead, log);
	error = "";
	_connectionJaguar = 0;
	_vesKg = vesKg;
	_log = log;
	vesFixed = false;
	this->MagicString = MagicString;
	//readThread = gcnew Thread(gcnew ThreadStart(this, &CModel::_parsingTCP));
	//   readThread->Start();

};


CModel::~CModel(){
	// delete _port;
	_work = 0;
	//readThread->Join();

	if (typeConnect == "com") {
		delete _port;
		readThread->Abort();
		delete readThread;
	}
	else if (typeConnect == "tcp") {
		delete _moxa;
	}

	else if (typeConnect == "jaguar") {
		readThread->Abort();

		delete _jaguar;
		delete readThread;
	}

}


bool CModel::getStatusMoxa(){
	//���������� ������ � �����?!?
	try{

		return _moxa->getStatus();
	}

	catch (Exception ^e){

		return 0;
	}
}

void CModel::_parsing(void){//����� - ������ ��� ��������� ������)
	while (_work){

		if( _port->isOpen()){
			try{

				String^ message = _port->getRawData();

				RawDate = message;

				_log->getRawMoxa(message);
				if (message->Length == 14) {
					array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( message );
					error = "";
					//������ ��� ���������
					//������� ���. 
					_weight = message->Substring(2,7);
					// 10 ������� ������������
					if (temp[9] == 63) _ind_stabil = 0;
					else if (temp[9] == 32) _ind_stabil = 1; 
					else {}; 

					// 11 ������� ����
					if (message[10] == 'B') _ind_tara = 0;
					else {_ind_tara = 1;}; 

					try{         // 11 ������� ����
						String^ temp_str = _weight->Remove(_weight->IndexOf('.'));
						//���� ����� �� ������ ��������� ���������
						if ((message[10] == 'N') && (Int64::Parse(temp_str) == 0) && (_ind_stabil)) _ind_null = 1;
						else {_ind_null = 0;}; 
					}
					catch (System::FormatException ^){_ind_null = 0;}
					catch ( System::ArgumentOutOfRangeException ^ ){_ind_null = 0;}          
					//delete temp;

				}

				//TimeOut
				else if (message->Length == 7) 
				{
					_weight = message;
				}

				else 
				{
					_weight = "WAIT";
					//������ ������
					error = message;

				}
			}
			catch (NullReferenceException ^){
				//Console::WriteLine("������� ���� Error");
				_weight = "NoMicro";
				error =  "NoMicro";
			}

		}//If isOpen
		else {
			_weight = "NoConne" ;

		}

	}//while



};

void CModel::parsingTCP(void){

	try{

		//String^ responseData = _moxa->getRawData();

		//��� ��� ������� ����� ������
		String^ responseData = _moxa->getRawDataBuffer();

		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;

		RawDate = responseData;
		this->CanWriteOracle = true;
		//��������� �� 24092014
		//  Debug::WriteLine("������ �������: " + responseData->Length.ToString());
		if (responseData->Length >= 15)  {
			//array<Byte>^ responseDataHex = Text::Encoding::UTF8->GetBytes( responseData );

			array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
			responseDataHex = BitConverter::ToString(temp)->Replace("-", String::Empty);

			int i = responseDataHex->IndexOf("0D0A", 13 * 2);

			responseDataParse = responseData->Substring(i / 2 - 13, 15);
			responseDataParseHex = responseDataHex->Substring(i - 13 * 2, 30);

			error = "";



			//������ ��� ���������
			//������� ���. 
			_weight = responseDataParse->Substring(2, 7);
			// 10 ������� ������������
			if (responseDataParse[9] == '?') _ind_stabil = 0;
			else if (responseDataParse[9] == ' ') _ind_stabil = 1; 
			else {}; 

			// 11 ������� ����
			if (responseDataParse[10] == 'B') _ind_tara = 0;
			else {_ind_tara = 1;}; 
			// 11 ������� ����������
			if (responseDataParse[10] == 'C') _weight = "Calibr";
			//else {_ind_tara = 1;}; 


			//delete temp;
			///////////******--*-************
			//������ �������
			_moxa->CleanBuffer(i - 1);
			///
			try{//����������� � ���
				// _vesMicrosim

				if (_vesKg)
				{
					String^ s = this->_weight->Replace(" ", String::Empty);
					s = s->Replace(".", ",");
					//_log->Break("DataTrack_Log","���: " + s);
					//Debug::WriteLine(s);
					Double f = Double::Parse(s);
					_vesMicrosim = f;
				}
				else
				{
					//���� ��� � ������ �� �������� �� 1000
					String^ s = this->_weight->Replace(" ",String::Empty);
					s = s->Replace(".", ",");
					//_log->Break("DataTrack_Log","���: " + s);
					//Debug::WriteLine(s);
					Double f = Double::Parse(s);
					f = f * 1000;
					_vesMicrosim = f;
				}
			}
			catch (Exception^ e){
				//Debug::WriteLine(e->Message);
				_log->Break("DataTrack_ErrorConvert","���: " + this->_weight + ":"+ e->Message->ToString());
				if (_weight->IndexOf("Err 20") > 0)
					_vesMicrosim = 0; ///���� Error 0 �� ��� ����� ��� ������ ������� 0

			}

		}

		//TimeOut
		else if (responseDataParse->Length == 7) 
		{
			_weight = responseDataParse;
		}

		else 
		{
			// _weight = "NoMicro";
			//  error = responseDataParse;
			//������ ������
			this->CanWriteOracle = false;

		}
	}
	catch (Exception ^){
		//Console::WriteLine("������� ���� Error");
		_weight = "NoMicro";
		this->CanWriteOracle = false;
	}


	if (_moxa->getStatus()){

	}
	else {
		_weight = "NoConne";
		this->CanWriteOracle = false;
	}


}


void CModel::parsingTCP_WE2120_ST(void){

	try{

		this->CanWriteOracle = false;
		String^ responseData = _moxa->getRawData();
		// _log->getRawMoxa(responseData);
		//55532C204D2C334D2C2020203131383020206B670D0A
		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;

		array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
		responseDataHex = BitConverter::ToString(temp)->Replace("-", String::Empty);
		_log->getRawMoxa(responseDataHex);

		int i = responseDataHex->IndexOf("0D0A", 18 * 2);


		responseDataParse = responseData->Substring(i / 2 - 20, 20);

		if (responseDataParse->IndexOf("ST") != -1) {
			//C - ������������
			this->_ind_stabil = 1;
		}
		else {
			this->_ind_stabil = 0;
		}

		/*int i = responseData->IndexOf("US");*/
		//responseDataParse = ;

		String^ tmp  = responseDataParse->Substring(9, 7);
		tmp = tmp->Replace(" ", "");
		_weight =  tmp;

		//������� ��� ���
		try{
			_vesMicrosim = Int32::Parse(_weight);
		}
		catch (Exception ^ee){

		}

		RawDate = responseData;
		this->CanWriteOracle = true;
		if (_moxa->getStatus()){

		}
		else {
			_weight = "NoConne";

		}
	}

	catch (Exception ^ee) {
		_weight = "";
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->Message->ToString());
	}


}

void CModel::parsingTCP_WE2120_ALT(void){

	try{
		this->CanWriteOracle = false;

		String^ responseData = _moxa->getRawData();
		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;

		array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
		responseDataHex = BitConverter::ToString(temp);
		_log->getRawMoxa(responseDataHex);

		int i_Begin_H = responseDataHex->IndexOf("02");
		int i_End_H = responseDataHex->IndexOf("03", i_Begin_H + 1);
		int i_len_H = i_End_H - i_Begin_H;

		responseDataParseHex = responseDataHex->Substring(i_Begin_H,i_End_H - i_Begin_H);
		responseDataParseHex = responseDataParseHex->Replace("-", String::Empty);
		int i_Begin= 0;
		int i_End = 0;

		i_Begin = i_Begin_H / 3;
		i_len_H = responseDataParseHex->Length;

		responseDataParse =  responseData->Substring(i_Begin + 1, i_len_H / 2 - 1);

		if ((responseDataParse[8] == 'M') || (responseDataParse[8] == 'E')) {
			//�������
			this->_ind_stabil = 0;
		}
		else {
			this->_ind_stabil = 1;
		}
		String^ tmp  = responseDataParse->Substring(0, 8);
		tmp = tmp->Replace(" ", String::Empty);
		_weight =  tmp;

		//������� ��� ���
		try{
			_vesMicrosim = Int32::Parse(_weight);
		}
		catch (Exception ^ee){

		}

		RawDate = responseData;
		this->CanWriteOracle = true;

		if (_moxa->getStatus()){

		}
		else {
			_weight = "NoConne";

		}
	}

	catch (Exception ^ee) {
		_weight = "";
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->Message->ToString());
	}


}

void CModel::parsingTCP_DEFAULT(String^ Begin, String^ End){

	try{

		String^ responseData = _moxa->getRawData();
		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;

		array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
		responseDataHex = BitConverter::ToString(temp)->Replace("-", String::Empty);
		_log->getRawMoxa(responseDataHex);



		_weight = responseData;
		RawDate = responseData;


	}

	catch (Exception ^ee) {

		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->Message->ToString());
	}

}


void CModel::parsingTCP_INECONT_OPUS(){

	try{
		this->CanWriteOracle = false;
		String^ responseData = _moxa->getRawData();
		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;

		RawDate = responseData;

		array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
		responseDataHex = BitConverter::ToString(temp);
		_log->getRawMoxa(responseDataHex);

		int i_Begin_H = responseDataHex->IndexOf("23");
		int i_End_H = responseDataHex->IndexOf("23", i_Begin_H + 1);
		int i_len_H = i_End_H - i_Begin_H;

		if (i_Begin_H == -1)
			return;

		if (i_End_H == -1)
			return;

		responseDataParseHex = responseDataHex->Substring(i_Begin_H,i_End_H - i_Begin_H);
		responseDataParseHex = responseDataParseHex->Replace("-", String::Empty);
		int i_Begin= 0;
		int i_End = 0;

		i_Begin = i_Begin_H / 3;
		i_len_H = responseDataParseHex->Length;

		responseDataParse =  responseData->Substring(i_Begin + 1, i_len_H / 2 - 1);

		String^ tmp = responseDataParse;
		tmp = tmp->Replace(" ", String::Empty);

		_weight = tmp;

		this->CanWriteOracle = true;

		this->_ind_stabil = 1;
		if (_moxa->getStatus()){

		}
		else {
			_weight = "NoConne";

		}
	}


	catch (Exception ^ee) {
		// 
		if ( _weight == "Null")
			if ((RawDate->Length > 0) && (RawDate != "NoConne"))
				_weight = "KeepAlive";
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->Message->ToString());
		_weight = "ErrorModel";
	}

}

void CModel::parsingTCP_DISOMAT_SATUS(){

	try{

		//�������� ������������������ ����:
		// byte[] data = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x22, 0x01, 0x55, 0x62, 0x00, 0x04, 0x01, 0x72, 0x70, 0x74, 0x6f, 0x20, 0x6c, 0x23, 0x42, 0x23, 0x34, 0x36, 0x23, 0x31, 0x23, 0x34, 0x30, 0x23, 0x46, 0x46, 0x23, 0x31, 0x23, 0x36, 0x31, 0x21, 0x23, 0xab, 0xaf };
		//array<Byte>^ sendData = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x22, 0x01, 0x55, 0x62, 0x00, 0x04, 0x01, 0x72, 0x70, 0x74, 0x6f, 0x20, 0x6c, 0x23, 0x42, 0x23, 0x34, 0x36, 0x23, 0x31, 0x23, 0x34, 0x30, 0x23, 0x46, 0x46, 0x23, 0x31, 0x23, 0x36, 0x31, 0x21, 0x23, 0xab, 0xaf };
		array<Byte>^ sendData =  gcnew array<Byte>(1);

		if (this->MagicString->Length > 0) {
			array<String^>^ sT = this->MagicString->Split(',');

			sendData = gcnew array<Byte>(sT->Length);

			for (int i = 0 ; i < sT->Length; i++){


				//Byte::Parse("/0x00");

				sendData[i] = Byte::Parse(sT[i], System::Globalization::NumberStyles::HexNumber);
			}
		}
		this->CanWriteOracle = false;
		String^ responseData = _moxa->getRawData_SendByte(sendData);
		String^ responseDataHex;
		String^ responseDataParse;
		String^ responseDataParseHex;


		array<Byte>^ temp = Text::Encoding::UTF8->GetBytes( responseData );
		responseDataHex = BitConverter::ToString(temp);
		_log->getRawMoxa(responseDataHex);

		///23-36-31-23- ������� ����
		int i_Begin_H = responseDataHex->IndexOf("23-36-31-23");
		int i_End_H = -1; //�������� �� ���������
		//int i_len_H = i_End_H - i_Begin_H;

		if (i_Begin_H == -1)
			return;
		else {
			i_End_H = responseDataHex->IndexOf("23", i_Begin_H + 10);
		}

		if (i_End_H == -1)
			return;

		responseDataParseHex = responseDataHex->Substring(i_Begin_H, i_End_H - i_Begin_H);

		responseDataParseHex = responseDataParseHex->Replace("-", String::Empty);
		int i_Begin= 0;
		//int i_End = 0;

		i_Begin = i_Begin_H / 3;
		int i_len_H = responseDataParseHex->Length; 

		//if (responseDataParseHex->Length > 0) 
		//	return;

		responseDataParse =  responseData->Substring(i_Begin + 4, i_len_H / 2 - 4);

		RawDate = responseData;





		///��������� ���������� ���, ������� ������������������

		/* if ((responseDataHex->IndexOf("01-56-61-00") > 0) || (responseDataHex->IndexOf("01-56-5F-00") > 0)){*/
		if (responseDataHex->IndexOf("00-6C-23") > 0){

			//���������� ���
			this->_ind_stabil = 1;
		}
		else  {
			this->_ind_stabil = 0;
		}
		String^ tmp = responseDataParse;

		try {
			String^ tmp2 =  responseDataParse->Replace(".", ",");
			Double d = Double::Parse(tmp2);
			d = Math::Round(d, 0);
			tmp = d.ToString();
			tmp = tmp->Replace( ",", ".");
		}

		catch (Exception ^e) {

		}



		_weight = tmp;

		this->CanWriteOracle = true;


		//������� ��� ���
		try{
			_vesMicrosim = Int32::Parse(_weight);
		}
		catch (Exception ^ee){

		}


		if (_moxa->getStatus()){

		}
		else {
			_weight = "NoConne";
			this->CanWriteOracle = false;
		}
	}


	catch (Exception ^ee) {
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->ToString());
		_weight = "ErrorModel";
	}

}

void CModel::parsingTCP_DATASCALES_REPEATER(void){

	try{

		this->CanWriteOracle = false;
		String^ responseData = _moxa->getRawData();

		if (responseData == "Hello") {
			RawDate = responseData;
			return;
		}
		//�������� � ���� � �������������� �� ���������..
		int wB = responseData->IndexOf("VES=") + 4;
		int wEnd = responseData->IndexOf(";;;", wB);
		_weight = responseData->Substring(wB, wEnd - wB);
		_weight = _weight->Replace(",", ".");

		wB = responseData->IndexOf("STABIL=") + 7;
		wEnd = responseData->IndexOf(";;;", wB);
		String^ Stab = responseData->Substring(wB, wEnd - wB);;

		if (Stab == "1") {
			//C - ������������
			this->_ind_stabil = 1;
		}
		else {
			this->_ind_stabil = 0;
		}



		//������� ��� ���
		try{
			String^ s = _weight->Replace(".", ",");
			Double t_weight = Double::Parse(s);
			if (!_vesKg)
				t_weight = t_weight * 1000;
			_vesMicrosim = t_weight;
		}
		catch (Exception ^ee){
			_log->Break("������ �������������� ���� ��� ���", _weight + ":" + ee->ToString());
		}

		RawDate = responseData;
		this->CanWriteOracle = true;


		try {
			//�������� �� ������������� ���
			wB = responseData->IndexOf("FIX=") + 4;
			wEnd = responseData->IndexOf(";;;", wB);
			String^ Fix = responseData->Substring(wB, wEnd - wB);;

			wB = responseData->IndexOf("DATETIME=") + 9;
			wEnd = responseData->IndexOf(";;;", wB);
			String^ FixTime = responseData->Substring(wB, wEnd - wB);;

			if (Fix == "1") {
				//������ ������������� ���.
				//this->CanWriteOracle = false;
				vesFixed = true;
				vesFixedTime = FixTime;

			}
			else {
				vesFixed = false;
			}
		}

		catch (Exception^ exee) {}


		if (_moxa->getStatus()){

		}
		else {
			_weight = "NoConne";

		}
	}

	catch (Exception ^ee) {
		_weight = "";
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->Message->ToString());
	}


}


void CModel::parsingTCP_DATASCALES_DLL(String^ modelDll){
	//��� DLL ���������� ������ ����...
	try{

		this->CanWriteOracle = false;
		//���������� ������� ������ � �������� ������...
		bool sendByte = DataScalesModel::Model::GetSendByteScales(modelDll);

		String^ responseData = "";
		if (sendByte) {
			array<Byte>^ sendByte = DataScalesModel::Model::GetStringForSendScales(modelDll);
			responseData = _moxa->getRawDataBuffer_SendByte(sendByte);
		}
		else 
			responseData = _moxa->getRawDataBuffer();
		/*
		String^ str = _mdl->getWeight();
		this->_RawData = _mdl->RawDate;
		this->_Weigth_Hour = _mdl->Weigth_Hour;
		this->weight = str;
		this->ind_null = _mdl->getInd_null();
		this->ind_stabil = _mdl->getInd_stabil();
		this->ind_tara = _mdl->getInd_tara();
		*/
		DataScalesModel::ReturnClass^ retModel = DataScalesModel::Model::RunModel(modelDll, responseData);

		if (retModel->GoodData) 
		{//������ ����������� �����
			this->RawDate = responseData;
			this->Weigth_Hour = DateTime::Now.ToString();
			this->_weight = retModel->weightS;
			this->_ind_null = false;
			this->_ind_stabil = retModel->stabil;
			this->_ind_tara = false;
			this->CanWriteOracle = true;
			_moxa->CleanBuffer(retModel->countClean);


			try{//����������� � ���
				// _vesMicrosim

				if (_vesKg)
				{
					String^ s = this->_weight->Replace(" ", String::Empty);
					s = s->Replace(".", ",");
					//_log->Break("DataTrack_Log","���: " + s);
					//Debug::WriteLine(s);
					Double f = Double::Parse(s);
					_vesMicrosim = f;
				}
				else
				{
					//���� ��� � ������ �� �������� �� 1000
					String^ s = this->_weight->Replace(" ",String::Empty);
					s = s->Replace(".", ",");
					//_log->Break("DataTrack_Log","���: " + s);
					//Debug::WriteLine(s);
					Double f = Double::Parse(s);
					f = f * 1000;
					_vesMicrosim = f;
				}
			}
			catch (Exception^ e){
				//Debug::WriteLine(e->Message);
				_log->Break("DataTrack_ErrorConvert","���: " + this->_weight + ":"+ e->Message->ToString());
				if (_weight->IndexOf("Err 20") > 0)
					_vesMicrosim = 0; ///���� Error 0 �� ��� ����� ��� ������ ������� 0

			}
		}


	}

	catch (Exception ^ee) {
		_weight = "";
		this->_ind_stabil = 0;
		_log->Break("ErrorModel", ee->ToString());
	}


}
void CModel::_parsingJaguar(){
	//��������� ������� �������� ��� ������
	_ind_null = 0;
	_ind_tara = 0;
	_ind_stabil = 0;
	_weight = "0";
	while (_work){


		bool con = _jaguar->getConnect();
		if (con) {
			String^ raw = _jaguar->getRawData();
			RawDate = raw;
			try {
				int Begin = raw->IndexOf("Ves=") + 4;
				int End = raw->IndexOf("Pocket=");
				String^ ves = raw->Substring(Begin, End - Begin);
				_weight = ves ;
				_ind_stabil = 1;
				_connectionJaguar = 1;

				RawDate = raw;
				try{//����������� � ���
					// 

					if (_vesKg)
					{
						String^ s = _weight;
						s = s->Replace(".", ",");
						Debug::WriteLine(s);
						Double f = Double::Parse(s);
						_vesMicrosim = f;
					}
					else
					{
						//���� ��� � ������ �� �������� �� 1000
						String^ s = _weight;//->Replace(" ","");
						s = s->Replace(".", ",");
						Debug::WriteLine(s);
						Double f = Double::Parse(s);
						f = f * 1000;
						_vesMicrosim = f;
					}
				}
				catch (Exception^){

				}

			}

			catch (Exception^) {
				//_weight = "0";
				_ind_stabil = 1;
				_connectionJaguar = 1;
			}


		}
		else {
			_ind_stabil = 0;
			//_weight = "NoConne";
			_connectionJaguar = 0;

		}

		Thread::Sleep(300);
	}

}


//�������� ����������� ������� �����
void CModel::command(String^ cmd)
{
	//��������� ��� �������� RealCom/Port
	if (typeConnect == "com")
		_port->command(cmd);
	else if (typeConnect == "tcp")
	{
		_moxa->command(cmd);	
	}


}


