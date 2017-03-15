#include "StdAfx.h"
#include "Weight.h"

CWeight::CWeight(String^ prtName, int bdRate, Parity prty, int dtBits, StopBits stpBits, Int32 tmRead, String^ name_weight, String^ locat, List<String^>^ oraclList, List<bool>^ buttonControl, int nomerSSM, bool vesKg, bool sendRawData, String^ _ipSSM)
{

	//Создадим буффер для записи в оракл
	buf_Oracle = gcnew List<List<String^>^>();

	_jaguar = nullptr;   

	_log = gcnew CLogCsv("log_" + name_weight);
	_mdl = gcnew CModel(prtName, bdRate, prty, dtBits, stpBits, tmRead, vesKg, _log);
	name = name_weight;
	this->ind_null = 0;
	this->ind_stabil = 0;
	this->ind_tara = 0;
	this->connect = 0;
	this->oracleConnect = 0;
	this->location = locat;

	this->_nomerSSM = nomerSSM;
	this->portName =  prtName;
	this->baudRate = bdRate;
	this->parity = prty;
	this->dataBits = dtBits;
	this->stopBits = stpBits;
	this->timeRead = tmRead;
	this->buttonControl = buttonControl;
	_counterVes = 0;
	_oldVes = "";
	this->_sendRawDate = sendRawData;
	_vesKg = vesKg;

	//
	String^ host = System::Net::Dns::GetHostName();
	_currentIP = System::Net::Dns::GetHostByName(host)->AddressList[0]->ToString();
	_typeScales = "Microsim/RealCom";


	String^ ConnectionString ="Data Source="+ oraclList[0] +";User ID="+ oraclList[1] +";Password="+ oraclList[2] +"";
	try{
		orcl = gcnew COrcl(ConnectionString, oraclList[3], _log);
	}
	catch (Exception ^e){


	}

	DataTrackIP = _ipSSM;

	_work = 1;

	if (bool::Parse(oraclList[4]))
		_sendOracle = 1;
	else 
		_sendOracle = 0;

	OracleThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::OracleSend));
	OracleThread->Start();		
	resultMes = 0;

	readThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::Worker));
	readThread->Start();
}



CWeight::CWeight(System::String ^tScales, System::String ^ip, System::String ^port, int tmRead, System::String ^name_weight, System::String ^locat, System::Collections::Generic::List<String^> ^oraclList,  System::Collections::Generic::List<bool> ^buttonControl, int nomerSSM, bool vesKg, bool sendRawData, String^ _ipSSM, String^ MagicString, String^ ModelDll)
{//Конструктор для подключения к TCP IP

	//Создадим буффер для записи в оракл
	buf_Oracle = gcnew List<List<String^>^>();

	_jaguar = nullptr;
	_log = gcnew CLogCsv("log_" + name_weight);
	_mdl = gcnew CModel(ip, port, tmRead, vesKg, _log, MagicString);
	name = name_weight;
	this->ind_null = 0;
	this->ind_stabil = 0;
	this->ind_tara = 0;
	this->connect = 0;
	this->oracleConnect = 0;
	this->location = locat;
	_vesKg = vesKg;
	_counterVes = 0;
	_oldVes = "";
	this->_sendRawDate = sendRawData;
	this->_nomerSSM = nomerSSM;
	this->timeRead = tmRead;
	this->buttonControl = buttonControl;
	this->MagicString = MagicString;
	//
	_currentIP = ip;
	_typeScales = tScales;

	DataTrackIP = _ipSSM;

	if (ModelDll == nullptr)
		this->_ModelDll = "-";
	else 
		this->_ModelDll = ModelDll;

	String^ ConnectionString ="Data Source="+ oraclList[0] +";User ID="+ oraclList[1] +";Password="+ oraclList[2] +"";
	try{
		orcl = gcnew COrcl(ConnectionString, oraclList[3], _log);
	}
	catch (Exception ^e){


	}



	_work = 1;
	resultMes = 0;

	if (bool::Parse(oraclList[4]))
		_sendOracle = 1;
	else 
		_sendOracle = 0;

	OracleThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::OracleSend));
	OracleThread->Start();


	readThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::Worker));
	readThread->Start();

}



CWeight::CWeight(System::String ^ip, System::String ^port, int tmRead, System::String ^name_weight, System::String ^locat, System::Collections::Generic::List<String^> ^oraclList, int nomerSSM, bool vesKg, String^ _ipSSM, Int32 _portJaguarSSM, List<int>^  _weightJaguar, bool sendRawData)
{//Конструктор для подключения к TCP IP к ЯГуарам
	//Создадим буффер для записи в оракл
	buf_Oracle = gcnew List<List<String^>^>();

	_mdl = nullptr;
	_jaguar = nullptr;
	_log = gcnew CLogCsv("log_" + name_weight);
	name = name_weight;
	this->ind_null = 0;
	this->ind_stabil = 0;
	this->ind_tara = 0;
	this->connect = 0;
	this->oracleConnect = 0;
	this->location = locat;
	this->timeRead = tmRead;
	_counterVes = 0;
	_oldVes = "";
	_vesKg = vesKg;
	this->_sendRawDate = sendRawData;

	//отключим кнопки управления
	List<bool>^ _buttonControl =gcnew  List<bool>();
	_buttonControl->Add(0);
	_buttonControl->Add(0);
	_buttonControl->Add(0);
	_buttonControl->Add(0);
	this->buttonControl = _buttonControl;

	this->_nomerSSM = nomerSSM;
	//
	_typeScales = "Jaguar/TCPIP";

	String^ ConnectionString ="Data Source="+ oraclList[0] +";User ID="+ oraclList[1] +";Password="+ oraclList[2] +"";
	try{
		orcl = gcnew COrcl(ConnectionString, oraclList[3], _log);
	}
	catch (Exception ^e){


	}


	DataTrackIP = _ipSSM;

	_work = 1;
	resultMes = 0;
	///OracleThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::OracleSend));
	// OracleThread->Start();

	if (bool::Parse(oraclList[4]))
		_sendOracle = 1;
	else 
		_sendOracle = 0;

	//Создаем подключение к Ягуару 
	_jaguar = gcnew CJaguar(ip, Int32::Parse(port), tmRead, _log, name, location,nomerSSM, orcl, _ipSSM, _portJaguarSSM, _weightJaguar);

	// оракл не посылаем отсюда
	readThread = gcnew Thread(gcnew ThreadStart(this, &CWeight::WorkerJaguar));
	readThread->Start();

	_currentIP = _jaguar->getCurrentIp();

}




void CWeight::Show(void){
	delete _FormOut;
	_FormOut = gcnew Tablitsa::Form1(_mdl, _log, name, location, buttonControl, _vesKg);
	_FormOut->Show();


}

CWeight::~CWeight(){
	_log->Break(name, "Штатное завершение");
	delete _log;
	delete _mdl;
	delete orcl;

	delete _jaguar;
	_work = 0;
	_sendOracle = 0;
	delete OracleThread;

	readThread->Abort();
	delete readThread;
}


void CWeight::cmd(String^ cmd){
	_mdl->command(cmd);
}




void CWeight::Worker(){
	while ( _work )
	{
		Thread::Sleep(timeRead);
		bool CanWriteOracle = true;
		if (_typeScales == "Microsim/TCPIP") {
			//Для моксы не используем поток, а вызываем функцию
			_mdl->parsingTCP();
			CanWriteOracle = _mdl->CanWriteOracle;

		}
		else if (_typeScales == "WE2120_ST/TCPIP") {
			_mdl->parsingTCP_WE2120_ST();
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;
		}

		else if (_typeScales == "WE2120_ALT/TCPIP") {
			_mdl->parsingTCP_WE2120_ALT();
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;
		}

		else if (_typeScales == "DEFAULT/TCPIP") {
			_mdl->parsingTCP_DEFAULT("", "");
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = false;
		}

		else if (_typeScales == "INTECONT_OPUS_ST/TCPIP") {
			_mdl->parsingTCP_INECONT_OPUS();
			//Узнаем есть ли что для Oracle?????
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;

		}

		else if (_typeScales == "DISOMAT_SATUS/TCPIP") {
			_mdl->parsingTCP_DISOMAT_SATUS();
			//Узнаем есть ли что для Oracle?????
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;

		}
		else if (_typeScales == "DATASCALES_REPEATER") {
			_mdl->parsingTCP_DATASCALES_REPEATER();
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;
		}

		else if (_typeScales == "DATASCALES_DLL") {
			_mdl->parsingTCP_DATASCALES_DLL(_ModelDll);
			this->connect = _mdl->getStatusMoxa();
			CanWriteOracle = _mdl->CanWriteOracle;
		}


		String^ str = _mdl->getWeight();
		this->_RawData = _mdl->RawDate;
		this->_Weigth_Hour = _mdl->Weigth_Hour;
		this->weight = str;
		this->ind_null = _mdl->getInd_null();
		this->ind_stabil = _mdl->getInd_stabil();
		this->ind_tara = _mdl->getInd_tara();

		if (_typeScales == "Microsim/TCPIP") {
			if (str == "TimeOut") { this->connect = 0; }
			else if (str == "NoConne") { this->connect = 0; }
			else if (str == "Error") { this->connect = 0; }
			else if (str == "Null") { this->connect = 0; }
			else if (str == "NoMicro") { this->connect = 0; }

			else 
			{	this->connect = 1;


			}
		}

		if ((_typeScales != "Microsim/RealCom") && (_typeScales != "WE2120_ST/TCPIP")  && (_typeScales != "WE2120_ALT/TCPIP")) {
			try {

				//float::Parse(this->weight); //если вес конвертиться то посылаем 20092014
				String^ s = this->weight;//->Replace(" ","");
				s = s->Replace(".", ",");
				s = s->Replace(" ", "");

				Double f = Double::Parse(s);

				//Если не конвертится то точно не стабильный
				this->ind_stabil = _mdl->getInd_stabil();
			}
			catch (Exception^ e1){
				ind_stabil = 0;
			}	

		}


		//if (this->_sendOracle = 1) 
		//	this->sendOracle();

		if (_typeScales == "Jaguar/TCPIP") 
		{
			this->connect = _mdl->getStatusConnectJaguar();
		}
		//Проверяем старый вес и увеличиваем счетчик для ССМ
		if (_oldVes != str) {
			_oldVes = str;
			_log->Weigth(this->name, str, this->ind_stabil);
			_counterVes++;
		}

		//if (_typeScales == "INTECONT_OPUS_ST/TCPIP") 
		//{//Используем отдельную логику для конвеерных весов
		//

		//Используем новую логику для всех весов
		if (CanWriteOracle) {

			//Добавляем в буффер для отправки в Oracle
			List<String^>^ buff = gcnew List<String^>();
			buff->Add(weight); //Вес
			buff->Add(this->ind_tara.ToString()); //Тара
			buff->Add(this->ind_stabil.ToString()); //Стабильность
			buff->Add(this->ind_null.ToString()); //Ноль
			buff->Add(_mdl->getFix().ToString()); //Фиксирование
			buff->Add(_mdl->getFixTime()); //Фиксирования время

			buf_Oracle->Add(buff);
		}
		//}
		//else 
		//{

		//	//Добавляем в буффер для отправки в Oracle
		//List<String^>^ buff = gcnew List<String^>();
		//buff->Add(weight); //Вес
		//buff->Add(this->ind_tara.ToString()); //Тара
		//buff->Add(this->ind_stabil.ToString()); //Стабильность
		//buff->Add(this->ind_null.ToString()); //Ноль

		//buf_Oracle->Add(buff);

		//}


	}

}
void CWeight::WorkerJaguar(){
	//в переменную weigth = записать дату последней посылки  

	while ( _work )
	{
		try{
			this->weight = _jaguar->getRawData();
			this->ind_null = 0;
			this->ind_stabil = 0;
			this->ind_tara = 0;
			this->oracleConnect = _jaguar->oracleConnect;
			Thread::Sleep(200);	
			this->connect = _jaguar->getConnect();

			//20092014
			// this->sendOracle();
		}
		catch (Exception^){
			Thread::Sleep(2000);

		}



	}

}
void CWeight::Stop(void){

	this->_sendOracle = 0;
};

void CWeight::Start(void){

	this->_sendOracle = 1;
}


void CWeight::OracleSend(void){
	while (_sendOracle)
	{
		if (buf_Oracle->Count > 0) {
			//Если есть послыать то работаем
			_log->sendOracle("Буффер для чтения равен: " + buf_Oracle->Count.ToString());

			//Забираем первое занчение из буфера
			List<String^>^ buff;

			buff = buf_Oracle[0];


			String^ weightTMP = buff[0];
			String^ taraTMP = buff[1];
			String^ stabilTMP = buff[2];
			String^ nullTMP = buff[3];
			String^ FixedTmp = buff[4];
			String^ FixedTimeTmp = buff[5];
			//Тут вшпиливаем код для отправки фиксированного веса...
			bool BFixedTmp = false;
			if (bool::TryParse(FixedTmp, BFixedTmp) && BFixedTmp) {
				try{
					String^ tmp = "";	
					if (_sendRawDate) 
						tmp = _RawData;

					resultMes = orcl->sendDataFixWeight(name, location, bool::Parse(taraTMP), bool::Parse(stabilTMP), bool::Parse(nullTMP), _vesKg, !_vesKg, weightTMP, _currentIP, _Weigth_Hour, tmp, FixedTmp, FixedTimeTmp);
					this->oracleConnect = resultMes;
				}

				catch (Exception^ e) {
					_log->Break(name, "Обрыв соединения с Oracle: " + e);
				}
			}

			else {

				try{
					String^ tmp = "";	
					if (_sendRawDate) 
						tmp = _RawData;

					resultMes = orcl->sendData(name, location, bool::Parse(taraTMP), bool::Parse(stabilTMP), bool::Parse(nullTMP), _vesKg, !_vesKg, weightTMP, _currentIP, _Weigth_Hour, tmp);
					this->oracleConnect = resultMes;
				}

				catch (Exception^ e) {
					_log->Break(name, "Обрыв соединения с Oracle: " + e);
				}

			}

			SetStatusUiOracle(resultMes); //TODO

			buf_Oracle->RemoveAt(0);
			Thread::Sleep(50);
		}

		else {
			//ожидаем время
			_log->sendOracle("Буффер для чтения равен: " + buf_Oracle->Count.ToString());
			Thread::Sleep(200);
		}




	}

};


void CWeight::SetStatusUiOracle(bool result){

	if ((result) && (_FormOut))
	{
		_FormOut->SetPicMes(System::Drawing::Color::Green);
	}
	else if ((_FormOut) && (resultMes == 0))
	{
		String^ error = orcl->error;
		_log->Break(name, "Обрыв соединения с Oracle: " + error);
		_FormOut->SetPicMes(System::Drawing::Color::Red);
	}
	else if (resultMes == 0)
	{		
		String^ error = orcl->error;
		_log->Break(name, "Обрыв соединения с Oracle: " + error);

	}


};

String^ CWeight::getTypeScales(){
	if (_typeScales == "DATASCALES_DLL")
		return "DS_DLL" + "/" + _ModelDll;
	else 
		return _typeScales;
};


String^ CWeight::getErrorOracle(){
	if (_sendOracle)
	{
		String^ error = orcl->error;
		if (error != "0") {
			_log->Break(name, error);
			orcl->error = "0";
		}
		return error;
	}
	else 
	{
		return "ORACLE OFFLINE";
	}
}


