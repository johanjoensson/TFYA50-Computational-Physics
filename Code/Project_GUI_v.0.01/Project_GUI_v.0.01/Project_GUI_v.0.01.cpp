// Project_GUI_v.0.01.cpp : main project file.

#include "Form1.h"
#include "output.h"
#include "input.h"
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>

using namespace Project_GUI_v001;

System::Void Form1::set_materials(unsigned int l)
{

	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();

	this->listBoxMaterial->BeginUpdate();
	for(int i = 0; i < l; i++ ){
		this->listBoxMaterial->Items->Add(context->marshal_as<System::String^>(materials[i].name));
	}
	this->listBoxMaterial->EndUpdate();
}

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

System::Void Form1::checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
{
	this->labelCollisionRate->Visible = !this->labelCollisionRate->Visible;
	this->textBoxCollisionRate->Visible = !this->textBoxCollisionRate->Visible;
}

System::Void Form1::listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
{
	Material mat = selected_material();
	set_defaults(mat);
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

	delete str;
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
		res.a = atof(str);
		delete str;
	}else{
		MessageBox::Show("Lattice constant not set\n0 assumed");
		res.a = 0;
	}

	if(this->textBoxCO->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxCO->Text);
		res.cut_off = atof(str);
		delete str;
	}else{
		MessageBox::Show("Cut off distance not set\n0 assumed");
		res.cut_off = 0;
	}

	if(this->textBoxEpsilon->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxEpsilon->Text);
		res.epsilon = atof(str);
		delete str;
	}else{
		MessageBox::Show("Epsilon not set\n0 assumed");
		res.epsilon = 0;
	}

	if(this->textBoxSigma->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxSigma->Text);
		res.sigma = atof(str);
		delete str;
	}else{
		MessageBox::Show("Sigma not set\n0 assumed");
		res.sigma = 0;
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
		res.t_step = atof(str);
		delete str;
	}else{
		MessageBox::Show("Time step size not set\n20 assumed");
		res.t_end = 20;
	}
	if(this->textBoxTemp->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTemp->Text);
		res.temp = atof(str);
		delete str;
	}else{
		MessageBox::Show("Temperature not set\n20K assumed");
		res.temp = 20;
	}
	return res;
}

float Form1::get_collision_rate()
{
	float res ;
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	const char* str;

	str = context->marshal_as<const char*>(this->textBoxCollisionRate->Text);
	
	res = atof(str);
	if(res > 1.0 || res < 0.0){
		res = 0.20;
		MessageBox::Show("Collision rate not between 0 and 1\n0.20 assumed");
	}
	delete str;

	return res;
}

Material Form1::selected_material()
{
	return materials[this->listBoxMaterial->SelectedIndex];
}

System::Void Form1::set_defaults(Material m)
{
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();

	std::ostringstream ss;

	ss << m.a;
	this->textBoxLatConst->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << 2.5*m.a;
	this->textBoxCO->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << m.sigma;
	this->textBoxSigma->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << m.epsilon;
	this->textBoxEpsilon->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");
}

crystalStructure Form1::get_structure()
{
	crystalStructure res;
	if(this->radioButtonFCC->Checked){
		res = FCC;
	}else if(this->radioButtonBCC->Checked){
		res = BCC;
	}else if(this->radioButtonDiamond->Checked){
		res = DIAMOND;
	}else{
		MessageBox::Show("No crystal structure set!\nFCC assumed");
		res = FCC;
	}
	return res;
}

System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	Material mat = selected_material();

	Input_data d = get_data();
	d.cStruct = get_structure();
	world w(d.x,d.y,d.z,d.a, mat.mass, d.temp,d.cStruct);
	w.set_sigma(mat.sigma);
	w.set_epsilon(mat.epsilon);
	w.set_timestep(d.t_step);
	w.set_cutoff(d.cut_off);

	if(this->checkBoxTermo->Checked){
		w.set_thermostat(true);
		w.set_collision_rate(this->get_collision_rate());
	}

	w.integrate(d.t_end);

	MessageBox::Show("Simulation complete!");
}
