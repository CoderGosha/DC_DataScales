// Tablitsa.cpp : main project file.

#include "stdafx.h"
#include "MainForm.h"

using namespace Tablitsa;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	//Реализация запуска одной копии

	Mutex^ m = gcnew Mutex();
			
	try{
		m->OpenExisting("SSM_VESY");
		MessageBox::Show("Программа весоизмерения уже запущена", "Повторный запуск",  MessageBoxButtons::OK, MessageBoxIcon::Error);	
		//return;
	}
	catch (WaitHandleCannotBeOpenedException^ e) {
		delete m;
		m = gcnew Mutex(true, "SSM_VESY");
		Application::Run(gcnew MainForm());
	}
	finally {
		delete m;
	}
	return 0;
}
