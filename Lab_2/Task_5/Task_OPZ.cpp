#include "Task_OPZ.h"

using namespace System;
using namespace System::Windows::Forms;


int main(array <String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Task5::Task_OPZ opz;
	Application::Run(% opz);
}

