#pragma once

#include "LogCsv.h"

using namespace System;
using namespace System::Timers;
	using namespace Oracle::DataAccess::Client;
	using namespace Oracle::DataAccess::Types;


ref class COrcl
{

private:
	String^ _connectionString;
	System::Timers::Timer^ _timerTimeOut;

	void OnTimerTimeOut(System::Object ^source, System::Timers::ElapsedEventArgs ^e);
	bool result;

	String^ _lastWeight;
	Int32 _lastStabil;
	float _timeOut;
	float _timeSend;
	CLogCsv^ _log;
	OracleConnection^ _OC;

	DateTime lastSendTimeDT;
	String^ _host;
	String^ _mac;
	String^ _user;

	
public:
	COrcl(String^ connectionString, String^ timeSend);
	COrcl(String^ connectionString, String^ timeSend, CLogCsv^ log);
	~COrcl();

	bool _sendData(String^ nom, String^ name, Int32 tara, Int32 stabil, Int32 zero, Int32 kg, Int32 tonn, String^ ves, String^ ip, String^ Weigth_Hour, String^ RawData);

	bool sendData(String^ nom, String^ name, Int32 tara, Int32 stabil, Int32 zero, Int32 kg, Int32 tonn, String^ ves, String^ ip, String^ Weigth_Hour, String^ RawData);
	String^ error;
	String^ lastSendTime;
	DateTime GetLastSendDateTime(void) {return lastSendTimeDT;}
};
