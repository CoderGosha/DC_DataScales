#pragma once
#include "Weight.h"

// ласс дл€ взаимодействи€ с удаленным терминалом
//¬ходные данные это IP:PORT и список CWeight, дл€ управлени€ микросимом
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Net;


ref class CTCPServer
{
private:
	bool _work;
	Thread^ readThread;
	TcpListener^ _srv; //—ервер дл€ подключени€ удаленных терминалов
	List<CWeight^>^ _weight_list;
	array<String^>^ getData(array<String^>^  inMsg);
	void Worker();
	
public:
	CTCPServer(IPAddress^ ip, Int32 port, List<CWeight^>^ weight_list);
	~CTCPServer();

};
