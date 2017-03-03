#pragma once

#include "StdAfx.h"
#define WIN32_LEAN_AND_MEAN

//#include <iostream>
#include <winsock2.h>


#pragma pack(push, 1)



#pragma pack(pop)

#pragma comment(lib, "ws2_32.lib")

using namespace System;
	using namespace Runtime::InteropServices;

class  ConnectSSM{
public:
	int portJaguar;
	int portMicrosim;
	bool status;
	int TCP_cnt_MTS;
	int TCP_cnt_MTS2;



	ConnectSSM(String^ ip, int port){
	
			//Преобразуем от String^ к char*
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(ip)).ToPointer();
	
		
		_StartupWinSock();
		TCP_cnt_MTS = 0;
		TCP_cnt_MTS2 = 0;
		status = this->_ConnectMTS(chars, port);
		
	
	};
	
	
	~ConnectSSM(){
		//_CleanupWinSock();
		
	}



#pragma pack(push, 1)

		struct MsgTCPJaguar
	{

		//1. Заголовок пакета
		unsigned  short int	len;		   // длина сообщения  когда short - абракадабры
		unsigned  short int	id;			   // ID телеграммы
		unsigned  short int	cnt;		   // счетчик телеграмм (0..32767)
		unsigned  int	    seconds;	   // текущее время 
		unsigned  short int	mseconds;
		unsigned  short int	status;	
		
		//Jaguar1
		int	        nomer1;	    
		int	        ves1;	   //в КГ 
        int     counter1; //Стчетчик передачи пакетов изменяем когда изменяется вес

		//Jaguar2
		int	        nomer2;	    
		int	        ves2;	   //в КГ 
        int     counter2;
		  
		//Jaguar3
		int	        nomer3;	    
		int	        ves3;
        int     counter3; //в КГ 

		char        rezerv[222];     // резерв

	    
	} msg;

struct MsgTCPMicrosim
	{
		////1. Заголовок пакета
		//unsigned  short int	len;		   // длина сообщения  когда short - абракадабры
		//unsigned  short int	id;			   // ID телеграммы
		//unsigned  short int	cnt;		   // счетчик телеграмм (0..32767)
		//unsigned  int	    seconds;	   // текущее время 
		//unsigned  short int	mseconds;
		//unsigned  short int	status;	
		

	  //Микросим1
    int	        nomer1;	    
    int	        ves1;	   //в КГ 
	char        stable1;	   //в 
    int         counter1;

	 //Микросим2
    int	        nomer2;	    
    int	        ves2;	   //в КГ 
	char        stable2;	   //в 
    int         counter2;

	//Микросим3
    int	        nomer3;	    
    int	        ves3;	   //в КГ 
	char        stable3;	   //в 
    int         counter3;

     //Микросим4
    int	        nomer4;	    
    int	        ves4;	   //в КГ 
	char        stable4;	   //в 
    int         counter4;

	     //Микросим6
    int	        nomer5;	    
    int	        ves5;	   //в КГ 
	char        stable5;	   //в 
    int         counter5;

	//Микросим6
    int	        nomer6;	    
    int	        ves6;	   //в КГ 
	char        stable6;	   //в
    int         counter6;

		//Микросим7
    int	        nomer7;	    
    int	        ves7;	   //в КГ 
	char        stable7;	   //в 
    int         counter7;

			//Микросим8
    int	        nomer8;	    
    int	        ves8;	   //в КГ 
	char        stable8;	   //в 
    int         counter8;

				//Микросим9
    int	        nomer9;	    
    int	        ves9;	   //в КГ 
	char        stable9;	   //в
    int         counter9;

					//Микросим9
    int	        nomer10;	    
    int	        ves10;	   //в КГ 
	char        stable10;	   //в 
    int         counter10;

    char        rezerv[128];     // резерв

	} msgMicrosim;
#pragma pack(pop)

#pragma comment(lib, "ws2_32.lib")



		

	SOCKET _sct;
	//int TCP_cnt_MTS;



	void FillHeaderTimes()
        {
            SYSTEMTIME st;
	        GetSystemTime(&st);
            ::FILETIME fst;
	        SystemTimeToFileTime(&st,&fst);
	        _int64 ist = *(_int64*)&fst;

	        SYSTEMTIME tdc;
	        tdc.wYear = 1988;
	        tdc.wMonth = 1;
	        tdc.wDay = 1;
	        tdc.wHour = 0;
	        tdc.wMinute = 0;
	        tdc.wSecond =0;
	        tdc.wDayOfWeek = 0;
	        tdc.wMilliseconds = 0;

            ::FILETIME ftdc;
	        SystemTimeToFileTime(&tdc,&ftdc);
	        _int64 itdc = *(_int64*)&ftdc;
	        _int64 res = ist - itdc;
	        _int64 h100mks = res / 10 / 100; //100мкс

	        msg.seconds = h100mks / 10000;
	        msg.mseconds = h100mks % 10000;
        }
	
	//void FillHeaderTimesMicrosim()
 //       {
 //           SYSTEMTIME st;
	//        GetSystemTime(&st);
 //           ::FILETIME fst;
	//        SystemTimeToFileTime(&st,&fst);
	//        _int64 ist = *(_int64*)&fst;

	//        SYSTEMTIME tdc;
	//        tdc.wYear = 1988;
	//        tdc.wMonth = 1;
	//        tdc.wDay = 1;
	//        tdc.wHour = 0;
	//        tdc.wMinute = 0;
	//        tdc.wSecond =0;
	//        tdc.wDayOfWeek = 0;
	//        tdc.wMilliseconds = 0;

 //           ::FILETIME ftdc;
	//        SystemTimeToFileTime(&tdc,&ftdc);
	//        _int64 itdc = *(_int64*)&ftdc;
	//        _int64 res = ist - itdc;
	//        _int64 h100mks = res / 10 / 100; //100мкс

	//        msgMicrosim.seconds = h100mks / 10000;
	//        msgMicrosim.mseconds = h100mks % 10000;
 //       }
	  
	void FillHeader()
        {

            msg = MsgTCPJaguar(); //очистить структуру
            msg.len = sizeof(msg);
	        msg.id = 1105;
            msg.cnt = TCP_cnt_MTS;         
            TCP_cnt_MTS++; //счетчик пакетов
            FillHeaderTimes();
        }

	//void FillHeaderMicrosim()
 //       {

 //           msgMicrosim = MsgTCPMicrosim(); //очистить структуру
 //           msgMicrosim.len = sizeof(msgMicrosim);
	//        msgMicrosim.id = 1106;
 //           msgMicrosim.cnt = TCP_cnt_MTS2;         
 //           TCP_cnt_MTS2++; //счетчик пакетов
	//		FillHeaderTimesMicrosim();
 //       }
		
		int _StartupWinSock() 
		{
			WSADATA WSAData;	
			//Инициализация процесса    
			return WSAStartup (0x202, &WSAData); // 0, если успешно
		}

		int _CleanupWinSock() 
		{    
			return WSACleanup();	
		}

	bool _ConnectMTS(const char* ip, int port)
	{
		int cnnt; 

		bool result = true;

		//Адрес конечной точки, к которому подключение сокет
		struct sockaddr_in Addr;
		Addr.sin_family = AF_INET;    // д.б. AF_INET).
		Addr.sin_port = htons(port); 
		Addr.sin_addr.s_addr = inet_addr(ip);   

		_sct = socket(AF_INET, SOCK_STREAM, 0); 

		if ( _sct < 0 )     
			result = false;
	    
		cnnt = connect( _sct, (sockaddr*)&Addr, sizeof( Addr ) ); 
	    
		if ( cnnt ) 
			result = false;
	    
		return result;
	}

	bool _SocketToMTS()
	{    
		bool result = true;
		int snd;               
	    
		//_sct;
		//Отправка данных на подключенный объек т Socket
		snd = send( _sct, (char*)&msg, sizeof(msg), 0); 
		Sleep(100);
	    
		if ( snd <= 0 ) 
			result = false;   
	    
		return result;
	}

	bool _SocketToMTSMicrosim()
	{    
		bool result = true;
		int snd;               
	    
		//_sct;
		//Отправка данных на подключенный объект Socket
		snd = send( _sct, (char*)&msgMicrosim, sizeof(msgMicrosim), 0); 
		Sleep(100);
	    
		if ( snd <= 0 ) 
			result = false;   
	    
		return result;
	}
};









