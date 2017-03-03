//в конфиге список с кол-во дататреков А в //
//Настрйоках весов список из кол-ва дата треков и выбор необходимого и -1 в позиции если не посылать

#pragma once

#include "Socket.h"
#include "Weight.h"

using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System;

ref class CDataTrack
{
private:
	Int32 _timeOut;
	
	Int32 _portJaguar;
	Int32 _portMicrosim;
	ConnectSSM* ts;
	ConnectSSM* tsM;
	List<CWeight^>^ _weigth;

	int cnt_jaguar;
	Thread^ sendJaguarThread;
	bool _sendJaguar;
	void _sendJaguarWork();


	Thread^ sendMicrosimThread;
	bool _sendMicrosim;
	void _sendMicrosimWork();

	bool statusJaguar;
	bool statusMicrosim;
	int counterJaguar;
	int counterMicrosim;
	int _NomerDT;

public:
	CDataTrack(List<CWeight^>^ weigth, String^ ip, Int32 timeOut, Int32 portMicrosim, Int32 portJaguar, Int32 NomerDT);
	~CDataTrack();
	void Send();
	bool getStatusMicrosim(){return statusMicrosim;};
	bool getStatusJaguar(){return statusJaguar;};
	String^ _ip;
};

