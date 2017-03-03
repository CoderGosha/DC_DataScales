#include "StdAfx.h"
#include "Jaguar.h"

CJaguar::CJaguar(String^ ip, Int32 port, Int32 timeRead, CLogCsv^ log, String^ nom, String^ name, Int32 positionSSM, COrcl^ orcl, String^ _ipSSM, Int32 _portJaguarSSM, List<int>^ weightJaguar):
_port(port),
_timeRead(timeRead)
{
	_weightJaguar = weightJaguar;
	this->nom = nom;
	this->name = name;
	_positionSSM = positionSSM;
	_orcl = orcl;
	_log = log;
	ves = "0";
	 this->_ipSSM = _ipSSM;
	 
	 this->_portJaguarSSM = _portJaguarSSM;

	 this->_dnsOrIp = ip;


	getIpFromDns();
///CCV

	ts = new ConnectSSM(_ipSSM, _portJaguarSSM);
	statusJaguar = ts->status;
		ts->msg.ves1 = 0;
		ts->msg.ves2 = 0;
		ts->msg.ves3 = 0;
		ts->msg.nomer1 = 0;
		ts->msg.nomer2 = 0;
		ts->msg.nomer3 = 0;
//
		//Выделяем память для buffer записи веса в базу  List<List<String^>^>^ _weightBuffer;

	_weightBuffer = gcnew List<List<String^>^>();

	//запускаем поток коннекта
	checkConnect = 1;
	_connecting = 0;
	_reading = 0;
	oracleConnect = 0;
	_counterSend = 0;
	_rawData = "null";
	checkThread = gcnew Thread(gcnew ThreadStart(this, &CJaguar::_checkConnect));
	checkThread->Start();

	sendThread = gcnew Thread(gcnew ThreadStart(this, &CJaguar::_sendOracle));
	sendThread->Start();

	readThread = nullptr;
}

void CJaguar::_sendOracle(void){
	while (true) {
		
		if (_weightBuffer->Count > 0) {
			List<String^>^ tmp = _weightBuffer[0];
			_weightBuffer->RemoveAt(0);

			//Тут мы что то посылаем
			try {
					bool resultMes = 0;
					resultMes = _orcl->_sendData(tmp[0], tmp[1], 0, 1, 0, 1, 0, tmp[2], tmp[3], "", ""); 
					this->oracleConnect = resultMes;
					
					//пишем в лог 
					_log->Weigth(this->nom, ves, 1);
				}
				catch (Exception^){
					String^ error = _orcl->error;
					_log->Break(name, "Обрыв соединения с Oracle: " + error);
		}

		}

		Thread::Sleep(100);
	}

};

void CJaguar::getIpFromDns(){
//Определим IP адрес
	try {
		IPAddress::Parse(_dnsOrIp);
		_ip = _dnsOrIp;
	}

	catch (FormatException^ e) {
		//Похоже это DNS имя
		//определим ip по dns
		array<IPAddress^>^ ips;
		try 
		{
			ips = Dns::GetHostAddresses(_dnsOrIp);
			for each ( IPAddress^ ipOne in ips )
			{	
				_ip = ipOne->ToString(); 
			}

		}
		catch (SocketException^ e){
		//не найден по DNS
			throw gcnew SocketException();
		}
	}//Catch
 }

CJaguar::~CJaguar(){
	try {
		checkConnect = 0;
		checkThread->Abort();
		//checkThread->Join();
		delete checkThread;
		
		sendThread->Abort();
		delete sendThread;

		_reading = 0;
		//readThread->Join();
		readThread->Abort();
		delete readThread;
	

		_client->Close();
		delete _client;
	}

	catch (Exception^) {
	}

}

void CJaguar::_checkConnect(){
	//Работаем на коннект
	while (checkConnect) {
		if (_connecting) {
			
		}
		else {//если нет подключения

			//_connecting = 1; //подключаемся
			_Reconnect();
		}

		Thread::Sleep(5000);
	}//while


}

void CJaguar::_Reconnect(){
	try {
		if (readThread != nullptr) {
			_reading = 0;
			readThread->Join();
			delete readThread; 

			_client->Close();
			delete _client;
		}
	}
	
	catch (Exception^ ){

	}
	//переподключение 

	String^ end = "\r\n\0";
	try{
		_log->Break(name, "Reconnect");

		_client = gcnew TcpClient(_ip , _port);
		String^ Body = "Hello=DataCenter";
		Body = Body->PadRight(61) + end;
		array<Byte>^data;
		data = gcnew array<Byte>(64);
		data = System::Text::Encoding::ASCII->GetBytes(Body );
		stream = _client->GetStream();
		stream->WriteTimeout = 80000;
		stream->ReadTimeout = 80000;
		stream->Write( data, 0, data->Length);
		
		_connecting = 1;
			//самое время запустить поток для чтения
		_reading = 1;
		readThread = gcnew Thread(gcnew ThreadStart(this, &CJaguar::_readData));
		readThread->Start();
	}
	catch (Exception^ e){
		_connecting = 0; //так запускаем переконнект
	}

};

void CJaguar::_readData(){
	array<Byte>^data;
	while (_reading) {
		//Thread::Sleep(_timeRead);
		try {
			data = gcnew array<Byte>(64);
			String^ responseData = String::Empty;
			Int32 bytes = stream->Read( data, 0, data->Length );
			responseData = System::Text::Encoding::ASCII->GetString( data, 0, bytes );
			//_rawData = responseData;
			
			//Пришел вес самое время его распарсить
			//Определим текущую дату

			try{
				int Begin = responseData->IndexOf("Ves=") + 4;
				int End = responseData->IndexOf("Pocket=");
				ves = responseData->Substring(Begin, End - Begin);
				_rawData = ves + " : "  + DateTime::Now + " : " + responseData;;
				//_rawData = 
				//спарсенный вес посылаем в ССМ 
				_log->Weigth(name, _rawData, 1);

				List<String^>^ tmp = gcnew List<String^>();
				tmp->Add(nom);
				tmp->Add(name);
				tmp->Add(ves);
				tmp->Add(_ip);
				_weightBuffer->Add(tmp);
				//посылаем в оракл
				//bool _sendData(String^ nom, String^ name, Int32 tara, Int32 stabil, Int32 zero, Int32 kg, Int32 tonn, String^ ves, String^ ip);
				//try{
				//	bool resultMes = 0;
				//	resultMes = _orcl->_sendData(nom, name, 0, 1, 0, 1, 0, ves, _ip); 
				//	this->oracleConnect = resultMes;
				//	
				//	//пишем в лог 
				//	_log->Weigth(this->nom, ves, 1);
				//}
				//catch (Exception^){
				//	String^ error = _orcl->error;
				//	_log->Break(name, "Обрыв соединения с Oracle: " + error);
				//}

				this->_sendSSM();

			}
			catch (ArgumentOutOfRangeException ^e2) {
				
				Thread::Sleep(_timeRead);
				
				
				//Тут проверим на KeepALive
				int Begin = responseData->IndexOf("KeepAlive=");
				if (Begin == -1) {
					_log->Break(name, "ERROR -> NEED RECONNECT : " + responseData);
					//Переподключение
					_reading = 0;
				    _connecting = 0;
				}

				else {
					_log->Break(name, "KeepAlive : " + responseData);
				}

				//Та самай сложная ошибка 2014/09/05
				//_reading = 0;
				//_connecting = 0;
				
				//_rawData = ves + " : " +  responseData;

			}

			catch (Exception^ e1)
			{
				_reading = 0;
				_connecting = 0;

				///если при парсинге ошибка значит это keepalive и посылаем это в оракл
				//_rawData = "KeepAlive" + " : " + DateTime::Now;
				//_rawData = 
				_log->Break(this->nom, e1->ToString());
				Thread::Sleep(_timeRead);
		 
				//Это скорее всего не работает 
				//try{
				//	bool resultMes = 0;
				//	resultMes = _orcl->_sendData(nom, name, 0, 1, 0, 1, 0, "KAlive", _ip); 
				//	this->oracleConnect = resultMes;
				//	_log->Weigth(this->nom, "KeepAlive", 0);
				//} 
				//catch (Exception^ ){
				//	String^ error = _orcl->error;
				//	_log->Break(name, "Обрыв соединения с Oracle: " + error);
				//	
				//}
			}

		}
		catch (Exception^ e) {
			_reading = 0;
			_connecting = 0;
			_log->Break(this->nom, e->ToString());

		}

	}//while
	Thread::Sleep(_timeRead);

};


void CJaguar::_sendSSM(){
	_counterSend++;	
	ts->FillHeader();
		
	
		switch (_positionSSM)
				{
				case 1 :
					{//Для первого устройства
					_weightJaguar[0] = Int32::Parse(nom);
					//ts->msg.nomer1 = 55;
					try{
					
                        _weightJaguar[1] = _counterSend;
						_weightJaguar[2] = Int32::Parse(ves);
					}
					catch (Exception^ e){
						_weightJaguar[2] = -1;
					}
					break;

					}

				case 2 :
					{//
					_weightJaguar[3] = Int32::Parse(nom);
					try{
					
						_weightJaguar[4] =_counterSend;
                        _weightJaguar[5] = Int32::Parse(ves);
					}
					catch (Exception^ e){
						_weightJaguar[5] = -1;
					}
					break;

					}

				case 3 :
					{//
					_weightJaguar[6] = Int32::Parse(nom);
					try{
					
						_weightJaguar[7] = _counterSend;
                        _weightJaguar[8] = Int32::Parse(ves);
					}
					catch (Exception^ e){
						_weightJaguar[8] = -1;
					}
					break;

					}

				}

	ts->msg.nomer1 = _weightJaguar[0];
    ts->msg.counter1 = _weightJaguar[1];
	ts->msg.ves1 = _weightJaguar[2];
    ts->msg.nomer2 = _weightJaguar[3];
    ts->msg.counter2 = _weightJaguar[4];
    ts->msg.ves2 = _weightJaguar[5];
	ts->msg.nomer3 = _weightJaguar[6];
    ts->msg.counter3 = _weightJaguar[7];
    ts->msg.ves3 = _weightJaguar[8];


		statusJaguar = ts->_SocketToMTS();
		if (!statusJaguar)
		{	delete ts;
			Thread::Sleep(500);
			ts = new ConnectSSM(_ipSSM, _portJaguarSSM);
			statusJaguar = ts->status;
		}
		
	
};