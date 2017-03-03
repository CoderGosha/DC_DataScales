#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;


ref class CLogCsv
{
private:

    String^ _fileName;
    String^ _currentUser;
    String^ _path;
	String^ oldMessgage;
    void _NewFile(void);
    bool _ActiveFile(void);
	void _RemoveOldFile(void);


public:
    CLogCsv(String^ path);
    bool Weigth(String^ name, String^ wg, bool stab);//Запись веса после прихода от Микросима
    bool RemoteTerminal(bool connect);  
    bool ControlDevice(String^ name, String^ cmd);
    bool Break(String^ name, String^ msg);
    bool Settings(String^ msg);
    bool DataTrack(String^ msg);
	bool getRawMoxa(String^ msg);
	bool sendOracle(String^ msg);

};
