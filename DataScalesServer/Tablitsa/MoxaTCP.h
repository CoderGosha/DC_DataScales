#pragma once

#include "LogCsv.h"

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Globalization;
using namespace System::Text;
using namespace System::Diagnostics;

ref class CMoxaTCP
{
private:
	Int32 _port;
	IPAddress^ _localAddr;
	String^ _ip;
	Int32 _timeOut;
	TcpClient^ _client;
	bool _status;
	NetworkStream^ stream;
	CLogCsv^ _log;
	int countFailGetDate;
	int countErrorConnect;
	String^ responseDataBuffering;
	void CleanBuffer();

public:
	String^ getRawData(void);
	String^ getRawData_SendByte(array<Byte>^ sendByte);
	String^ getRawDataBuffer(void);
	String^ getRawDataBuffer_SendByte(array<Byte>^ sendString);

	void CleanBuffer(int ShitStart);

	CMoxaTCP(String^ ip, String^ port, Int32 timeOut, CLogCsv^ log);
	~CMoxaTCP();
	void Connect();
	bool getStatus(){return _status;}
	void command(String^ cmd);

};
