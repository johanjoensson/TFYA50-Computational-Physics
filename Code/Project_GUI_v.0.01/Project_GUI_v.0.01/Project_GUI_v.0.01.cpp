// Project_GUI_v.0.01.cpp : main project file.

#include "Form1.h"
#include "output.h"
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>

using namespace Project_GUI_v001;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}

System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	world w(5,5,5,0.3,BCC);
//	outputter writer();
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	const char* str = context->marshal_as<const char*>(this->textBox10->Text);
	float co = atof(str);
	if(this->textBox10->Text != ""){
		w.set_cutoff(co);
	}else{
		MessageBox::Show("Cutoff distance not set!");
	}
	w.set_timestep(0.2);
	w.integrate(1000);
	MessageBox::Show("Simulation complete!");
//	delete str;
}
