#pragma once



//Класс для взаимодействия с удаленным мониторингом
//Входные данные это IP:PORT
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System;
using namespace System::Globalization;
using namespace Oracle::DataAccess::Client;
using namespace Oracle::DataAccess::Types;
using namespace System::Data;
using namespace System::Runtime::Serialization::Formatters::Binary;
using namespace System::IO;


[Serializable]
ref class CTCPSetverToOracle
{

private:
	bool _work;
	Thread^ readThread;
	TcpListener^ _srv; //Сервер для подключения удаленных мониторов
	void Worker();
	List<String^>^ _orcl;
	List<List<String^>^>^ _data;
	List<String^>^ _dataHeader;

	void getDataOracle(String^ nomerVesy, String^ counter);
	array<Byte>^ ToByteArray(List<List<String^>^>^ input);
	List<List<String^>^>^ ByteArrayToList (array<Byte>^ input);

public:
	CTCPSetverToOracle(IPAddress^ ip, Int32 port, List<String^>^ orcl);
	~CTCPSetverToOracle();

};
