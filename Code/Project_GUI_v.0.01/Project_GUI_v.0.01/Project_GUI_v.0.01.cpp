// Project_GUI_v.0.01.cpp : main project file.

#include "Form1.h"
#include "output.h"
#include "input.h"
#include "average.h"
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <sstream>
#include <Windows.h>
#include <crtdbg.h>


using namespace Project_GUI_v001;

System::Void Form1::set_materials(unsigned int l)
{

	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();

	this->listBoxMaterial->BeginUpdate();
	for(unsigned int i = 0; i < l; i++ ){
		this->listBoxMaterial->Items->Add(context->marshal_as<System::String^>(materials[i].name));
	}
	this->listBoxMaterial->EndUpdate();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
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

//	delete str;
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
//		delete str;
	}else{
		MessageBox::Show("x-dimensions not set\n0 assumed");
		res.x = 0;
	}
	if(this->textBoxYdim->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxYdim->Text);
		res.y = atoi(str);
//		delete str;
	}else{
		MessageBox::Show("y-dimensions not set\n0 assumed");
		res.y = 0;
	}

	if(this->textBoxZdim->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxZdim->Text);
		res.z = atoi(str);
//		delete str;
	}else{
		MessageBox::Show("z-dimensions not set\n0 assumed");
		res.z = 0;
	}

	if(this->textBoxLatConst->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxLatConst->Text);
		res.a = atof(str);
//		delete str;
	}else{
		MessageBox::Show("Lattice constant not set\n0 assumed");
		res.a = 0;
	}

	if(this->textBoxCO->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxCO->Text);
		res.cut_off = atof(str);
//		delete str;
	}else{
		MessageBox::Show("Cut off distance not set\n0 assumed");
		res.cut_off = 0;
	}

	if(this->textBoxEpsilon->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxEpsilon->Text);
		res.epsilon = atof(str);
//		delete str;
	}else{
		MessageBox::Show("Epsilon not set\n0 assumed");
		res.epsilon = 0;
	}

	if(this->textBoxSigma->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxSigma->Text);
		res.sigma = atof(str);
//		delete str;
	}else{
		MessageBox::Show("Sigma not set\n0 assumed");
		res.sigma = 0;
	}

	if(this->textBoxTStart->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTStart->Text);
		res.t_start = atoi(str);
//		delete str;
	}else{
		res.t_start = 0;
	}

	if(this->textBoxTEnd->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTEnd->Text);
		res.t_end = atoi(str);
//		delete str;
	}else{
		MessageBox::Show("Number of time steps not set\n2000 assumed");
		res.t_end = 2000;
	}

	if(this->textBoxTStep->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTStep->Text);
		res.t_step = atof(str);
//		delete str;
	}else{
		MessageBox::Show("Time step size not set\n20 assumed");
		res.t_step = 20;
	}
	if(this->textBoxTemp->Text != ""){
		str = context->marshal_as<const char*>(this->textBoxTemp->Text);
		res.temp = atof(str);
//		delete str;
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
//	delete str;

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

System::Void Form1::set_information(Material m, Input_data d, int N)
{
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	std::ostringstream ss;

	ss << "Material : " << m.name << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Mass of each atom : " << m.mass << "u" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Number of atoms in bulk : " << N << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Unit cells in - x: " << d.x << ", y: " << d.y << ", z: " << d.z << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Lattice constant : " << d.a << "Å" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Sigma : " << d.sigma << "Å, epsilon : " << d.epsilon << "eV, cutoff distance: " << d.cut_off << "Å" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Crystal structure :" ;
	switch(d.cStruct){
	case FCC:
		ss << " FCC";
		break;
	case BCC:
		ss << " BCC";
		break;
	case DIAMOND:
		ss << " Diamond";
		break;
	}
	ss << std::endl;

	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");
	
	ss << "Starting simulation at : " << d.temp << "K" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Running for " << d.t_end << " timesteps," << " with a timestep of " << d.t_step << "fs" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << "Calculations of average properties will begin after " << d.t_start << " timesteps" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss << std::endl << "-----------------------------------------------------------------------------------------------------------";
	ss << std::endl;

	ss << "\tStarting simulation! Live Long and prosper!" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	this->richTextBoxResults->Refresh();

}

float* get_averages(int t_start, int t_end)
{
	float *data;

	data = averageValue(t_start, t_end);

	return data;
}



System::Void Form1::set_end_of_simulation(Input_data d, clock_t time)
{
	msclr::interop::marshal_context ^ context = gcnew msclr::interop::marshal_context();
	std::ostringstream ss;

	ss <<std::endl << "\tPeace and long life!" << std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	float total_time = ((float)time)/CLOCKS_PER_SEC;
	ss <<std::endl << "The simulation took " << total_time << " seconds" <<  std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	ss <<"Which means " << (float) total_time/d.t_end << " seconds per time step" <<  std::endl;
	this->richTextBoxResults->AppendText(context->marshal_as<System::String^>(ss.str()));
	ss.clear();
	ss.str("");

	float* res;
	res = averageValue(d.t_start, d.t_end);

	ss << res[0];
	this->textBoxEKin->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[1];
	this->textBoxEPot->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");
	
	ss << res[2];
	this->textBoxETot->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[3];
	this->textBoxECoh->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[4];
	this->textBoxMSD->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[5];
	this->textBoxIntP->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[6];
	this->textBoxResTemp->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[7];
	this->textBoxDebTemp->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[8];
	this->textBoxSpecHeat->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	ss << res[9];
	this->textBoxDiffCo->Text = context->marshal_as<System::String^>(ss.str());
	ss.clear();
	ss.str("");

	this->richTextBoxResults->Refresh();
	delete res;
}

System::Void Form1::reset_results()
{
	this->richTextBoxResults->Clear();
	this->textBoxEKin->Clear();
	this->textBoxEPot->Clear();
	this->textBoxETot->Clear();
	this->textBoxECoh->Clear();
	this->textBoxMSD->Clear();
	this->textBoxIntP->Clear();
	this->textBoxResTemp->Clear();
	this->textBoxDebTemp->Clear();
	this->textBoxSpecHeat->Clear();
	this->textBoxDiffCo->Clear();

	this->richTextBoxResults->Refresh();
	this->textBoxEKin->Refresh();
	this->textBoxEPot->Refresh();
	this->textBoxETot->Refresh();
	this->textBoxECoh->Refresh();
	this->textBoxMSD->Refresh();
	this->textBoxIntP->Refresh();
	this->textBoxResTemp->Refresh();
	this->textBoxDebTemp->Refresh();
	this->textBoxSpecHeat->Refresh();
	this->textBoxDiffCo->Refresh();
}

System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	reset_results();
	Material mat;
	if(this->listBoxMaterial->SelectedIndex == -1){
		MessageBox::Show("No material selected!\nChoosing the first material in the list.");
		mat = materials[0];
	}else{
		mat = selected_material();
	}

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
	if(this->checkBoxVisualise->Checked){
		w.set_visualisation(true);
	}

	set_information(mat, d, w.N);
	clock_t time = clock();
	w.integrate(d.t_end);

	w.unset_world();
	time = clock() - time;
	set_end_of_simulation(d, time);

	MessageBox::Show("Simulation complete!");
}
