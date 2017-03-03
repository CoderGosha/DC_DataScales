#include "StdAfx.h"
#include "LogCsv.h"

using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Collections;

CLogCsv::CLogCsv(String^ path)
{
    _fileName = "test.csv";
    _currentUser = System::Security::Principal::WindowsIdentity::GetCurrent()->Name;
    _path = path;
    //������� ���������� ���
    DirectoryInfo^ dir = gcnew DirectoryInfo(_path);
    dir->Create(); ///
   this->_ActiveFile();
   if (!File::Exists(_fileName)) {this->_NewFile();};

   oldMessgage = "";

}


bool CLogCsv::Weigth(String^ name, String ^wg, bool stab){// ������ ����
 try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    String^ temp_stab;
    if (stab) temp_stab = "����������";
    else temp_stab = "�� ����������";

	//��������� 03102014
	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "���" + ";" + "����: " + name + ";���:" + wg + ";" + temp_stab ;

	if (temp_str != oldMessgage) {
		StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
		oldMessgage = temp_str;
		sw->WriteLine(temp_str);
		sw->Close();
	}
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }
}


bool CLogCsv::RemoteTerminal(bool connect){
 try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    String^ temp_connect;
    if (connect) temp_connect = "�����������";
    else temp_connect = "����������";
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "���������_��������" + ";" + temp_connect ;
    sw->WriteLine(temp_str);
    sw->Close();
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }

}

bool CLogCsv::ControlDevice(System::String ^name, System::String ^cmd){//���������� ������
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "����������" + ";����: " + name + ";�������: " +  cmd;
    sw->WriteLine(temp_str);
    sw->Close();
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }



};

bool CLogCsv::getRawMoxa(String^ msg){
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};

	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "MOXA" + ";" + "'" + msg + "'";
    
	if (oldMessgage != temp_str) {

	StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    oldMessgage = temp_str;
    sw->WriteLine(temp_str);
    sw->Close();

	}
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }



}

bool CLogCsv::sendOracle(String^ msg){
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};

	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "ORACLE" + ";" + "'" + msg + "'";
    
	if (oldMessgage != temp_str) {

	StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    oldMessgage = temp_str;
    sw->WriteLine(temp_str);
    sw->Close();

	}
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }



}

bool CLogCsv::Break(System::String ^name, System::String ^msg){//��� ������ ����������
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
	
	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "�����" + ";����: " + name + ";�������: " +  msg;
	
	if (oldMessgage != temp_str) {

		StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
	    oldMessgage = temp_str;
		sw->WriteLine(temp_str);
		sw->Close();
	}
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }


}

bool CLogCsv::Settings(String^ msg){//��������� �������� � �������
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "���������" + ";" +  msg;
    sw->WriteLine(temp_str);
    sw->Close();
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }


}


bool CLogCsv::DataTrack(String^ msg){//����� � ���� ������
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "����-����" + ";" +  msg;
    sw->WriteLine(temp_str);
    sw->Close();
    return 1;
    }
    catch (System::IO::IOException ^){
        return 0;
    }

    catch (System::UnauthorizedAccessException ^){
    return 0;
    }

}

void CLogCsv::_NewFile(void){ //�������� ������ �����
try{
    	//���� ������� ����� ���� �� � �������� ������ �� ��������
	this->_RemoveOldFile();
	
	StreamWriter^ sw = gcnew StreamWriter(_fileName, false, Encoding::GetEncoding(1251));
    String^ temp_str = "����/�����;������������;�������;���������" ;
    sw->WriteLine(temp_str);
    sw->Close();


}
    catch (System::IO::IOException ^){
    }

    catch (System::UnauthorizedAccessException ^){}
}

bool CLogCsv::_ActiveFile(void){//��������� ������������ �����
    DateTime date = DateTime::Now;
    String^ currentFile = _path+ "/" + date.ToString()[0] + "" + date.ToString()[1] + "_" + date.ToString()[3]  + date.ToString()[4] 
    + "" + "_" + date.ToString()[6]  + date.ToString()[7] + ""
    + "" + date.ToString()[8]  + date.ToString()[9] + ".csv";
    
    if (currentFile == _fileName) return 1;
    else {_fileName = currentFile; return 0;}

};

void CLogCsv::_RemoveOldFile(){
//������� ������ �����

	//�������� ������ ������
	array<String^>^ dir = Directory::GetFiles(_path + "/", "*.csv");
	
	System::Collections::IEnumerator^ d = dir->GetEnumerator();
	while (d->MoveNext()) 
	{//
		String^ fileName = static_cast<String^>(d->Current);
		
		//�� ������� ����� �� ����� � ���������
		DateTime date = DateTime::Now;
		date = date.AddDays(-1);
		String^ Old1File = _path+ "/" + date.ToString()[0] + "" + date.ToString()[1] + "_" + date.ToString()[3]  + date.ToString()[4]  + "" + "_" + date.ToString()[6]  + date.ToString()[7] + ""  + "" + date.ToString()[8]  + date.ToString()[9] + ".csv";
		date = date.AddDays(-1);
		String^ Old2File = _path+ "/" + date.ToString()[0] + "" + date.ToString()[1] + "_" + date.ToString()[3]  + date.ToString()[4]  + "" + "_" + date.ToString()[6]  + date.ToString()[7] + ""  + "" + date.ToString()[8]  + date.ToString()[9] + ".csv";
		
		try{
			if ((fileName != Old1File) && (fileName != Old2File)) {
				File::Delete(fileName);
			}
		}
		catch (Exception^ e) {


		}
	}



}