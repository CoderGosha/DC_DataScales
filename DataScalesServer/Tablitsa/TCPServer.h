#pragma once
#include "Weight.h"

//����� ��� �������������� � ��������� ����������
//������� ������ ��� IP:PORT � ������ CWeight, ��� ���������� ����������
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Net;


ref class CTCPServer
{
private:
	bool _work;
	Thread^ readThread;
	TcpListener^ _srv; //������ ��� ����������� ��������� ����������
	List<CWeight^>^ _weight_list;
	array<String^>^ getData(array<String^>^  inMsg);
	void Worker();
	
public:
	CTCPServer(IPAddress^ ip, Int32 port, List<CWeight^>^ weight_list);
	~CTCPServer();

};
