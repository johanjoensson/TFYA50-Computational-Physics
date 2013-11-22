#pragma once
#include "world.h"
#include "input.h"

struct Input_data{
	int x;
	int y;
	int z;
	float a;
	float epsilon;
	float sigma;
	float temp;
	float cut_off;
	int t_start;
	int t_end;
	float t_step;
	crystalStructure cStruct;
} in_data_t;

namespace Project_GUI_v001 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Material* materials;

		Form1(void)
		{
			InitializeComponent();
			inputter input("materials.txt");
			materials = input.get_material("materials.txt");
			set_materials(input.num_mat);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPageStructure;
	protected: 

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::RadioButton^  radioButtonBCC;

	private: System::Windows::Forms::RadioButton^  radioButtonFCC;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxCO;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxLatConst;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPageCalculation;
	private: System::Windows::Forms::TextBox^  textBoxTStep;






	private: System::Windows::Forms::TextBox^  textBoxTEnd;

	private: System::Windows::Forms::TextBox^  textBoxTStart;
	private: System::Windows::Forms::CheckBox^  checkBoxTermo;






	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TabPage^  tabPageResult;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBoxResults;
	private: System::Windows::Forms::TextBox^  textBoxDebTemp;
	private: System::Windows::Forms::TextBox^  textBoxResTemp;




	private: System::Windows::Forms::TextBox^  textBoxMSD;

	private: System::Windows::Forms::TextBox^  textBoxECoh;

	private: System::Windows::Forms::TextBox^  textBoxETot;

	private: System::Windows::Forms::TextBox^  textBoxEPot;

	private: System::Windows::Forms::TextBox^  textBoxEKin;
	private: System::Windows::Forms::Label^  labelDebTemp;


	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::CheckBox^  checkBoxVisualise;

	private: System::Windows::Forms::TextBox^  textBoxZdim;

	private: System::Windows::Forms::TextBox^  textBoxYdim;

	private: System::Windows::Forms::TextBox^  textBoxXdim;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::RadioButton^  radioButtonDiamond;

	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::ListBox^  listBoxMaterial;
	private: System::Windows::Forms::TextBox^  textBoxEpsilon;


	private: System::Windows::Forms::Label^  labelEpsilon;

	private: System::Windows::Forms::TextBox^  textBoxSigma;

	private: System::Windows::Forms::Label^  labelSigma;

	private: System::Windows::Forms::TextBox^  textBoxCollisionRate;

	private: System::Windows::Forms::Label^  labelCollisionRate;
private: System::Windows::Forms::TextBox^  textBoxHeatCap;

private: System::Windows::Forms::Label^  labelHeatCap;
private: System::Windows::Forms::TextBox^  textBoxTemp;

private: System::Windows::Forms::Label^  label9;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->listBoxMaterial = (gcnew System::Windows::Forms::ListBox());
			this->tabPageStructure = (gcnew System::Windows::Forms::TabPage());
			this->textBoxEpsilon = (gcnew System::Windows::Forms::TextBox());
			this->labelEpsilon = (gcnew System::Windows::Forms::Label());
			this->textBoxSigma = (gcnew System::Windows::Forms::TextBox());
			this->labelSigma = (gcnew System::Windows::Forms::Label());
			this->radioButtonDiamond = (gcnew System::Windows::Forms::RadioButton());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBoxZdim = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYdim = (gcnew System::Windows::Forms::TextBox());
			this->textBoxXdim = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButtonBCC = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonFCC = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxCO = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxLatConst = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPageCalculation = (gcnew System::Windows::Forms::TabPage());
			this->textBoxTemp = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBoxCollisionRate = (gcnew System::Windows::Forms::TextBox());
			this->labelCollisionRate = (gcnew System::Windows::Forms::Label());
			this->checkBoxVisualise = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxTStep = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTEnd = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTStart = (gcnew System::Windows::Forms::TextBox());
			this->checkBoxTermo = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tabPageResult = (gcnew System::Windows::Forms::TabPage());
			this->textBoxHeatCap = (gcnew System::Windows::Forms::TextBox());
			this->labelHeatCap = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBoxResults = (gcnew System::Windows::Forms::RichTextBox());
			this->textBoxDebTemp = (gcnew System::Windows::Forms::TextBox());
			this->textBoxResTemp = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMSD = (gcnew System::Windows::Forms::TextBox());
			this->textBoxECoh = (gcnew System::Windows::Forms::TextBox());
			this->textBoxETot = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEPot = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEKin = (gcnew System::Windows::Forms::TextBox());
			this->labelDebTemp = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPageStructure->SuspendLayout();
			this->tabPageCalculation->SuspendLayout();
			this->tabPageResult->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPageStructure);
			this->tabControl1->Controls->Add(this->tabPageCalculation);
			this->tabControl1->Controls->Add(this->tabPageResult);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(636, 450);
			this->tabControl1->TabIndex = 2;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->listBoxMaterial);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(628, 424);
			this->tabPage1->TabIndex = 3;
			this->tabPage1->Text = L"Material";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// listBoxMaterial
			// 
			this->listBoxMaterial->FormattingEnabled = true;
			this->listBoxMaterial->Location = System::Drawing::Point(0, 8);
			this->listBoxMaterial->Name = L"listBoxMaterial";
			this->listBoxMaterial->Size = System::Drawing::Size(628, 407);
			this->listBoxMaterial->TabIndex = 1;
			this->listBoxMaterial->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBox1_SelectedIndexChanged);
			// 
			// tabPageStructure
			// 
			this->tabPageStructure->Controls->Add(this->textBoxEpsilon);
			this->tabPageStructure->Controls->Add(this->labelEpsilon);
			this->tabPageStructure->Controls->Add(this->textBoxSigma);
			this->tabPageStructure->Controls->Add(this->labelSigma);
			this->tabPageStructure->Controls->Add(this->radioButtonDiamond);
			this->tabPageStructure->Controls->Add(this->label19);
			this->tabPageStructure->Controls->Add(this->textBoxZdim);
			this->tabPageStructure->Controls->Add(this->textBoxYdim);
			this->tabPageStructure->Controls->Add(this->textBoxXdim);
			this->tabPageStructure->Controls->Add(this->label12);
			this->tabPageStructure->Controls->Add(this->label11);
			this->tabPageStructure->Controls->Add(this->label10);
			this->tabPageStructure->Controls->Add(this->label4);
			this->tabPageStructure->Controls->Add(this->radioButtonBCC);
			this->tabPageStructure->Controls->Add(this->radioButtonFCC);
			this->tabPageStructure->Controls->Add(this->label3);
			this->tabPageStructure->Controls->Add(this->textBoxCO);
			this->tabPageStructure->Controls->Add(this->label2);
			this->tabPageStructure->Controls->Add(this->textBoxLatConst);
			this->tabPageStructure->Controls->Add(this->label1);
			this->tabPageStructure->Location = System::Drawing::Point(4, 22);
			this->tabPageStructure->Name = L"tabPageStructure";
			this->tabPageStructure->Padding = System::Windows::Forms::Padding(3);
			this->tabPageStructure->Size = System::Drawing::Size(628, 424);
			this->tabPageStructure->TabIndex = 0;
			this->tabPageStructure->Text = L"Structure";
			this->tabPageStructure->UseVisualStyleBackColor = true;
			// 
			// textBoxEpsilon
			// 
			this->textBoxEpsilon->Location = System::Drawing::Point(150, 120);
			this->textBoxEpsilon->Name = L"textBoxEpsilon";
			this->textBoxEpsilon->Size = System::Drawing::Size(87, 20);
			this->textBoxEpsilon->TabIndex = 44;
			this->textBoxEpsilon->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// labelEpsilon
			// 
			this->labelEpsilon->AutoSize = true;
			this->labelEpsilon->Location = System::Drawing::Point(7, 124);
			this->labelEpsilon->Name = L"labelEpsilon";
			this->labelEpsilon->Size = System::Drawing::Size(41, 13);
			this->labelEpsilon->TabIndex = 43;
			this->labelEpsilon->Text = L"Epsilon";
			this->labelEpsilon->Click += gcnew System::EventHandler(this, &Form1::label20_Click);
			// 
			// textBoxSigma
			// 
			this->textBoxSigma->Location = System::Drawing::Point(150, 92);
			this->textBoxSigma->Name = L"textBoxSigma";
			this->textBoxSigma->Size = System::Drawing::Size(87, 20);
			this->textBoxSigma->TabIndex = 42;
			// 
			// labelSigma
			// 
			this->labelSigma->AutoSize = true;
			this->labelSigma->Location = System::Drawing::Point(7, 98);
			this->labelSigma->Name = L"labelSigma";
			this->labelSigma->Size = System::Drawing::Size(36, 13);
			this->labelSigma->TabIndex = 41;
			this->labelSigma->Text = L"Sigma";
			// 
			// radioButtonDiamond
			// 
			this->radioButtonDiamond->AutoSize = true;
			this->radioButtonDiamond->Location = System::Drawing::Point(191, 331);
			this->radioButtonDiamond->Name = L"radioButtonDiamond";
			this->radioButtonDiamond->Size = System::Drawing::Size(67, 17);
			this->radioButtonDiamond->TabIndex = 40;
			this->radioButtonDiamond->TabStop = true;
			this->radioButtonDiamond->Text = L"Diamond";
			this->radioButtonDiamond->UseVisualStyleBackColor = true;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(13, 173);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(71, 13);
			this->label19->TabIndex = 39;
			this->label19->Text = L"Dimensions";
			// 
			// textBoxZdim
			// 
			this->textBoxZdim->Location = System::Drawing::Point(150, 263);
			this->textBoxZdim->Name = L"textBoxZdim";
			this->textBoxZdim->Size = System::Drawing::Size(87, 20);
			this->textBoxZdim->TabIndex = 38;
			this->textBoxZdim->TextChanged += gcnew System::EventHandler(this, &Form1::textBox7_TextChanged);
			// 
			// textBoxYdim
			// 
			this->textBoxYdim->Location = System::Drawing::Point(150, 230);
			this->textBoxYdim->Name = L"textBoxYdim";
			this->textBoxYdim->Size = System::Drawing::Size(87, 20);
			this->textBoxYdim->TabIndex = 37;
			// 
			// textBoxXdim
			// 
			this->textBoxXdim->Location = System::Drawing::Point(150, 197);
			this->textBoxXdim->Name = L"textBoxXdim";
			this->textBoxXdim->Size = System::Drawing::Size(87, 20);
			this->textBoxXdim->TabIndex = 36;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(7, 233);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(129, 13);
			this->label12->TabIndex = 35;
			this->label12->Text = L"Nb. of atoms in y direction";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(7, 266);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(129, 13);
			this->label11->TabIndex = 34;
			this->label11->Text = L"Nb. of atoms in z direction";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(7, 200);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(129, 13);
			this->label10->TabIndex = 33;
			this->label10->Text = L"Nb. of atoms in x direction";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(13, 301);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(101, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Crystal Structure";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// radioButtonBCC
			// 
			this->radioButtonBCC->AutoSize = true;
			this->radioButtonBCC->Location = System::Drawing::Point(100, 331);
			this->radioButtonBCC->Name = L"radioButtonBCC";
			this->radioButtonBCC->Size = System::Drawing::Size(46, 17);
			this->radioButtonBCC->TabIndex = 19;
			this->radioButtonBCC->TabStop = true;
			this->radioButtonBCC->Text = L"BCC";
			this->radioButtonBCC->UseVisualStyleBackColor = true;
			// 
			// radioButtonFCC
			// 
			this->radioButtonFCC->AutoSize = true;
			this->radioButtonFCC->Location = System::Drawing::Point(10, 331);
			this->radioButtonFCC->Name = L"radioButtonFCC";
			this->radioButtonFCC->Size = System::Drawing::Size(45, 17);
			this->radioButtonFCC->TabIndex = 18;
			this->radioButtonFCC->TabStop = true;
			this->radioButtonFCC->Text = L"FCC";
			this->radioButtonFCC->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 219);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 16;
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// textBoxCO
			// 
			this->textBoxCO->Location = System::Drawing::Point(150, 64);
			this->textBoxCO->Name = L"textBoxCO";
			this->textBoxCO->Size = System::Drawing::Size(87, 20);
			this->textBoxCO->TabIndex = 15;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(80, 13);
			this->label2->TabIndex = 14;
			this->label2->Text = L"Cutoff Distance";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// textBoxLatConst
			// 
			this->textBoxLatConst->Location = System::Drawing::Point(150, 36);
			this->textBoxLatConst->Name = L"textBoxLatConst";
			this->textBoxLatConst->Size = System::Drawing::Size(87, 20);
			this->textBoxLatConst->TabIndex = 13;
			this->textBoxLatConst->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Lattice Constant";
			// 
			// tabPageCalculation
			// 
			this->tabPageCalculation->Controls->Add(this->textBoxTemp);
			this->tabPageCalculation->Controls->Add(this->label9);
			this->tabPageCalculation->Controls->Add(this->textBoxCollisionRate);
			this->tabPageCalculation->Controls->Add(this->labelCollisionRate);
			this->tabPageCalculation->Controls->Add(this->checkBoxVisualise);
			this->tabPageCalculation->Controls->Add(this->textBoxTStep);
			this->tabPageCalculation->Controls->Add(this->textBoxTEnd);
			this->tabPageCalculation->Controls->Add(this->textBoxTStart);
			this->tabPageCalculation->Controls->Add(this->checkBoxTermo);
			this->tabPageCalculation->Controls->Add(this->label5);
			this->tabPageCalculation->Controls->Add(this->label6);
			this->tabPageCalculation->Controls->Add(this->label7);
			this->tabPageCalculation->Location = System::Drawing::Point(4, 22);
			this->tabPageCalculation->Name = L"tabPageCalculation";
			this->tabPageCalculation->Padding = System::Windows::Forms::Padding(3);
			this->tabPageCalculation->Size = System::Drawing::Size(628, 424);
			this->tabPageCalculation->TabIndex = 1;
			this->tabPageCalculation->Text = L"Calculations";
			this->tabPageCalculation->UseVisualStyleBackColor = true;
			// 
			// textBoxTemp
			// 
			this->textBoxTemp->Location = System::Drawing::Point(448, 80);
			this->textBoxTemp->Name = L"textBoxTemp";
			this->textBoxTemp->Size = System::Drawing::Size(87, 20);
			this->textBoxTemp->TabIndex = 38;
			this->textBoxTemp->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(362, 83);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(67, 13);
			this->label9->TabIndex = 37;
			this->label9->Text = L"Temperature";
			this->label9->Click += gcnew System::EventHandler(this, &Form1::label9_Click);
			// 
			// textBoxCollisionRate
			// 
			this->textBoxCollisionRate->Location = System::Drawing::Point(448, 40);
			this->textBoxCollisionRate->Name = L"textBoxCollisionRate";
			this->textBoxCollisionRate->Size = System::Drawing::Size(87, 20);
			this->textBoxCollisionRate->TabIndex = 36;
			this->textBoxCollisionRate->Visible = false;
			// 
			// labelCollisionRate
			// 
			this->labelCollisionRate->AutoSize = true;
			this->labelCollisionRate->Location = System::Drawing::Point(362, 43);
			this->labelCollisionRate->Name = L"labelCollisionRate";
			this->labelCollisionRate->Size = System::Drawing::Size(66, 13);
			this->labelCollisionRate->TabIndex = 35;
			this->labelCollisionRate->Text = L"Collision rate";
			this->labelCollisionRate->Visible = false;
			// 
			// checkBoxVisualise
			// 
			this->checkBoxVisualise->AutoSize = true;
			this->checkBoxVisualise->Location = System::Drawing::Point(9, 123);
			this->checkBoxVisualise->Name = L"checkBoxVisualise";
			this->checkBoxVisualise->Size = System::Drawing::Size(121, 17);
			this->checkBoxVisualise->TabIndex = 34;
			this->checkBoxVisualise->Text = L"Include visualisation";
			this->checkBoxVisualise->UseVisualStyleBackColor = true;
			this->checkBoxVisualise->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// textBoxTStep
			// 
			this->textBoxTStep->Location = System::Drawing::Point(198, 79);
			this->textBoxTStep->Name = L"textBoxTStep";
			this->textBoxTStep->Size = System::Drawing::Size(87, 20);
			this->textBoxTStep->TabIndex = 29;
			// 
			// textBoxTEnd
			// 
			this->textBoxTEnd->Location = System::Drawing::Point(198, 48);
			this->textBoxTEnd->Name = L"textBoxTEnd";
			this->textBoxTEnd->Size = System::Drawing::Size(87, 20);
			this->textBoxTEnd->TabIndex = 28;
			// 
			// textBoxTStart
			// 
			this->textBoxTStart->Location = System::Drawing::Point(198, 17);
			this->textBoxTStart->Name = L"textBoxTStart";
			this->textBoxTStart->Size = System::Drawing::Size(87, 20);
			this->textBoxTStart->TabIndex = 27;
			// 
			// checkBoxTermo
			// 
			this->checkBoxTermo->AutoSize = true;
			this->checkBoxTermo->Location = System::Drawing::Point(365, 16);
			this->checkBoxTermo->Name = L"checkBoxTermo";
			this->checkBoxTermo->Size = System::Drawing::Size(79, 17);
			this->checkBoxTermo->TabIndex = 26;
			this->checkBoxTermo->Text = L"Thermostat";
			this->checkBoxTermo->UseVisualStyleBackColor = true;
			this->checkBoxTermo->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 83);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(71, 13);
			this->label5->TabIndex = 19;
			this->label5->Text = L"Timestep size";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 52);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(99, 13);
			this->label6->TabIndex = 18;
			this->label6->Text = L"Run for # timesteps";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 20);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(169, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"Start calculations after # timesteps";
			// 
			// tabPageResult
			// 
			this->tabPageResult->Controls->Add(this->textBoxHeatCap);
			this->tabPageResult->Controls->Add(this->labelHeatCap);
			this->tabPageResult->Controls->Add(this->button1);
			this->tabPageResult->Controls->Add(this->richTextBoxResults);
			this->tabPageResult->Controls->Add(this->textBoxDebTemp);
			this->tabPageResult->Controls->Add(this->textBoxResTemp);
			this->tabPageResult->Controls->Add(this->textBoxMSD);
			this->tabPageResult->Controls->Add(this->textBoxECoh);
			this->tabPageResult->Controls->Add(this->textBoxETot);
			this->tabPageResult->Controls->Add(this->textBoxEPot);
			this->tabPageResult->Controls->Add(this->textBoxEKin);
			this->tabPageResult->Controls->Add(this->labelDebTemp);
			this->tabPageResult->Controls->Add(this->label13);
			this->tabPageResult->Controls->Add(this->label14);
			this->tabPageResult->Controls->Add(this->label15);
			this->tabPageResult->Controls->Add(this->label16);
			this->tabPageResult->Controls->Add(this->label17);
			this->tabPageResult->Controls->Add(this->label8);
			this->tabPageResult->Location = System::Drawing::Point(4, 22);
			this->tabPageResult->Name = L"tabPageResult";
			this->tabPageResult->Padding = System::Windows::Forms::Padding(3);
			this->tabPageResult->Size = System::Drawing::Size(628, 424);
			this->tabPageResult->TabIndex = 2;
			this->tabPageResult->Text = L"Results";
			this->tabPageResult->UseVisualStyleBackColor = true;
			// 
			// textBoxHeatCap
			// 
			this->textBoxHeatCap->Location = System::Drawing::Point(143, 241);
			this->textBoxHeatCap->Name = L"textBoxHeatCap";
			this->textBoxHeatCap->ReadOnly = true;
			this->textBoxHeatCap->Size = System::Drawing::Size(87, 20);
			this->textBoxHeatCap->TabIndex = 41;
			// 
			// labelHeatCap
			// 
			this->labelHeatCap->AutoSize = true;
			this->labelHeatCap->Location = System::Drawing::Point(15, 241);
			this->labelHeatCap->Name = L"labelHeatCap";
			this->labelHeatCap->Size = System::Drawing::Size(73, 13);
			this->labelHeatCap->TabIndex = 40;
			this->labelHeatCap->Text = L"Heat capacity";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(18, 296);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 23);
			this->button1->TabIndex = 39;
			this->button1->Text = L"Start Simulation";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// richTextBoxResults
			// 
			this->richTextBoxResults->Location = System::Drawing::Point(256, 3);
			this->richTextBoxResults->Name = L"richTextBoxResults";
			this->richTextBoxResults->Size = System::Drawing::Size(254, 344);
			this->richTextBoxResults->TabIndex = 38;
			this->richTextBoxResults->Text = L"";
			// 
			// textBoxDebTemp
			// 
			this->textBoxDebTemp->Location = System::Drawing::Point(145, 211);
			this->textBoxDebTemp->Name = L"textBoxDebTemp";
			this->textBoxDebTemp->ReadOnly = true;
			this->textBoxDebTemp->Size = System::Drawing::Size(87, 20);
			this->textBoxDebTemp->TabIndex = 37;
			// 
			// textBoxResTemp
			// 
			this->textBoxResTemp->Location = System::Drawing::Point(145, 174);
			this->textBoxResTemp->Name = L"textBoxResTemp";
			this->textBoxResTemp->ReadOnly = true;
			this->textBoxResTemp->Size = System::Drawing::Size(87, 20);
			this->textBoxResTemp->TabIndex = 36;
			// 
			// textBoxMSD
			// 
			this->textBoxMSD->Location = System::Drawing::Point(145, 141);
			this->textBoxMSD->Name = L"textBoxMSD";
			this->textBoxMSD->ReadOnly = true;
			this->textBoxMSD->Size = System::Drawing::Size(87, 20);
			this->textBoxMSD->TabIndex = 35;
			// 
			// textBoxECoh
			// 
			this->textBoxECoh->Location = System::Drawing::Point(145, 112);
			this->textBoxECoh->Name = L"textBoxECoh";
			this->textBoxECoh->ReadOnly = true;
			this->textBoxECoh->Size = System::Drawing::Size(87, 20);
			this->textBoxECoh->TabIndex = 34;
			// 
			// textBoxETot
			// 
			this->textBoxETot->Location = System::Drawing::Point(145, 83);
			this->textBoxETot->Name = L"textBoxETot";
			this->textBoxETot->ReadOnly = true;
			this->textBoxETot->Size = System::Drawing::Size(87, 20);
			this->textBoxETot->TabIndex = 33;
			// 
			// textBoxEPot
			// 
			this->textBoxEPot->Location = System::Drawing::Point(145, 48);
			this->textBoxEPot->Name = L"textBoxEPot";
			this->textBoxEPot->ReadOnly = true;
			this->textBoxEPot->Size = System::Drawing::Size(87, 20);
			this->textBoxEPot->TabIndex = 32;
			// 
			// textBoxEKin
			// 
			this->textBoxEKin->Location = System::Drawing::Point(145, 16);
			this->textBoxEKin->Name = L"textBoxEKin";
			this->textBoxEKin->ReadOnly = true;
			this->textBoxEKin->Size = System::Drawing::Size(87, 20);
			this->textBoxEKin->TabIndex = 31;
			// 
			// labelDebTemp
			// 
			this->labelDebTemp->AutoSize = true;
			this->labelDebTemp->Location = System::Drawing::Point(17, 211);
			this->labelDebTemp->Name = L"labelDebTemp";
			this->labelDebTemp->Size = System::Drawing::Size(97, 13);
			this->labelDebTemp->TabIndex = 30;
			this->labelDebTemp->Text = L"Debye temperature";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(17, 141);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(31, 13);
			this->label13->TabIndex = 29;
			this->label13->Text = L"MSD";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(15, 115);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(87, 13);
			this->label14->TabIndex = 28;
			this->label14->Text = L"Cohesive Energy";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(15, 83);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(67, 13);
			this->label15->TabIndex = 27;
			this->label15->Text = L"Total Energy";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(15, 48);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(84, 13);
			this->label16->TabIndex = 26;
			this->label16->Text = L"Potential Energy";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(15, 16);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(75, 13);
			this->label17->TabIndex = 25;
			this->label17->Text = L"Kinetic Energy";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 174);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(67, 13);
			this->label8->TabIndex = 18;
			this->label8->Text = L"Temperature";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(651, 462);
			this->Controls->Add(this->tabControl1);
			this->Name = L"Form1";
			this->Text = L"TFYA50";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPageStructure->ResumeLayout(false);
			this->tabPageStructure->PerformLayout();
			this->tabPageCalculation->ResumeLayout(false);
			this->tabPageCalculation->PerformLayout();
			this->tabPageResult->ResumeLayout(false);
			this->tabPageResult->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


private: 

private: Input_data Form1::get_data();
private: System::Void get_dimensions(int &a, int &b, int &c);
private: float get_lattice_constant();
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: float get_collision_rate();


private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void label20_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void set_materials(unsigned int l);
private: Material selected_material();
private: System::Void set_defaults(Material m);
};
}

