#include "StdAfx.h"
#include "DataTrack.h"

#include "Socket.h"

using namespace System::Runtime::InteropServices;

using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Collections;

CDataTrack::CDataTrack(List<CWeight^>^ weigth, String^ ip, Int32 timeOut, Int32 portMicrosim, Int32 portJaguar, Int32 NomerDT):
_ip(ip),
_timeOut(timeOut),
_portJaguar(portJaguar),
_portMicrosim(portMicrosim)
{
_weigth = weigth;

cnt_jaguar = 0;
statusJaguar = 0;
statusMicrosim = 0;
counterJaguar = 0;
counterMicrosim = 0;
_NomerDT = NomerDT;

for each(CWeight^ elem in _weigth) {
			//Обход по всем весам
			if (elem->getTypeScales() == "Jaguar/TCPIP" )
			{
				counterJaguar++;
			}
			else if (elem->getTypeScales() == "Microsim/RealCom" ) 
			{
				counterMicrosim++;
			}

			else if (elem->getTypeScales() == "Microsim/TCPIP" )
			{
				counterMicrosim++;
			}
			else if (elem->getTypeScales() == "WE2120_ST/TCPIP" )
			{
				counterMicrosim++;
			}
			else if (elem->getTypeScales() == "WE2120_ALT/TCPIP" )
			{
				counterMicrosim++;
			}
			else if (elem->getTypeScales() == "DISOMAT_SATUS/TCPIP" )
			{
				counterMicrosim++;
			}
			else if (elem->getTypeScales() == "DATASCALES_REPEATER" )
			{
				counterMicrosim++;
			}


			
}//for earch
	if (counterJaguar){
		//Создаем подключение к ССМ для ягуаров

	}
	if (counterMicrosim) {
		_sendMicrosim = 1;
		sendMicrosimThread = gcnew Thread(gcnew ThreadStart(this, &CDataTrack::_sendMicrosimWork));
		sendMicrosimThread->Start();
	}
	
}

CDataTrack::~CDataTrack(){
	if (counterJaguar) {

	}
	if (counterMicrosim) {
		_sendMicrosim = 0;
		sendMicrosimThread->Join();
		delete sendMicrosimThread;
	}
}

void CDataTrack::Send(){
ts->FillHeader();
ts->msg.nomer1 = 78;
ts->msg.ves1 = 79;
ts->_SocketToMTS();

};

void CDataTrack::_sendJaguarWork(){


	ts = new ConnectSSM(_ip, _portJaguar);
	statusJaguar = ts->status;
	//Отправка данных в SSM()
	while (_sendJaguar){
		Thread::Sleep(_timeOut);
		ts->FillHeader();
		
		//Обнуляем
	
	/*	ts->msg.ves1 = 0;
		ts->msg.ves2 = 0;
		ts->msg.ves3 = 0;
		ts->msg.nomer1 = 0;
		ts->msg.nomer2 = 0;
		ts->msg.nomer3 = 0;
		
	*/	///*/*/*/
		for each(CWeight^ elem in _weigth) {
			//Обход по всем весам
			if (elem->getTypeScales() == "Jaguar/TCPIP" ){
				//Если ягуар то, проверяем номер в которой доллжнеа будет отрпавлятся посылка
				
									
				switch (elem->getNomerSSM())
				{
				case 1 :
					{//Для первого устройства
					ts->msg.nomer1 = Int32::Parse(elem->name);
					//ts->msg.nomer1 = 55;
					try{
					
                        ts->msg.counter1 = elem->getCounterVes();
						ts->msg.ves1 = Int32::Parse(elem->weight);
					}
					catch (Exception^){
						ts->msg.ves1 = 0;
					}
					break;

					}

				case 2 :
					{//
					ts->msg.nomer2 = Int32::Parse(elem->name);
					try{
					
						ts->msg.counter2 = elem->getCounterVes();
                        ts->msg.ves2 = Int32::Parse(elem->weight);
					}
					catch (Exception^ ){
						ts->msg.ves2 = 0;
					}
					break;

					}

				case 3 :
					{//
					ts->msg.nomer3 = Int32::Parse(elem->name);
					try{
					
						ts->msg.counter3 = elem->getCounterVes();
                        ts->msg.ves3 = Int32::Parse(elem->weight);
					}
					catch (Exception^ ){
						ts->msg.ves3 = 0;
					}
					break;

					}

				}

			}

		}

		statusJaguar = ts->_SocketToMTS();
		if (!statusJaguar)
		{	delete ts;
			Thread::Sleep(500);
			ts = new ConnectSSM(_ip, _portJaguar);
			statusJaguar = ts->status;
		}
	}//while


};




void CDataTrack::_sendMicrosimWork(){

	tsM = new ConnectSSM(_ip, _portMicrosim);
	statusMicrosim = tsM->status;
	//Отправка данных в SSM()
	while (_sendMicrosim){
try{	
		Thread::Sleep(_timeOut);
		//tsM->FillHeaderMicrosim();
		
		//Обнуляем
	//*/*/*/**/*/*/*///////
	/*	tsM->msgMicrosim.ves1 = 0;
		tsM->msgMicrosim.ves2 = 0;
		tsM->msgMicrosim.ves3 = 0;
		tsM->msgMicrosim.ves4 = 0;
		tsM->msgMicrosim.ves5 = 0;
		tsM->msgMicrosim.ves6 = 0;
		tsM->msgMicrosim.ves7 = 0;
		tsM->msgMicrosim.ves8 = 0;
		tsM->msgMicrosim.ves9 = 0;
		tsM->msgMicrosim.ves10 = 0;
		tsM->msgMicrosim.nomer1 = 0;
		tsM->msgMicrosim.nomer2 = 0;
		tsM->msgMicrosim.nomer3 = 0;
		tsM->msgMicrosim.nomer4 = 0;
		tsM->msgMicrosim.nomer5 = 0;
		tsM->msgMicrosim.nomer6 = 0;
		tsM->msgMicrosim.nomer7 = 0;
		tsM->msgMicrosim.nomer8 = 0;
		tsM->msgMicrosim.nomer9 = 0;
		tsM->msgMicrosim.nomer10 = 0;
		tsM->msgMicrosim.stable1 = 0;
		tsM->msgMicrosim.stable2 = 0;
		tsM->msgMicrosim.stable3 = 0;
		tsM->msgMicrosim.stable4 = 0;
		tsM->msgMicrosim.stable5 = 0;
		tsM->msgMicrosim.stable6 = 0;
		tsM->msgMicrosim.stable7 = 0;
		tsM->msgMicrosim.stable8 = 0;
		tsM->msgMicrosim.stable9 = 0;
		tsM->msgMicrosim.stable10 = 0;
		*/ 
		///*//*/

		for each(CWeight^ elem in _weigth) {
			//Обход по всем весам
			if (((elem->getTypeScales() == "Microsim/TCPIP" ) || 
				(elem->getTypeScales() == "WE2120_ST/TCPIP") ||
				(elem->getTypeScales() == "WE2120_ALT/TCPIP" ) ||
				(elem->getTypeScales() == "DATASCALES_REPEATER" ) ||
				(elem->getTypeScales() == "DISOMAT_SATUS/TCPIP" )
				) && (elem->DataTrackIP == _ip))
			{
				//Если микросим
				switch (elem->getNomerSSM())
				{
				case 1:
					{//Для первого устройства
							tsM->msgMicrosim.nomer1 = Int32::Parse(elem->name);
						try{
							tsM->msgMicrosim.ves1 = elem->getVesMicrosim();
                            tsM->msgMicrosim.counter1 = elem->getCounterVes();
							tsM->msgMicrosim.stable1 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves1 = 0;
						}
						break;

					}
				case 2:
					{//Для первого устройства
							tsM->msgMicrosim.nomer2 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter2 = elem->getCounterVes();
							tsM->msgMicrosim.ves2 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable2 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves2 = 0;
						}
						break;

					}
				case 3:
					{//Для первого устройства
							tsM->msgMicrosim.nomer3 = Int32::Parse(elem->name);
						try{
						
							tsM->msgMicrosim.counter3 = elem->getCounterVes();
                            tsM->msgMicrosim.ves3 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable3 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves3 = 0;
						}
						break;

					}
				case 4:
					{//Для первого устройства
							tsM->msgMicrosim.nomer4 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter4 = elem->getCounterVes();
							tsM->msgMicrosim.ves4 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable4 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves4 = 0;
						}
						break;

					}
			case 5:
					{//Для первого устройства
							tsM->msgMicrosim.nomer5 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter5 = elem->getCounterVes();
							tsM->msgMicrosim.ves5 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable5 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves5 = 0;
						}
						break;

					}

				case 6:
					{//Для первого устройства
							tsM->msgMicrosim.nomer6 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter6 = elem->getCounterVes();
							tsM->msgMicrosim.ves6 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable6 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves6 = 0;
						}
						break;

					}
				case 7:
					{//Для первого устройства
							tsM->msgMicrosim.nomer7 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter7 = elem->getCounterVes();
							tsM->msgMicrosim.ves7 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable7 = elem->ind_stabil;

						}
						catch (Exception^){
							tsM->msgMicrosim.ves7 = 0;
						}
						break;

					}

				case 8:
					{//Для первого устройства
							tsM->msgMicrosim.nomer8 = Int32::Parse(elem->name);
						try{
						    tsM->msgMicrosim.counter8 = elem->getCounterVes();
							tsM->msgMicrosim.ves8 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable8 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves8 = 0;
						}
						break;

					}
				case 9:
					{//Для первого устройства
							tsM->msgMicrosim.nomer9 = Int32::Parse(elem->name);
						try{
						   tsM->msgMicrosim.counter9 = elem->getCounterVes();
							tsM->msgMicrosim.ves9 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable9 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves9 = 0;
						}
						break;

					}
				case 10:
					{//Для первого устройства
							tsM->msgMicrosim.nomer10 = Int32::Parse(elem->name);
						try{
						   tsM->msgMicrosim.counter10 = elem->getCounterVes();
							tsM->msgMicrosim.ves10 = elem->getVesMicrosim();
							tsM->msgMicrosim.stable10 = elem->ind_stabil;

						}
						catch (Exception^ ){
							tsM->msgMicrosim.ves10 = 0;
						}
						break;

					}
				}

			}

		}



		statusMicrosim = tsM->_SocketToMTSMicrosim();

		if (!statusMicrosim)
		{	delete tsM;
			Thread::Sleep(500);
			tsM = new ConnectSSM(_ip, _portMicrosim);
			statusMicrosim = tsM->status;
		}
}
			catch (Exception ^) {

	}
	}//while*/


};