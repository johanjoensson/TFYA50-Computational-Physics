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

System::Void Form1::get_dimensions(int &a, int &b, int &c)
{
	if(this->textBoxXdim->Text != ""){
		a = int::Parse(this->textBoxXdim->Text);
	}else{
		a = 0;
		MessageBox::Show("x-dimension not set!\n0 assumed");
	}
	if(this->textBoxXdim->Text != ""){
		b = int::Parse(this->textBoxYdim->Text);
	}else{
		b = 0;
		MessageBox::Show("y-dimension not set!\n0 assumed");
	}
	if(this->textBoxZdim->Text != ""){
		c = int::Parse(this->textBoxZdim->Text);
	}else{
		c = 0;
		MessageBox::Show("z-dimension not set!\n0 assumed");
	}
}

float Form1::get_lattice_constant()
{
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	const char* str = context->marshal_as<const char*>(this->textBoxLatConst->Text);
	float lc;
	if(this->textBoxLatConst->Text != ""){
		lc = atof(str);
	}else{
		lc = 0;
		MessageBox::Show("Lattice constant not set!\n0 assumed");
	}

	return lc;
}

Input_data Form1::get_data()
{
	Input_data res;
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	const char* str;

	if(this->textBoxXdim->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxXdim->Text);
		res.x = atoi(str);
		delete str;
	}else{
		MessageBox::Show("x-dimensions not set\n0 assumed");
		res.x = 0;
	}
	if(this->textBoxYdim->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxYdim->Text);
		res.y = atoi(str);
		delete str;
	}else{
		MessageBox::Show("y-dimensions not set\n0 assumed");
		res.y = 0;
	}

	if(this->textBoxZdim->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxZdim->Text);
		res.z = atoi(str);
		delete str;
	}else{
		MessageBox::Show("z-dimensions not set\n0 assumed");
		res.z = 0;
	}

	if(this->textBoxLatConst->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxLatConst->Text);
		res.a = atoi(str);
		delete str;
	}else{
		MessageBox::Show("Lattice constant not set\n0 assumed");
		res.a = 0;
	}

	if(this->textBoxCO->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxCO->Text);
		res.cut_off = atoi(str);
		delete str;
	}else{
		MessageBox::Show("Cut off distance not set\n0 assumed");
		res.cut_off = 0;
	}

	if(this->textBoxTStart->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTStart->Text);
		res.t_start = atoi(str);
		delete str;
	}else{
		res.t_start = 0;
	}

	if(this->textBoxTEnd->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTEnd->Text);
		res.t_end = atoi(str);
		delete str;
	}else{
		MessageBox::Show("Number of time steps not set\n2000 assumed");
		res.t_end = 2000;
	}

	if(this->textBoxTStep->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTStep->Text);
		res.t_step = atoi(str);
		delete str;
	}else{
		MessageBox::Show("Time step size not set\n20 assumed");
		res.t_end = 20;
	}

	return res;
}

System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	Input_data d = get_data();
	world w(d.x,d.y,d.z,d.a,FCC);
	w.set_timestep(d.t_step);
	w.integrate(d.t_end);
/*	
	std::ostringstream ss;
	ss << co;
	std::string s(ss.str());
	this->tabPage1->Text = context->marshal_as<System::String^>(s);
*/
	MessageBox::Show("Simulation complete!");
}
