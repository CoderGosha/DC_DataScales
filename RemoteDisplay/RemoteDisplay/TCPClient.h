#include "StdAfx.h"
#include "stdafx.h"
#pragma once

using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System;


ref class CTCPClient
{
private:
	Int32 _port;
	String^ _ip;


public:
	CTCPClient(String^ ip, Int32 port);
	~CTCPClient(void);
	
	void Setup(String^ ip, Int32 port);
	array<String^>^ getDevice(void);
	array<String^>^ getData(String^ deviceName);
	void getCmd(String^ deviceName, String^ cmd);

};
