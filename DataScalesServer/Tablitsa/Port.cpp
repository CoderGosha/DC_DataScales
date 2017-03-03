#include "StdAfx.h"
#include "Port.h"
#include "stdlib.h"

using namespace System::Threading;

CPort::CPort(String^ portName, int baudRate, Parity parity, int dataBits, StopBits stopBits, Int32 timeRead)
{

	_serialPort = gcnew SerialPort(portName, baudRate, parity, dataBits, stopBits) ;
    _serialPort->ReadTimeout = timeRead;
    _serialPort->WriteTimeout = timeRead;
    try{
		_serialPort->Open();
    }
    catch (System::InvalidOperationException ^ e){
        Console::WriteLine("�� ������ ����");
    }
    
    catch (System::IO::IOException ^ e )
	{ 
		Console::WriteLine("���� ���������� ��� ��� ������������");}

    catch (System::UnauthorizedAccessException ^e)
	{

    }
}



CPort::~CPort(void)
{

	   
		   _serialPort->Close();
		delete _serialPort;
	
}

String^ CPort::getRawData(void){

		try{

	    
		String^ message = _serialPort->ReadLine();
		//Console::WriteLine(message);
				return message;}
		catch (TimeoutException ^) { 
					return "TimeOut";
		    
			  }
	
		//�� ����� ������ ��������� COM ����
	  catch (System::IO::IOException ^)
		{return "NoConne";} 
	


};


bool CPort::isOpen(void){
    if (_serialPort->IsOpen) {return 1;}
    else { //��������� ������� ��� ���

    try{
    //_sleep(2000);
		Thread::Sleep(2000);
    _serialPort->Open();
    }
    catch (System::InvalidOperationException ^ e){
        Console::WriteLine("�� ������ ����");
        return 0;
    }
    
    catch (System::IO::IOException ^ e ) { 
    Console::WriteLine("���� ���������� ��� ��� ������������");
     return 0;
    }
    catch (System::UnauthorizedAccessException ^e){
         return 0;
    }

    // System.UnauthorizedAccessException

    }
    return 0;
}

void CPort::command(String^  cmd){//�������� ����������� ������
try{
    Thread::Sleep(200);
    _serialPort->WriteLine(cmd);
    Console::WriteLine("��������� �������");
    }
catch (TimeoutException ^) { 
 
}}