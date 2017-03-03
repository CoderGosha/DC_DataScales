#pragma once
#include "LogCsv.h"
#include "Model.h"
#include "Form1.h"
#include "Jaguar.h"


using namespace System::Timers;
using namespace System::Net::Sockets;
using namespace System::Collections;
using namespace System::Collections::Generic;
//using namespace System::Net;


ref class CWeight
{
private:
    CModel^ _mdl;
    CLogCsv^ _log;
	CJaguar^ _jaguar;
    Tablitsa::Form1^ _FormOut;
	void OracleSend(void);
	bool _sendOracle;
	bool _work;
	bool _sendRawDate;
	//Для отправки данных в оракл
	COrcl^ orcl;
	Thread^ readThread;
	void Worker();
	

	Thread^ OracleThread;
	List<bool>^ buttonControl;
	String^ _typeScales;
	String^ _currentIP;
    int _nomerSSM;
    int _counterVes;
    String^ _oldVes;
	void WorkerJaguar();
						
	bool resultMes;
	String^ _RawData;
	String^ _Weigth_Hour;
	
	List<List<String^>^>^ buf_Oracle;
	String^ _ModelDll;

public:
    CWeight(String^ prtName, int bdRate, Parity prty, int dtBits, StopBits stpBits, Int32 tmRead, String^ name_weight, String^ locat, List<String^>^ oraclList, List<bool>^ buttonControl, int nomerSSM, bool vesKg, bool sendRawData, String^ _ipSSM);
	CWeight(System::String ^tScales, String^ ip, String^ port, Int32 tmRead, String^ name_weight, String^ locat, List<String^>^ oraclList,  List<bool>^ buttonControl, int nomerSSM, bool vesKg, bool sendRawData, String^ _ipSSM, String^ MagicString, String^ ModelDll);
	
	//Ягуары
	CWeight(String^ ip, String^ port, Int32 tmRead, String^ name_weight, String^ locat, List<String^>^ oraclList, int nomerSSM, bool vesKg, String^ _ipSSM, Int32 _portJaguarSSM, List<int>^  _weightJaguar, bool sendRawData);
//asdsad
	~CWeight();
    bool ind_tara;
    bool ind_stabil;
    bool ind_null;
    bool connect;
	bool oracleConnect;
	bool _vesKg;
    String^ weight;
    String^ name;
    String^ location;
    String^ portName;
    int baudRate;
    Parity parity;
    int dataBits;
    StopBits stopBits;
    Int32 timeRead;

	String^ DataTrackIP;
	String^ MagicString; 
    void Show(void);
	void cmd(String^ cmd);

	void Stop(void);
	void Start(void);
	String^ getErrorOracle(void);
	String^ getLastSendTime(void){return orcl->lastSendTime;}; 
	bool sendOracle(){return _sendOracle;};
		
	String^ getTypeScales();
	String^ getIp(){return _currentIP;};
    int getNomerSSM(){return _nomerSSM;};
    int getCounterVes(){return _counterVes;}; //Количество раз которое изменился вес;
	int getVesMicrosim(){return _mdl->getVesMicrosim();};
	bool getStatusSSMJaguar(){return _jaguar->statusJaguar;};
	String^ getRawData(){return _RawData;};
	String^ getWeigthHour(){return _Weigth_Hour;};
	
	void SetStatusUiOracle(bool result);

	void SetDataTrackIp(String^ Ip){DataTrackIP = Ip;}; 

	String^ ModelDll(void) {return _ModelDll;};
};
