#include "StdAfx.h"
#include "TCPServer.h"

CTCPServer::CTCPServer(IPAddress^ ip, Int32 port, List<CWeight^>^ weight_list)
{//Инициализируем сервер
	_srv = gcnew TcpListener(ip, port);
	_weight_list = weight_list;
	_srv->Start();
	_work = 1;

	readThread = gcnew Thread(gcnew ThreadStart(this, &CTCPServer::Worker));
    readThread->Start();
}

CTCPServer::~CTCPServer()
{
//Деструктор
	_work = 0;
	_srv->Stop();
    readThread->Join();
    delete readThread;
	delete _srv;

};

array<String^>^ CTCPServer::getData(array<String^>^  inMsg)
{//Обработка входной строки
	
	array<String^>^ outMsg = gcnew array<String^>(10); //Передаем массив в 10 строк
	for (int i = 0; i < 10; i++){outMsg[i]= "";}//Обнуляем
	outMsg[0] = "Error";

	if (inMsg[0] == "get_device") 
	{//Получение списка устройств
		
		outMsg[0] = "get_device";
		int j = 1;
		for each(CWeight^ elem in _weight_list ) 
		{
			if (j < 10) outMsg[j] = elem->name;
			j++;
        }
	}
	
	else if (inMsg[0] == "get_data"){
		
		String^ name = inMsg[1];
		int count = _weight_list->Count;

		for each(CWeight^ elem in _weight_list ) 
		{
			if (elem->name == name){
				outMsg[0] = "get_data";
				outMsg[1] = elem->name;
				outMsg[2] = elem->weight;
				outMsg[3] = elem->ind_tara.ToString();
				outMsg[4] = elem->ind_stabil.ToString();
				outMsg[5] = elem->ind_null.ToString();
				outMsg[6] = elem->_vesKg.ToString();
				outMsg[7] =	(!elem->_vesKg).ToString();
				outMsg[8] =	"False";
				outMsg[9] = "0";
			}
			else {
				count--;
			}
				
		}

		if (count == 0){
			//Если устройства нет
				outMsg[0] = "get_data";
				outMsg[1] = name;
				outMsg[2] = "NoDev";
				outMsg[3] = "False";
				outMsg[4] = "False";
				outMsg[5] = "False";
				outMsg[6] = "False";
				outMsg[7] =	"False";
				outMsg[8] =	"False";
				outMsg[9] = "0";
			}
		}

	else if (inMsg[0] == "get_cmd"){

		String^ name = inMsg[1];
		String^ cmd = inMsg[2];
		
		for each(CWeight^ elem in _weight_list ) 
		{
			if (elem->name == name){
				elem->cmd(cmd);
				outMsg[0] = "get_cmd";
				outMsg[1] = elem->name;
				outMsg[2] = "1";
				outMsg[3] = "0";
				outMsg[4] = "0";
				outMsg[5] = "0";
				outMsg[6] = "0";
				outMsg[7] =	"0";
				outMsg[8] =	"0";
				outMsg[9] = "0";
			}
        }

	}

	return outMsg;

}


void CTCPServer::Worker(){
//Слушаем порт
	 // Buffer for reading data
      array<Byte>^bytes = gcnew array<Byte>(256);
      array<String^>^ inMsg = gcnew array<String^>(10);
	  array<String^>^ OutMsg = nullptr;
	  String^ data;

      // Enter the listening loop.
	  while (( _work ))
      {
         try
			 {
			 TcpClient^ client = _srv->AcceptTcpClient();
			NetworkStream^ stream = client->GetStream();
			 // Get a stream Object* for reading and writing
			 
			 Int32 i;

 			while ( i = stream->Read( bytes, 0, bytes->Length ) )
			{
					//Получаем строку разделенную &
				data = System::Text::Encoding::UTF8->GetString( bytes, 0, i );
				inMsg = data->Split('&', 10);
				OutMsg = this->getData(inMsg); 

				//Посылаем массив преобразовав в строку
				String^ SendStr = "";
				for (int k = 0; k < 10; k++){
					SendStr += OutMsg[k] + "&";
				}
				array<Byte>^msg = System::Text::Encoding::UTF8->GetBytes( SendStr );
					// Send back a response.
				stream->Write( msg, 0, msg->Length );
					
				
			
			}

		client->Close();
		 // Shutdown and end connection
			 
		  }
	  
		 catch ( Exception^ e ) 
		{
      
		}
	  }//While
};