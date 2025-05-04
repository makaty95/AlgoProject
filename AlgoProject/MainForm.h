#pragma once
#include <iostream>
#include "Utility.h"
#include <msclr/marshal_cppstd.h> // Required for marshal_as
using namespace msclr::interop;

namespace AlgoProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{


	public:

		void EnableDoubleBuffering(Control^ ctrl)
		{
			System::Reflection::PropertyInfo^ aProp =
				ctrl->GetType()->GetProperty("DoubleBuffered",
					System::Reflection::BindingFlags::NonPublic |
					System::Reflection::BindingFlags::Instance);
			aProp->SetValue(ctrl, true, nullptr);
		}


		MainForm(void)
		{
			InitializeComponent();
			EnableDoubleBuffering(this->mapView_panel); // enable smooth drawing for any animations.
		}

		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ cover_panel;
	private: System::Windows::Forms::Panel^ controls_panel;
	protected:

	private: System::Windows::Forms::Panel^ mapView_panel;
	private: System::Windows::Forms::Button^ loadMap_btn;
	private: System::Windows::Forms::Panel^ indQuery_panel;
	private: System::Windows::Forms::Button^ exAll_btn;


	private: System::Windows::Forms::Button^ loadQueries_btn;



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
			this->cover_panel = (gcnew System::Windows::Forms::Panel());
			this->controls_panel = (gcnew System::Windows::Forms::Panel());
			this->loadMap_btn = (gcnew System::Windows::Forms::Button());
			this->mapView_panel = (gcnew System::Windows::Forms::Panel());
			this->loadQueries_btn = (gcnew System::Windows::Forms::Button());
			this->exAll_btn = (gcnew System::Windows::Forms::Button());
			this->indQuery_panel = (gcnew System::Windows::Forms::Panel());
			this->cover_panel->SuspendLayout();
			this->controls_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// cover_panel
			// 
			this->cover_panel->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->cover_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->cover_panel->Controls->Add(this->controls_panel);
			this->cover_panel->Controls->Add(this->mapView_panel);
			this->cover_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cover_panel->Location = System::Drawing::Point(0, 0);
			this->cover_panel->Name = L"cover_panel";
			this->cover_panel->Size = System::Drawing::Size(1374, 761);
			this->cover_panel->TabIndex = 0;
			// 
			// controls_panel
			// 
			this->controls_panel->BackColor = System::Drawing::SystemColors::ControlLight;
			this->controls_panel->Controls->Add(this->indQuery_panel);
			this->controls_panel->Controls->Add(this->exAll_btn);
			this->controls_panel->Controls->Add(this->loadQueries_btn);
			this->controls_panel->Controls->Add(this->loadMap_btn);
			this->controls_panel->Location = System::Drawing::Point(1042, 31);
			this->controls_panel->Name = L"controls_panel";
			this->controls_panel->Size = System::Drawing::Size(325, 681);
			this->controls_panel->TabIndex = 1;
			// 
			// loadMap_btn
			// 
			this->loadMap_btn->Location = System::Drawing::Point(18, 14);
			this->loadMap_btn->Name = L"loadMap_btn";
			this->loadMap_btn->Size = System::Drawing::Size(286, 55);
			this->loadMap_btn->TabIndex = 0;
			this->loadMap_btn->Text = L"Load Map";
			this->loadMap_btn->UseVisualStyleBackColor = true;
			this->loadMap_btn->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// mapView_panel
			// 
			this->mapView_panel->BackColor = System::Drawing::Color::LightSteelBlue;
			this->mapView_panel->Location = System::Drawing::Point(10, 31);
			this->mapView_panel->Name = L"mapView_panel";
			this->mapView_panel->Size = System::Drawing::Size(1026, 681);
			this->mapView_panel->TabIndex = 0;
			// 
			// loadQueries_btn
			// 
			this->loadQueries_btn->Location = System::Drawing::Point(18, 87);
			this->loadQueries_btn->Name = L"loadQueries_btn";
			this->loadQueries_btn->Size = System::Drawing::Size(286, 55);
			this->loadQueries_btn->TabIndex = 1;
			this->loadQueries_btn->Text = L"Load Queries";
			this->loadQueries_btn->UseVisualStyleBackColor = true;
			// 
			// exAll_btn
			// 
			this->exAll_btn->Location = System::Drawing::Point(18, 611);
			this->exAll_btn->Name = L"exAll_btn";
			this->exAll_btn->Size = System::Drawing::Size(286, 55);
			this->exAll_btn->TabIndex = 2;
			this->exAll_btn->Text = L"Execute All Queries";
			this->exAll_btn->UseVisualStyleBackColor = true;
			// 
			// indQuery_panel
			// 
			this->indQuery_panel->BackColor = System::Drawing::SystemColors::Window;
			this->indQuery_panel->Location = System::Drawing::Point(18, 216);
			this->indQuery_panel->Name = L"indQuery_panel";
			this->indQuery_panel->Size = System::Drawing::Size(286, 363);
			this->indQuery_panel->TabIndex = 3;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1374, 761);
			this->Controls->Add(this->cover_panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->cover_panel->ResumeLayout(false);
			this->controls_panel->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Text Files (*.txt)|*.txt";
		openFileDialog->Title = "Choose the map file";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ mapPath = openFileDialog->FileName;

			std::string file_path = marshal_as<std::string>(mapPath);
		    

			int status = FIO::ReadInputs(file_path, MapData::nodes, MapData::graph);
			if (status != -1) {
				MessageBox::Show("Done");

				// show the map info on the console.
				Debug::PrintMapData(MapData::nodes, MapData::graph);
				
				//TODO// draw the graph on the map view.

				
			}
			else MessageBox::Show("Some error happened.");
		}


	}
};
}
