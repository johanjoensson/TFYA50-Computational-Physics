#pragma once
#include "world.h"

struct Input_data{
	int x;
	int y;
	int z;
	float a;
	float cut_off;
	int t_start;
	int t_end;
	float t_step;
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
		Form1(void)
		{
			InitializeComponent();
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
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBoxCO;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxLatConst;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPageCalculation;
	private: System::Windows::Forms::TextBox^  textBoxTStep;






	private: System::Windows::Forms::TextBox^  textBoxTEnd;

	private: System::Windows::Forms::TextBox^  textBoxTStart;

	private: System::Windows::Forms::CheckBox^  checkBox2;




	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TabPage^  tabPageResult;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TextBox^  textBoxZdim;

	private: System::Windows::Forms::TextBox^  textBoxYdim;

	private: System::Windows::Forms::TextBox^  textBoxXdim;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::Label^  label19;

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
			this->tabPageStructure = (gcnew System::Windows::Forms::TabPage());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBoxZdim = (gcnew System::Windows::Forms::TextBox());
			this->textBoxYdim = (gcnew System::Windows::Forms::TextBox());
			this->textBoxXdim = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxCO = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxLatConst = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPageCalculation = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxTStep = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTEnd = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTStart = (gcnew System::Windows::Forms::TextBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tabPageResult = (gcnew System::Windows::Forms::TabPage());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPageStructure->SuspendLayout();
			this->tabPageCalculation->SuspendLayout();
			this->tabPageResult->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPageStructure);
			this->tabControl1->Controls->Add(this->tabPageCalculation);
			this->tabControl1->Controls->Add(this->tabPageResult);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(636, 450);
			this->tabControl1->TabIndex = 2;
			// 
			// tabPageStructure
			// 
			this->tabPageStructure->Controls->Add(this->radioButton3);
			this->tabPageStructure->Controls->Add(this->label19);
			this->tabPageStructure->Controls->Add(this->textBoxZdim);
			this->tabPageStructure->Controls->Add(this->textBoxYdim);
			this->tabPageStructure->Controls->Add(this->textBoxXdim);
			this->tabPageStructure->Controls->Add(this->label12);
			this->tabPageStructure->Controls->Add(this->label11);
			this->tabPageStructure->Controls->Add(this->label10);
			this->tabPageStructure->Controls->Add(this->label4);
			this->tabPageStructure->Controls->Add(this->radioButton2);
			this->tabPageStructure->Controls->Add(this->radioButton1);
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
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(191, 262);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(67, 17);
			this->radioButton3->TabIndex = 40;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Diamond";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(13, 104);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(71, 13);
			this->label19->TabIndex = 39;
			this->label19->Text = L"Dimensions";
			// 
			// textBoxZdim
			// 
			this->textBoxZdim->Location = System::Drawing::Point(150, 194);
			this->textBoxZdim->Name = L"textBoxZdim";
			this->textBoxZdim->Size = System::Drawing::Size(87, 20);
			this->textBoxZdim->TabIndex = 38;
			this->textBoxZdim->TextChanged += gcnew System::EventHandler(this, &Form1::textBox7_TextChanged);
			// 
			// textBoxYdim
			// 
			this->textBoxYdim->Location = System::Drawing::Point(150, 161);
			this->textBoxYdim->Name = L"textBoxYdim";
			this->textBoxYdim->Size = System::Drawing::Size(87, 20);
			this->textBoxYdim->TabIndex = 37;
			// 
			// textBoxXdim
			// 
			this->textBoxXdim->Location = System::Drawing::Point(150, 128);
			this->textBoxXdim->Name = L"textBoxXdim";
			this->textBoxXdim->Size = System::Drawing::Size(87, 20);
			this->textBoxXdim->TabIndex = 36;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(7, 164);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(129, 13);
			this->label12->TabIndex = 35;
			this->label12->Text = L"Nb. of atoms in y direction";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(7, 197);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(129, 13);
			this->label11->TabIndex = 34;
			this->label11->Text = L"Nb. of atoms in z direction";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(7, 131);
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
			this->label4->Location = System::Drawing::Point(13, 232);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(101, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Crystal Structure";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(100, 262);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(46, 17);
			this->radioButton2->TabIndex = 19;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"BCC";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(10, 262);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(45, 17);
			this->radioButton1->TabIndex = 18;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"FCC";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 150);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 16;
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// textBoxCO
			// 
			this->textBoxCO->Location = System::Drawing::Point(150, 69);
			this->textBoxCO->Name = L"textBoxCO";
			this->textBoxCO->Size = System::Drawing::Size(87, 20);
			this->textBoxCO->TabIndex = 15;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 72);
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
			this->label1->Location = System::Drawing::Point(7, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Lattice Constant";
			// 
			// tabPageCalculation
			// 
			this->tabPageCalculation->Controls->Add(this->checkBox1);
			this->tabPageCalculation->Controls->Add(this->textBoxTStep);
			this->tabPageCalculation->Controls->Add(this->textBoxTEnd);
			this->tabPageCalculation->Controls->Add(this->textBoxTStart);
			this->tabPageCalculation->Controls->Add(this->checkBox2);
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
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(365, 79);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(121, 17);
			this->checkBox1->TabIndex = 34;
			this->checkBox1->Text = L"Include visualisation";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// textBoxTStep
			// 
			this->textBoxTStep->Location = System::Drawing::Point(198, 80);
			this->textBoxTStep->Name = L"textBoxTStep";
			this->textBoxTStep->Size = System::Drawing::Size(87, 20);
			this->textBoxTStep->TabIndex = 29;
			// 
			// textBoxTEnd
			// 
			this->textBoxTEnd->Location = System::Drawing::Point(198, 43);
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
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(365, 16);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(79, 17);
			this->checkBox2->TabIndex = 26;
			this->checkBox2->Text = L"Thermostat";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
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
			this->tabPageResult->Controls->Add(this->button1);
			this->tabPageResult->Controls->Add(this->richTextBox1);
			this->tabPageResult->Controls->Add(this->textBox17);
			this->tabPageResult->Controls->Add(this->textBox14);
			this->tabPageResult->Controls->Add(this->textBox15);
			this->tabPageResult->Controls->Add(this->textBox16);
			this->tabPageResult->Controls->Add(this->textBox11);
			this->tabPageResult->Controls->Add(this->textBox12);
			this->tabPageResult->Controls->Add(this->textBox13);
			this->tabPageResult->Controls->Add(this->label18);
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
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(256, 3);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(254, 344);
			this->richTextBox1->TabIndex = 38;
			this->richTextBox1->Text = L"";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(145, 211);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(87, 20);
			this->textBox17->TabIndex = 37;
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(145, 174);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(87, 20);
			this->textBox14->TabIndex = 36;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(145, 141);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(87, 20);
			this->textBox15->TabIndex = 35;
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(145, 112);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(87, 20);
			this->textBox16->TabIndex = 34;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(145, 83);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(87, 20);
			this->textBox11->TabIndex = 33;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(145, 48);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(87, 20);
			this->textBox12->TabIndex = 32;
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(145, 16);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(87, 20);
			this->textBox13->TabIndex = 31;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(17, 211);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(67, 13);
			this->label18->TabIndex = 30;
			this->label18->Text = L"Temperature";
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
			this->Text = L"Form1";
			this->tabControl1->ResumeLayout(false);
			this->tabPageStructure->ResumeLayout(false);
			this->tabPageStructure->PerformLayout();
			this->tabPageCalculation->ResumeLayout(false);
			this->tabPageCalculation->PerformLayout();
			this->tabPageResult->ResumeLayout(false);
			this->tabPageResult->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: Input_data Form1::get_data();
private: System::Void get_dimensions(int &a, int &b, int &c);
private: float get_lattice_constant();
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);


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
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

