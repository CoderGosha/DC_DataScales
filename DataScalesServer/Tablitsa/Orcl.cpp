#include "StdAfx.h"
#include "Orcl.h"
    
	using namespace Oracle::DataAccess::Client;
	using namespace Oracle::DataAccess::Types;
	using namespace System::Windows::Forms;
	using namespace System::Data;

	using namespace System::Net;
	using namespace System::Net::NetworkInformation;
	using namespace System::Net::Sockets;

COrcl::COrcl(String^ connectionString, String^ timeSend)
{
	 _OC = nullptr;

	_connectionString = connectionString;

	_timeSend = float::Parse(timeSend);
	_timeOut = _timeSend;
	_lastStabil = 0;
	_lastWeight = "NULL";
	result = 0;

	_log = nullptr;
	lastSendTimeDT =  DateTime::Now.AddMinutes(-1);
	////Включаем таймер, для отсчета попыток и повтора отправки
	//_timerTimeOut = gcnew System::Timers::Timer(500);
	//_timerTimeOut->Elapsed += gcnew ElapsedEventHandler(this, &COrcl::OnTimerTimeOut );
 //   _timerTimeOut->Enabled = 1;
	error = "0";
	lastSendTime = "NoSend";


			// Получение имени компьютера.
	_host = System::Net::Dns::GetHostName();

		//получаем MAC
		array<NetworkInterface^>^adapters = NetworkInterface::GetAllNetworkInterfaces();
	_mac = adapters[0]->GetPhysicalAddress()->ToString();
	//получаем юзера
	_user = Environment::UserName;
}

COrcl::COrcl(String^ connectionString, String^ timeSend, CLogCsv^ log)
{
	 _OC = nullptr;
	_connectionString = connectionString;

	_timeSend = float::Parse(timeSend);
	
	_lastStabil = 0;
	_lastWeight = "NULL";
	result = 0;
	lastSendTimeDT =  DateTime::Now.AddMinutes(-1);
    _log = log;

	////Включаем таймер, для отсчета попыток и повтора отправки
	//_timerTimeOut = gcnew System::Timers::Timer(500);
	//_timerTimeOut->Elapsed += gcnew ElapsedEventHandler(this, &COrcl::OnTimerTimeOut );
 //   _timerTimeOut->Enabled = 1;
	error = "0";
	lastSendTime = "NoSend";

				// Получение имени компьютера.
	_host = System::Net::Dns::GetHostName();

	


	//получаем MAC
		array<NetworkInterface^>^adapters = NetworkInterface::GetAllNetworkInterfaces();
	_mac = adapters[0]->GetPhysicalAddress()->ToString();
	//получаем юзера
	_user = Environment::UserName;
}

COrcl::~COrcl(){
	try{
		if (_OC != nullptr)
			_OC->Close();

		delete _OC;
	}
	
	
	catch (Exception ^ e){

	}

}

bool COrcl::sendData(String^ nom, String^ name, Int32 tara, Int32 stabil, Int32 zero, Int32 kg, Int32 tonn, String^ ves, String^ ip, String^ Weigth_Hour, String^ RawData)
{//логика отправки  данных с таймаутами


	if ((_lastWeight != ves) || (_lastStabil != stabil))
	{//Если новый вес изменился то
		//Отправляем данные
		result = _sendData(nom, name, tara, stabil, zero, kg, tonn, ves, ip, Weigth_Hour, RawData);
		//Переприсваиваем
		_lastWeight = ves;
		_lastStabil = stabil;
		
		
	}
	else 
	{//Если вес не изменился

		//Нормальный алгоритм

		if (lastSendTimeDT.AddMilliseconds(_timeSend) <= DateTime::Now){
			//Отправляем данные
			result =  _sendData(nom, name, tara, stabil, zero, kg, tonn, ves, ip, Weigth_Hour, RawData);
			//Переприсваиваем
			_lastWeight = ves;
			_lastStabil = stabil;
		}


	}
	return result;
	
}
bool COrcl::_sendData(String^ nom, String^ name, Int32 tara, Int32 stabil, Int32 zero, Int32 kg, Int32 tonn, String^ ves, String^ ip, String^ Weigth_Hour, String^ RawData)
{ 
	bool result = 1;
//Отправка даных в оракл
	//try{

	DateTime td = DateTime::Now;

	if (_OC == nullptr) {
		_OC = gcnew OracleConnection(_connectionString);
		_OC->Open();

	}
		//Создаем подключние

	OracleCommand^ cmd = gcnew OracleCommand("VESY_ZAP_PACK.save_ves", _OC);
		cmd->CommandType = System::Data::CommandType::StoredProcedure;

		cmd->Parameters->Add("vesy_guid_", Oracle::DataAccess::Client::OracleDbType::Int64, ParameterDirection::Output);
		cmd->Parameters->Add("vesy_nom_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = nom;
		cmd->Parameters->Add("vesy_name_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = name;

		cmd->Parameters->Add("vesy_tara_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = tara;

		cmd->Parameters->Add("vesy_stabil_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = stabil;

		cmd->Parameters->Add("vesy_zero_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = zero;
		cmd->Parameters->Add("vesy_kg_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = kg;
		cmd->Parameters->Add("vesy_tonn_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = tonn;
		cmd->Parameters->Add("vesy_ves_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = ves;


		

		cmd->Parameters->Add("vesy_ip_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = ip; //ip
		cmd->Parameters->Add("vesy_mac_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = _mac;//mac_adr;
		cmd->Parameters->Add("vesy_cur_user_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = _user;
		cmd->Parameters->Add("vesy_err_code_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = 0;
		cmd->Parameters->Add("vesy_error_", Oracle::DataAccess::Client::OracleDbType::Varchar2, ParameterDirection::Output);
		cmd->Parameters->Add("vesy_dnsname_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = _host;//strHostName;
	
		String^ now = DateTime::Today.ToString();
		cmd->Parameters->Add("vesy_datetime_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = now;
		cmd->Parameters->Add("vesy_err_db_code_", Oracle::DataAccess::Client::OracleDbType::Int16)->Value = 1;
		cmd->Parameters->Add("vesy_error_db_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = "1";
		
		cmd->Parameters->Add("vesy_raw_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = RawData;
		cmd->Parameters->Add("vesy_ves_hour_", Oracle::DataAccess::Client::OracleDbType::Varchar2)->Value = Weigth_Hour;
        


	try
		{
		error = "0";

		
		
		cmd->ExecuteNonQuery();
		String^ now = DateTime::Now.ToString();
		lastSendTime = now;
		}
	catch (Oracle::DataAccess::Types::OracleTypeException::Exception ^e)
      { 
		result = 0;
	    error = e->ToString();

		//Делаем переподключение
		try {
			_OC->Close();
		}

		catch (Exception ^ e)
		{

		}
		_OC = nullptr;
       }
		
		//catch (Exception ^e){

		//}
        finally
            {
				 
				//return result;
				 //return result; 
            }
	//}
	//
	//	result = false;
	//}
	DateTime te =  DateTime::Now;
    TimeSpan tR = te - td ;
	if (_log != nullptr) 
		_log->sendOracle("Посылка в БД: " + ves + " Стаб: " + stabil.ToString() + " Time: "+ tR.ToString() + " мс.");

	lastSendTimeDT = DateTime::Now;
 return result;       
};



void COrcl::OnTimerTimeOut(System::Object ^source, System::Timers::ElapsedEventArgs ^e){
		//Увеличиваем счетчик таймаута
/*	_timeOut += 500;*/ 

}