#include "LogCsv.h"
#include "Orcl.h"
#include "Socket.h"

#pragma once

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Collections::Generic;

ref class CJaguar
{
private:
	String^ _ip;
	String^ _dnsOrIp;

	Int32 _port;
	Int32 _timeRead;
	TcpClient^ _client;
	NetworkStream^ stream;
	Thread^ checkThread;
	Thread^ readThread;

	Thread^ sendThread;

	bool checkConnect;
	bool _connecting;
	bool _reading;
	String^ _rawData;
	int _counterSend;
	CLogCsv^ _log;
	COrcl^ _orcl;
	ConnectSSM* ts;
	String^ _ipSSM; 
	Int32 _portJaguarSSM;

	void _sendSSM();
	void _checkConnect(void);

	void _sendOracle(void);

	void _Reconnect(void);
	void _readData(void);
	void getIpFromDns();
	String^ ves;
	String^ name;
	String^ nom;
	Int32 _positionSSM;
	List<int>^ _weightJaguar;

	List<List<String^>^>^ _weightBuffer;

public:
	CJaguar(String^ ip, Int32 port, Int32 timeRead, CLogCsv^ log, String^ nom, String^ name, Int32 positionSSM, COrcl^ orcl, String^ _ipSSM, Int32 _portJaguarSSM, List<int>^ weightJaguar);
	~CJaguar();
	String^ getRawData(void) {return _rawData;}
	bool getConnect(){ return _reading; };
	String^ getCurrentIp(){return _ip;};
	bool oracleConnect;
	bool statusJaguar;

};
