#pragma once
using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;

ref class CPort
{
private:
    SerialPort^ _serialPort; //

public:
    CPort(String^ portName, int baudRate, Parity parity, int dataBits, StopBits stopBits, Int32 timeRead);

	~CPort(void);
    String^ getRawData(void);
    void command (String^  cmd);
    bool isOpen(void);
};
