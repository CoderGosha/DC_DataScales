#include "StdAfx.h"
#include "WE2110.h"

CWE2110::CWE2110(Int32 NPP_, String^ NameVesy_, String^ TcpIp_, String^ TcpPort_, Int32 TimeOutGenerateRaw_, Random^ rdn)
{
	NPP = NPP_;
	NameVesy = NameVesy_;
	String^ myHost = System::Net::Dns::GetHostName();
	TcpIp = System::Net::Dns::GetHostByName(myHost)->AddressList[0]->ToString();;
	TcpPort = TcpPort_;
	TimeOutGenerateRaw = TimeOutGenerateRaw_;
	RawString = "NULL RAW";
	DateLastRaw = "NULL";

	LoadParams();

	rand = rdn;
	//Thread::Sleep(rand->Next(10));
	genThread = gcnew Thread(gcnew ThreadStart(this, &CWE2110::GeneratorRaw));
	genThread->Start();
	GenerateWork = true;

	_srv = gcnew TcpListener(IPAddress::Parse(TcpIp), Int32::Parse(TcpPort));
	_srv->Start();
	_workTcpServer = 1;


	ThreadTcpServer = gcnew Thread(gcnew ThreadStart(this, &CWE2110::ListenerTCPServer));
    ThreadTcpServer->Start();
}

	


CWE2110::~CWE2110(){
	GenerateWork = false;
	genThread->Abort();

	_workTcpServer = false;
	ThreadTcpServer->Abort();

	_srv->Stop();

	delete genThread;
	delete ThreadTcpServer;
	delete _srv;

}

void CWE2110::LoadParams(){
	L_Sign = gcnew List<String^>();
	L_Sign->Add(" ");
	L_Sign->Add("-");
	L_Sign->Add(" ");
	L_Sign->Add(" ");
	L_Sign->Add(" ");
	L_Sign->Add("-");


	L_Status = gcnew List<String^>();
	//L_Status->Add("G");
	//L_Status->Add("N");
	//L_Status->Add("U");
	//L_Status->Add("O");
	//L_Status->Add("M");
	//L_Status->Add("E");
	L_Status->Add("B");
	L_Status->Add("N");
		L_Status->Add("B");
	L_Status->Add("N");
		L_Status->Add("B");
	L_Status->Add("N");

	L_Stab = gcnew List<String^>();
	//L_Status->Add("G");
	//L_Status->Add("N");
	//L_Status->Add("U");
	//L_Status->Add("O");
	//L_Status->Add("M");
	//L_Status->Add("E");
	L_Stab->Add("?");
	L_Stab->Add(" ");
	L_Stab->Add(" ");

}
String^ CWE2110::_generateRaw(){

	

//Алгоритм генерации посылок от WE2110
	String^ _raw;
	/*String^ StartSim = Convert::ToChar(02).ToString();*/
	//String^ End1 = Convert::ToChar(23).ToString();;
	
	//String^ StartSim = Convert::ToChar(2).ToString(); //WE
	String^ StartSim = "    ";
	//String^ End1 = Convert::ToChar(3).ToString();; //WE
	int value = Convert::ToInt32("0D", 16);
    // Get the character corresponding to the integral value. 
	String^ End1 = Char::ConvertFromUtf32(value);
	
	value = Convert::ToInt32("0A", 16);

	String^ End2 = Char::ConvertFromUtf32(value);;
	
	String^ Weigth = rand->Next(9999).ToString();
	VES = Weigth;
	String^ Status = L_Status[rand->Next(6)];

	

	String^ Sign = L_Sign[rand->Next(6)];
	String^ Stab = L_Stab[rand->Next(3)];

	Weigth = Sign + Weigth;
	Weigth = Weigth->PadLeft(5, ' ');
	Weigth = Weigth + "" + Stab + Status;

	_raw = StartSim + Weigth + "  " + End1 + End2;
	return _raw;
}


void CWE2110::GeneratorRaw(){
	
	
	
	while (GenerateWork){
		
		this->RawString = _generateRaw();
		
		this->DateLastRaw = DateTime::Now.ToString();
		Thread::Sleep(TimeOutGenerateRaw);
	}

}

void CWE2110::ListenerTCPServer(){

	client = _srv->AcceptTcpClient();
	stream = client->GetStream();
	stream->WriteTimeout = 1;
	while ( _workTcpServer )
      {
		try
		 {


			array<Byte>^msg = System::Text::Encoding::UTF8->GetBytes( this->RawString  );
					// Send back a response.
			//if (stream->CanWrite)
			stream->Write( msg, 0, msg->Length );

			Thread::Sleep(this->TimeOutGenerateRaw);
		}
		catch ( Exception^ e ) 
		{
			//_srv = gcnew TcpListener(IPAddress::Parse(TcpIp), Int32::Parse(TcpPort));
			//_srv->Start();

			//TcpClient^ client = _srv->AcceptTcpClient();
			//NetworkStream^ stream = client->GetStream();

			try{
				_srv->Stop();

				delete _srv;

				_srv = gcnew TcpListener(IPAddress::Parse(TcpIp), Int32::Parse(TcpPort));
				_srv->Start();
				//client->Close();
				client = _srv->AcceptTcpClient();
				stream = client->GetStream();
			}
			catch (Exception^ e){
			}

		}
	}

	client->Close();
};
