#include "StdAfx.h"
#include "MoxaTCP.h"

CMoxaTCP::CMoxaTCP(String^ ip, String^ port, Int32 timeOut, CLogCsv^ log)
{
	_localAddr = IPAddress::Parse(ip);
	_ip = ip;
	_port = Int32::Parse(port);
	_timeOut = timeOut;
	_client = gcnew TcpClient();
	_status = 0;
	_log = log;
	countFailGetDate = 200; //Для первого запуска
	countErrorConnect = 0;
	responseDataBuffering = String::Empty;

}
void CMoxaTCP::Connect(){
	//Вызов фунции идет при первом вызове getRawData()
	Debug::WriteLine("Пробуем подключится");

	//countErrorConnect += 1;
	try{
		delete _client;
		Thread::Sleep(10 *  countErrorConnect);
		_client = gcnew TcpClient();
	}
	catch (Exception ^e1){
		Debug::WriteLine(e1->Message->ToString());

	}
	_status = 0;
	try{

		_client->Connect(_ip, _port);
		//	_client->Connect();
		this->_status = 1;

		array<Byte>^data = gcnew array<Byte>(64);
		// System::Text::Encoding::
		data = System::Text::Encoding::ASCII->GetBytes("" );
		stream = _client->GetStream();
		stream->WriteTimeout = 300000;
		stream->ReadTimeout = 300000;

		stream->Write( data, 0, data->Length);
		Debug::WriteLine("Переподключение успех");
	}

	catch (SocketException^ e){

		_log->getRawMoxa("SocketException by Reconnect " + e->ToString());
		Debug::WriteLine("Переподключение неудача");
		_status = 0;
		countErrorConnect += 1;
		Thread::Sleep(10 *  countErrorConnect);
		if (countErrorConnect > 100) {
			countErrorConnect = 1;
		}
	}


}



CMoxaTCP::~CMoxaTCP(){
	try{
		stream->Close();
		_client->Close();
		delete _client;
	}

	catch (Exception ^e){

	}
}


//String^ CMoxaTCP::getRawData(void){
//	//Thread::Sleep(_timeOut);
//	//Debug::WriteLine("TestTCP");
//
//try
//{ 
//
// // if (_client->Connected){
// 	 String^ message = "";
//
//	 Thread::Sleep(_timeOut);	
//	 array<Byte>^data = gcnew array<Byte>(1024);
//	 data = gcnew array<Byte>(1024);
//	 String^ responseData = String::Empty;
//	 Int32 bytes = stream->Read( data, 0,data->Length );
//	 responseData = System::Text::Encoding::ASCII->GetString( data, 0, bytes );
//	// Debug::WriteLine(responseData);
//	 _log->getRawMoxa(responseData);
//	 return responseData;
//	//}
//	//else 
//	//{
//	//	_log->Break(_ip, "Переподключаемся");
//	//	_status = 0;
//	//	
//
//	//	Thread::Sleep(1000);
//	//	this->Connect();
//	//	
//	//	
//	//}
//	
//
//}
//
//catch (Exception^ e){
//	_log->getRawMoxa("ExeptRec_1 " + e->ToString());
//
//	try {
//
//     	  if (_client->Connected){
//			_log->getRawMoxa("Lite Reconnect On... " + e->ToString());
//			this->_status = 1;
//   		    array<Byte>^data = gcnew array<Byte>(64);
//			data = System::Text::Encoding::ASCII->GetBytes("" );
//			stream = _client->GetStream();
//			stream->WriteTimeout = 20000;
//			stream->ReadTimeout = 20000;
//
//			stream->Write( data, 0, data->Length);
//		  }
//		  else {
//			  countFailGetDate++;
//			  _log->getRawMoxa("Buffer empry... " + e->ToString());
//			_status = 1;
//			  if (countFailGetDate > 20) {
//					_log->getRawMoxa("countFailGetDate > 20... " + e->ToString());
//					countFailGetDate = 0;
//					this->Connect();
//
//			  }
//		  }
//	}
//	catch (Exception ^e) {
//		_log->getRawMoxa("Lite Reconnect Fail " + e->ToString());
//
//		 Debug::WriteLine(e);
//		 
//		 this->Connect();
//	}
//	 
//
//}
//	
//	return "Error" ;
//};
//

String^ CMoxaTCP::getRawData(void){
	if (!_client->Connected) {
		//Нет подключения
		Debug::WriteLine("Нет подключения к _clinet");
		this->Connect();
		return "";

	}
	{

		try{
			//Debug::WriteLine("Парсинг ON");
			array<Byte>^data = gcnew array<Byte>(1024);
			data = gcnew array<Byte>(1024);
			String^ responseData = String::Empty;

			Int32 bytes = stream->Read( data, 0,data->Length );
			responseData = System::Text::Encoding::ASCII->GetString( data, 0, bytes );
			//Debug::WriteLine(responseData);
			_log->getRawMoxa(responseData);
			return responseData;

		}

		catch (IOException ^e){
			Debug::WriteLine("Истекло время ожидания посылки");
			countErrorConnect += 1;
			Thread::Sleep(10 *  countErrorConnect);
			return "";
		}



	}



}


String^ CMoxaTCP::getRawDataBuffer(void){
	if (!_client->Connected) {
		//Нет подключения
		Debug::WriteLine("Нет подключения к _clinet");
		this->Connect();
		return "";

	}
	{

		try{
			//Debug::WriteLine("Парсинг ON");
			array<Byte>^data = gcnew array<Byte>(1024);
			data = gcnew array<Byte>(1024);
			Int32 bytes = stream->Read( data, 0,data->Length );
			//Проверка
			CleanBuffer();
			//Добавляем к прошлой посылке
			responseDataBuffering += System::Text::Encoding::ASCII->GetString( data, 0, bytes );
			//Debug::WriteLine(responseData);
			_log->getRawMoxa(responseDataBuffering);
			return responseDataBuffering;

		}

		catch (IOException ^e){
			Debug::WriteLine("Истекло время ожидания посылки");
			countErrorConnect += 1;
			Thread::Sleep(10 *  countErrorConnect);
			return "";
		}



	}



}

String^ CMoxaTCP::getRawDataBuffer_SendByte(array<Byte>^ sendString){
	if (!_client->Connected) {
		//Нет подключения
		Debug::WriteLine("Нет подключения к _clinet");
		this->Connect();
		return "";

	}
	{

		try{
			//Debug::WriteLine("Парсинг ON");
			array<Byte>^data = gcnew array<Byte>(1024);
			data = gcnew array<Byte>(1024);
			//Создадим sendByte
			//array<Byte>^sendByte;
			//sendByte = System::Text::Encoding::Unicode->GetBytes(sendString);
			stream->Write(sendString, 0, sendString->Length);
			Int32 bytes = stream->Read( data, 0,data->Length );
			//Проверка
			CleanBuffer();
			//Добавляем к прошлой посылке
			responseDataBuffering += System::Text::Encoding::ASCII->GetString( data, 0, bytes );
			//Debug::WriteLine(responseData);
			_log->getRawMoxa(responseDataBuffering);
			return responseDataBuffering;

		}

		catch (IOException ^e){
			Debug::WriteLine("Истекло время ожидания посылки");
			countErrorConnect += 1;
			Thread::Sleep(10 *  countErrorConnect);
			return "";
		}



	}



}


void CMoxaTCP::CleanBuffer(){
	//Только переполенение провряем
	if (responseDataBuffering->Length > 4000) {
		//Обнуляем буфер
		responseDataBuffering = String::Empty;
		_log->Break("BufferMoxa", "Сброс буффера");
	}
}

void CMoxaTCP::CleanBuffer(int ShitStart){
	//Только переполенение провряем
	if (responseDataBuffering->Length > ShitStart) {
		//Чистим буфер от уже использованого веса
		responseDataBuffering = responseDataBuffering->Remove(0, ShitStart);
	}

}


String^ CMoxaTCP::getRawData_SendByte(array<Byte>^ sendByte){
	if (!_client->Connected) {
		//Нет подключения
		Debug::WriteLine("Нет подключения к _clinet");
		this->Connect();
		return "";

	}
	{

		try{
			//Debug::WriteLine("Парсинг ON");
			array<Byte>^data = gcnew array<Byte>(1024);
			data = gcnew array<Byte>(1024);
			String^ responseData = String::Empty;
			stream->Write(sendByte, 0, sendByte->Length);
			Int32 bytes = stream->Read( data, 0,data->Length );
			responseData = System::Text::Encoding::ASCII->GetString( data, 0, bytes );
			//Debug::WriteLine(responseData);
			_log->getRawMoxa(responseData);
			return responseData;

		}

		catch (IOException ^e){
			Debug::WriteLine("Истекло время ожидания посылки");
			countErrorConnect += 1;
			Thread::Sleep(10 *  countErrorConnect);
			return "";
		}



	}



}

void CMoxaTCP::command(String^ cmd){
	//Отправка управляющей команды весам

	try{
		Debug::WriteLine("Connect SendCommand");
		TcpClient^ client = gcnew TcpClient();
		client->Connect(_ip, _port);

		array<Byte>^data = gcnew array<Byte>(64);
		// System::Text::Encoding::
		data = System::Text::Encoding::ASCII->GetBytes(cmd);
		NetworkStream^ streamCMD = client->GetStream();
		streamCMD->WriteTimeout = 500;
		streamCMD->ReadTimeout = 500;

		streamCMD->Write( data, 0, data->Length);
		client->Close();

	}

	catch (SocketException^ e){
		Debug::WriteLine(e->ToString());

	}
	catch (Exception^ e){
		Debug::WriteLine(e->ToString());

	}
}