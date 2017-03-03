#pragma once
#include "Port.h"
#include "Orcl.h"
#include "MoxaTCP.h"
#include "Jaguar.h" 

ref class CModel
{
private:
    
    bool _ind_tara;
    bool _ind_stabil;
    bool _ind_null;
	bool vesFixed;
	String^ vesFixedTime;
	Int32 _timeOut;
    CPort^ _port; 
    Thread^ readThread;
    void _parsing(void);
	
	void _parsingJaguar(void);

    String^ _weight;
	
    bool _work;
	String^ typeConnect;
	CMoxaTCP^ _moxa;
	CJaguar^ _jaguar;
	bool _vesKg;
	String^ error;
	int _vesMicrosim;
	bool _connectionJaguar;
	CLogCsv^ _log;
	String^ MagicString;



public:
    CModel(String^ portName, int baudRate, Parity parity, int dataBits, StopBits stopBits, Int32 timeRead, bool vesKg, CLogCsv^ log);
    CModel(String^ ip, String^ port, Int32 timeRead, bool vesKg, CLogCsv^ log, String^ MagicString);
   
	~CModel();
    String^ getWeight(void){return _weight;};
	String^ RawDate;
	String^ Weigth_Hour;
	bool CanWriteOracle;
    bool getInd_tara(void){return _ind_tara;};
    bool getInd_stabil(void){return _ind_stabil;};
    bool getInd_null(void){return _ind_null;};
	bool getFix(void){return vesFixed;};
	String^ getFixTime (void) {return vesFixedTime;};

    void command(String^ cmd);
	String^ getError(){return error;};
	String^ getCurrentJaguarIp(){return _jaguar->getCurrentIp();};
	int getVesMicrosim(){return _vesMicrosim;};
	bool getStatusConnectJaguar(){return  _connectionJaguar;};
	bool getStatusMoxa();
	
	void parsingTCP(void);
	void parsingTCP_WE2120_ST(void);
	void parsingTCP_WE2120_ALT(void);
	void parsingTCP_DEFAULT(String^ Begin, String^ End);
	void parsingTCP_INECONT_OPUS(void);
	void parsingTCP_DISOMAT_SATUS(void);
	void parsingTCP_DATASCALES_REPEATER(void);
	void parsingTCP_DATASCALES_DLL(String^ modelDll);

};
