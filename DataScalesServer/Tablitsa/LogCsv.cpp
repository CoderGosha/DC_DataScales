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
    //Создади директорию ЛОГ
    DirectoryInfo^ dir = gcnew DirectoryInfo(_path);
    dir->Create(); ///
   this->_ActiveFile();
   if (!File::Exists(_fileName)) {this->_NewFile();};

   oldMessgage = "";

}


bool CLogCsv::Weigth(String^ name, String ^wg, bool stab){// Запись веса
 try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    String^ temp_stab;
    if (stab) temp_stab = "Стабильный";
    else temp_stab = "Не стабильный";

	//добавлено 03102014
	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "Вес" + ";" + "Весы: " + name + ";Вес:" + wg + ";" + temp_stab ;

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
    if (connect) temp_connect = "Подключился";
    else temp_connect = "Отключился";
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "удаленный_терминал" + ";" + temp_connect ;
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

bool CLogCsv::ControlDevice(System::String ^name, System::String ^cmd){//Управление весами
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "управление" + ";Весы: " + name + ";Команда: " +  cmd;
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

bool CLogCsv::Break(System::String ^name, System::String ^msg){//При обрыве соединения
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
	
	String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "обрыв" + ";Весы: " + name + ";Событие: " +  msg;
	
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

bool CLogCsv::Settings(String^ msg){//Изменение настроек в админке
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "настройка" + ";" +  msg;
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


bool CLogCsv::DataTrack(String^ msg){//Обмен с дата треком
try{
    this->_ActiveFile();
    if (!File::Exists(_fileName)) {this->_NewFile();};
    StreamWriter^ sw = gcnew StreamWriter(_fileName, true, Encoding::GetEncoding(1251));
    String^ temp_str = DateTime::Now + ";" + _currentUser + ";" +  "ДАТА-Трек" + ";" +  msg;
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

void CLogCsv::_NewFile(void){ //Создание нового файла
try{
    	//Если создаем новый файл то и проверим старые на удаление
	this->_RemoveOldFile();
	
	StreamWriter^ sw = gcnew StreamWriter(_fileName, false, Encoding::GetEncoding(1251));
    String^ temp_str = "Дата/Время;Пользователь;Событие;Параметры" ;
    sw->WriteLine(temp_str);
    sw->Close();


}
    catch (System::IO::IOException ^){
    }

    catch (System::UnauthorizedAccessException ^){}
}

bool CLogCsv::_ActiveFile(void){//Проверяет актуальность файла
    DateTime date = DateTime::Now;
    String^ currentFile = _path+ "/" + date.ToString()[0] + "" + date.ToString()[1] + "_" + date.ToString()[3]  + date.ToString()[4] 
    + "" + "_" + date.ToString()[6]  + date.ToString()[7] + ""
    + "" + date.ToString()[8]  + date.ToString()[9] + ".csv";
    
    if (currentFile == _fileName) return 1;
    else {_fileName = currentFile; return 0;}

};

void CLogCsv::_RemoveOldFile(){
//Удаляем старые файлы

	//Получаем список файлов
	array<String^>^ dir = Directory::GetFiles(_path + "/", "*.csv");
	
	System::Collections::IEnumerator^ d = dir->GetEnumerator();
	while (d->MoveNext()) 
	{//
		String^ fileName = static_cast<String^>(d->Current);
		
		//Не удаляем файлы за вчера и позавчера
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