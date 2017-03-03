#include "StdAfx.h"
#include "TCPSetverToOracle.h"


CTCPSetverToOracle::CTCPSetverToOracle(IPAddress^ ip, Int32 port, List<String^>^ orcl)
{
//Запомним настройки Oracle
	_orcl = orcl;
	_data = gcnew List<List<String^>^>();
	_dataHeader = gcnew List<String^>();

	//Запускаем сервер

	_srv = gcnew TcpListener(ip, port);
	_srv->Start();
	_work = 1;

	readThread = gcnew Thread(gcnew ThreadStart(this, &CTCPSetverToOracle::Worker));
    readThread->Start();

	
}


CTCPSetverToOracle::~CTCPSetverToOracle(){
	_work = 0;
	_srv->Stop();
    readThread->Join();
    delete readThread;
	delete _srv;
}


void CTCPSetverToOracle::Worker()
{
	
	//Thread::Sleep(1000);
	//this->getDataOracle("37", "10");
	array<Byte>^bytes = gcnew array<Byte>(200086);

	while ( _work )
      {
         try
			 {
			TcpClient^ client = _srv->AcceptTcpClient();
			NetworkStream^ stream = client->GetStream();
			 // Get a stream Object* for reading and writing
			 
			 Int32 i;

 			while ( i = stream->Read( bytes, 0, bytes->Length ) )
			{
				
				List<List<String^>^>^ inPutList = this->ByteArrayToList(bytes);

						
				//System::Windows::Forms::MessageBox::Show(inPutList[0][0]);
				
				//отсылаем данные
				this->getDataOracle(inPutList[0][1], inPutList[0][2]);
				array<Byte>^ msg = this->ToByteArray(_data);
					// Send back a response.
				stream->Write( msg, 0, msg->Length );
				
			
			}

		client->Close();
		 // Shutdown and end connection
			 
		  }
	  
		catch ( SocketException^ e ) 
		{
      
		}
		catch (Exception^ e){

		}
	}
}

void CTCPSetverToOracle::getDataOracle(System::String^ nomerVesy, System::String^ counter){
//Запрос данных у Oracle
		String^ ConnectionString ="Data Source="+ _orcl[0] +";User ID="+ _orcl[1] +";Password="+ _orcl[2] +"";
		OracleConnection^ OC = gcnew OracleConnection(ConnectionString);
		OracleCommand^ cmd = gcnew OracleCommand("VESY_ZAP_PACK.Get_Ves", OC);
		cmd->CommandType = System::Data::CommandType::StoredProcedure;
		/*
		  --Получение N последних записей из таблицы логов по весам
			  procedure Get_Ves   
			   (
				Curs          in out TCursor,
				n             in     integer,
				vesy_nom_     in     vesy.vesy_nom%type
			   )
		*/
		cmd->Parameters->Add("Curs", Oracle::DataAccess::Client::OracleDbType::RefCursor, ParameterDirection::Output);
		cmd->Parameters->Add("n", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = Int32::Parse(counter);
		cmd->Parameters->Add("vesy_nom", Oracle::DataAccess::Client::OracleDbType::Int32)->Value = Int32::Parse(nomerVesy);



		try
		{
			OC->Open();
			OracleDataReader^ reader = cmd->ExecuteReader();
			//cmd->ExecuteNonQuery();
			int i = 0;
			//Выполним обход полученных данных
			DataTable^ table = gcnew DataTable();
			table->Load(reader);
			
			
			//собираем название столбцов
			_dataHeader->Clear();
			_data->Clear();
			for each (DataColumn^ col in table->Columns)
			{
				_dataHeader->Add(col->ColumnName);

			}
			_data->Add(_dataHeader);
			
			//Делаем обход по таблице и пишем в список
			
			if (table->Rows->Count)
			{
				for each (DataRow^ row in table->Rows)
				{
					
					List<String^>^ temp = gcnew List<String^>();
					for each (DataColumn^ col in table->Columns)
					{
						temp->Add(row[col]->ToString());
					}
					_data->Add(temp);
				}
			}

			else {


			}
		
			
		}
		catch (Oracle::DataAccess::Types::OracleTypeException::Exception ^e)
            { 
				System::Windows::Forms::MessageBox::Show(e->ToString());
            }
        finally
            {
				OC->Close(); 
            }


}


array<Byte>^ CTCPSetverToOracle::ToByteArray(List<List<String^>^>^ input){
	 BinaryFormatter^ br = gcnew BinaryFormatter();
	 MemoryStream^ ms  = gcnew MemoryStream();
	
	 br->Serialize(ms, input);

	 return ms->ToArray();
}

List<List<String^>^>^ CTCPSetverToOracle::ByteArrayToList (array<Byte>^ input)
 {
	
	 BinaryFormatter^ br = gcnew BinaryFormatter();
	 MemoryStream^ ms  = gcnew MemoryStream();
	 ms->Write(input, 0, input->Length);
	 ms->Seek(0, System::IO::SeekOrigin::Begin);
	 List<List<String^>^>^ out = (List<List<String^>^>^)br->Deserialize(ms);
	 return out;
}