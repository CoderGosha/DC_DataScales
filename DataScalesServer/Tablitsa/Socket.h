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
	
			//����������� �� String^ � char*
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

		//1. ��������� ������
		unsigned  short int	len;		   // ����� ���������  ����� short - �����������
		unsigned  short int	id;			   // ID ����������
		unsigned  short int	cnt;		   // ������� ��������� (0..32767)
		unsigned  int	    seconds;	   // ������� ����� 
		unsigned  short int	mseconds;
		unsigned  short int	status;	
		
		//Jaguar1
		int	        nomer1;	    
		int	        ves1;	   //� �� 
        int     counter1; //�������� �������� ������� �������� ����� ���������� ���

		//Jaguar2
		int	        nomer2;	    
		int	        ves2;	   //� �� 
        int     counter2;
		  
		//Jaguar3
		int	        nomer3;	    
		int	        ves3;
        int     counter3; //� �� 

		char        rezerv[222];     // ������

	    
	} msg;

struct MsgTCPMicrosim
	{
		////1. ��������� ������
		//unsigned  short int	len;		   // ����� ���������  ����� short - �����������
		//unsigned  short int	id;			   // ID ����������
		//unsigned  short int	cnt;		   // ������� ��������� (0..32767)
		//unsigned  int	    seconds;	   // ������� ����� 
		//unsigned  short int	mseconds;
		//unsigned  short int	status;	
		

	  //��������1
    int	        nomer1;	    
    int	        ves1;	   //� �� 
	char        stable1;	   //� 
    int         counter1;

	 //��������2
    int	        nomer2;	    
    int	        ves2;	   //� �� 
	char        stable2;	   //� 
    int         counter2;

	//��������3
    int	        nomer3;	    
    int	        ves3;	   //� �� 
	char        stable3;	   //� 
    int         counter3;

     //��������4
    int	        nomer4;	    
    int	        ves4;	   //� �� 
	char        stable4;	   //� 
    int         counter4;

	     //��������6
    int	        nomer5;	    
    int	        ves5;	   //� �� 
	char        stable5;	   //� 
    int         counter5;

	//��������6
    int	        nomer6;	    
    int	        ves6;	   //� �� 
	char        stable6;	   //�
    int         counter6;

		//��������7
    int	        nomer7;	    
    int	        ves7;	   //� �� 
	char        stable7;	   //� 
    int         counter7;

			//��������8
    int	        nomer8;	    
    int	        ves8;	   //� �� 
	char        stable8;	   //� 
    int         counter8;

				//��������9
    int	        nomer9;	    
    int	        ves9;	   //� �� 
	char        stable9;	   //�
    int         counter9;

					//��������9
    int	        nomer10;	    
    int	        ves10;	   //� �� 
	char        stable10;	   //� 
    int         counter10;

    char        rezerv[128];     // ������

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
	        _int64 h100mks = res / 10 / 100; //100���

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
	//        _int64 h100mks = res / 10 / 100; //100���

	//        msgMicrosim.seconds = h100mks / 10000;
	//        msgMicrosim.mseconds = h100mks % 10000;
 //       }
	  
	void FillHeader()
        {

            msg = MsgTCPJaguar(); //�������� ���������
            msg.len = sizeof(msg);
	        msg.id = 1105;
            msg.cnt = TCP_cnt_MTS;         
            TCP_cnt_MTS++; //������� �������
            FillHeaderTimes();
        }

	//void FillHeaderMicrosim()
 //       {

 //           msgMicrosim = MsgTCPMicrosim(); //�������� ���������
 //           msgMicrosim.len = sizeof(msgMicrosim);
	//        msgMicrosim.id = 1106;
 //           msgMicrosim.cnt = TCP_cnt_MTS2;         
 //           TCP_cnt_MTS2++; //������� �������
	//		FillHeaderTimesMicrosim();
 //       }
		
		int _StartupWinSock() 
		{
			WSADATA WSAData;	
			//������������� ��������    
			return WSAStartup (0x202, &WSAData); // 0, ���� �������
		}

		int _CleanupWinSock() 
		{    
			return WSACleanup();	
		}

	bool _ConnectMTS(const char* ip, int port)
	{
		int cnnt; 

		bool result = true;

		//����� �������� �����, � �������� ����������� �����
		struct sockaddr_in Addr;
		Addr.sin_family = AF_INET;    // �.�. AF_INET).
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
		//�������� ������ �� ������������ ����� � Socket
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
		//�������� ������ �� ������������ ������ Socket
		snd = send( _sct, (char*)&msgMicrosim, sizeof(msgMicrosim), 0); 
		Sleep(100);
	    
		if ( snd <= 0 ) 
			result = false;   
	    
		return result;
	}
};









