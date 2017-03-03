#include <iostream>
#include <winsock2.h>
#include <windows.h>

#include "DataDll.h"
#define MAXMODULE 50

char module[MAXMODULE];

struct MsgHeader
{
	unsigned short int	len;		//aeeia niiauaiey 
	unsigned short int	id;			//ID oaeaa?aiiu
	unsigned short int	cnt;		//n?ao?ee oaeaa?aii (0..32767)
	unsigned int		seconds;	//oaeouaa a?aiy 
	unsigned short int	mseconds;
	unsigned short int	status;	
	unsigned short int	k;	
	char data[108];
} msg;



extern "C" __declspec(dllexport) int sendData(int k){
	WSADATA w;
    
    if (WSAStartup(0x202,&w))
	{
        std::cout << "Error WSA Startup\n";
        WSACleanup ();
    }
	 else 
	 {
        std::cout << " ... WSAStartup - ok\n";
     }
    if (w.wVersion = 0x202)
	{
        std::cout << " ... WSA version 0x202\n";
    }
	 else
	 {
        std::cout << "WSA version != 0x202\n";
        WSACleanup ();
	 }

    int re ; 
    struct sockaddr_in peer;
    peer.sin_family = AF_INET; 
    peer.sin_port = htons(3333); 
    peer.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); 


	if ( s < 0 ) 
        { 
            std::cout << "error socket create\n"; 
        //return 0; 
        } 
        re = connect( s, (sockaddr*)&peer, sizeof( peer ) ); 
        if ( re ) 
        { 
        std::cout << "error connect\n"; 
        //return 0; 
        } 
       

		msg.len = 1024;
		msg.id = 1111;
		msg.cnt++;

		SYSTEMTIME st;
		GetSystemTime(&st);
		FILETIME fst;
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
		FILETIME ftdc;
		SystemTimeToFileTime(&tdc,&ftdc);
		_int64 itdc = *(_int64*)&ftdc;

		_int64 res = ist - itdc;

		_int64 h100mks = res / 10 / 100; //100ien

		msg.seconds = h100mks / 10000;
		msg.mseconds = h100mks % 10000;

		
////////////////////////////////////////////////////////	
	
		msg.k=k;
		//MessageBox(0, (char*)&msg, "ooo", MB_OK);
		re = send( s, (char*)&msg, 1024, 0); 
        
		Sleep(100);
		if ( re <= 0 ) 
        { 
        std::cout << "error send mesage\n";  
       // exit( 1 ); 
			
        }  
		else std::cout<< k << "\n";

		WSACleanup ();
		return re;
}