#include "StdAfx.h"
#include "TCPClient.h"

CTCPClient::CTCPClient(String^ ip, Int32 port)
{//Настроим подключение к серверу
	_port = port;
	_ip = ip;
}

void CTCPClient::Setup(String^ ip, Int32 port)
{
	_port = port;
	_ip = ip;
//nullptr;
}

CTCPClient::~CTCPClient(void){

}

array<String^>^ CTCPClient::getDevice(void){
//Спрашиваем у сервера какие подключены устройства
	try{
	
	  TcpClient^ client = gcnew TcpClient( _ip, _port);
      NetworkStream^ stream = client->GetStream();
		
	  //Создаем массив и забиваем нулями
	  array<String^>^ SendMsg = gcnew array<String^>(10);
	  for (int i = 0; i < 10; i++){
		SendMsg[i] = "";
	  }
	  SendMsg[0] = "get_device";
		
	  //Посылаем массив из 10 строк
	  String^ SendStr = "";
	  for (int i = 0; i < 10; i++){
			SendStr += SendMsg[i] + "&";
	  }

	  array<Byte>^dataSend = Text::Encoding::UTF8->GetBytes( SendStr );
	  stream->Write( dataSend, 0, dataSend->Length );
	  array<Byte>^data = gcnew array<Byte>(256);
	  String^ responseData = String::Empty;
	  array<String^>^ ResMsg = gcnew array<String^>(10);

	  Int32 bytes = stream->Read( data, 0, data->Length );
	  responseData = Text::Encoding::UTF8->GetString( data, 0, bytes );
	  ResMsg = responseData->Split('&', 10);
	  

      // Close everything.
      client->Close();
	  return ResMsg;

	  	}

  catch (NullReferenceException^ ){
   }
   catch (Exception^ ex) 
   {

   }



}

array<String^>^ CTCPClient::getData(String^ deviceName){
//Спрашиваем у сервера данные по соотведствующему устройству
	try{ 
	  TcpClient^ client = gcnew TcpClient( _ip, _port);
      NetworkStream^ stream = client->GetStream();
		
	  //Создаем массив и забиваем нулями
	  array<String^>^ SendMsg = gcnew array<String^>(10);
	  for (int i = 0; i < 10; i++){
		SendMsg[i] = "";
	  }
	  SendMsg[0] = "get_data";
	  SendMsg[1] = deviceName;
		
	  //Посылаем массив из 10 строк
	  String^ SendStr = "";
	  for (int i = 0; i < 10; i++){
			SendStr += SendMsg[i] + "&";
	  }

	  array<Byte>^dataSend = Text::Encoding::UTF8->GetBytes( SendStr );
	  stream->Write( dataSend, 0, dataSend->Length );
	  array<Byte>^data = gcnew array<Byte>(256);
	  String^ responseData = String::Empty;
	  array<String^>^ ResMsg = gcnew array<String^>(10);

	  Int32 bytes = stream->Read( data, 0, data->Length );
	  responseData = Text::Encoding::UTF8->GetString( data, 0, bytes );
	  ResMsg = responseData->Split('&', 10);
	  

      // Close everything.
      client->Close();
	  return ResMsg;
	}
   catch (Exception^ ex) 
   {

   }
}


void CTCPClient::getCmd(String^ deviceName, String^ cmd){
//Спрашиваем у сервера данные по соотведствующему устройству
	try{ 
	  TcpClient^ client = gcnew TcpClient( _ip, _port);
      NetworkStream^ stream = client->GetStream();
		
	  //Создаем массив и забиваем нулями
	  array<String^>^ SendMsg = gcnew array<String^>(10);
	  for (int i = 0; i < 10; i++){
		SendMsg[i] = "";
	  }
	  SendMsg[0] = "get_cmd";
	  SendMsg[1] = deviceName;
	  SendMsg[2] = cmd;
		
	  //Посылаем массив из 10 строк
	  String^ SendStr = "";
	  for (int i = 0; i < 10; i++){
			SendStr += SendMsg[i] + "&";
	  }

	  array<Byte>^dataSend = Text::Encoding::UTF8->GetBytes( SendStr );
	  stream->Write( dataSend, 0, dataSend->Length );
	  array<Byte>^data = gcnew array<Byte>(256);
	  String^ responseData = String::Empty;
	  array<String^>^ ResMsg = gcnew array<String^>(10);

	  Int32 bytes = stream->Read( data, 0, data->Length );
	  responseData = Text::Encoding::UTF8->GetString( data, 0, bytes );
      // Close everything.
      client->Close();

	}
   catch (Exception^ ex) 
   {

   }
}
