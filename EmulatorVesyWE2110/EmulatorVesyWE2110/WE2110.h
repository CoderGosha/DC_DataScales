using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace System::Net::Sockets;
using namespace System::Net;

#pragma once

ref class CWE2110
{
public:
	CWE2110(Int32 NPP_, String^ NameVesy_, String^ TcpIp_, String^ TcpPort_, Int32 TimeOutGenerateRaw_, Random^ rdn);
	void UpdateRandom(Random^ rdn) {rand = rdn;};
	~CWE2110();
	Int32 NPP;
	String^ NameVesy;
	String^ RawString;
	String^ TcpIp;
	String^ TcpPort;
	Int32 TimeOutGenerateRaw;
	String^ DateLastRaw;
	Thread^ genThread;
	bool GenerateWork;
	void GeneratorRaw();

	String^ VES;

private: 
	String^ _generateRaw();
	void LoadParams();
	List<String^>^ L_Sign;
	List<String^>^ L_Status;
	List<String^>^ L_Stab;
	Random^ rand;
	void ListenerTCPServer();

	bool _workTcpServer;
	Thread^ ThreadTcpServer;
	TcpListener^ _srv; //Сервер для подключения удаленных терминалов
	TcpClient^ client ;
	NetworkStream^ stream ;

};
