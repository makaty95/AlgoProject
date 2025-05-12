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
	private: System::Windows::Forms::TrackBar^ zoom_trackBar;
	private: System::Windows::Forms::BindingSource^ bindingSource1;
	private: System::ComponentModel::IContainer^ components;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->cover_panel = (gcnew System::Windows::Forms::Panel());
			this->controls_panel = (gcnew System::Windows::Forms::Panel());
			this->zoom_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->indQuery_panel = (gcnew System::Windows::Forms::Panel());
			this->exAll_btn = (gcnew System::Windows::Forms::Button());
			this->loadQueries_btn = (gcnew System::Windows::Forms::Button());
			this->loadMap_btn = (gcnew System::Windows::Forms::Button());
			this->mapView_panel = (gcnew System::Windows::Forms::Panel());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->cover_panel->SuspendLayout();
			this->controls_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoom_trackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// cover_panel
			// 
			this->cover_panel->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->cover_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->cover_panel->Controls->Add(this->zoom_trackBar);
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
			this->controls_panel->Location = System::Drawing::Point(1042, 10);
			this->controls_panel->Name = L"controls_panel";
			this->controls_panel->Size = System::Drawing::Size(325, 681);
			this->controls_panel->TabIndex = 1;
			// 
			// zoom_trackBar
			// 
			this->zoom_trackBar->Location = System::Drawing::Point(348, 698);
			this->zoom_trackBar->Maximum = 100;
			this->zoom_trackBar->Minimum = 5;
			this->zoom_trackBar->Name = L"zoom_trackBar";
			this->zoom_trackBar->Size = System::Drawing::Size(688, 56);
			this->zoom_trackBar->TabIndex = 2;
			this->zoom_trackBar->Value = 5;
			this->zoom_trackBar->Scroll += gcnew System::EventHandler(this, &MainForm::zoom_trackBar_Scroll);
			this->zoom_trackBar->ValueChanged += gcnew System::EventHandler(this, &MainForm::zoom_trackBar_ValueChanged);
			// 
			// indQuery_panel
			// 
			this->indQuery_panel->AutoScroll = true;
			this->indQuery_panel->BackColor = System::Drawing::SystemColors::Window;
			this->indQuery_panel->Location = System::Drawing::Point(18, 216);
			this->indQuery_panel->Name = L"indQuery_panel";
			this->indQuery_panel->Size = System::Drawing::Size(286, 363);
			this->indQuery_panel->TabIndex = 3;
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
			// loadQueries_btn
			// 
			this->loadQueries_btn->Location = System::Drawing::Point(18, 87);
			this->loadQueries_btn->Name = L"loadQueries_btn";
			this->loadQueries_btn->Size = System::Drawing::Size(286, 55);
			this->loadQueries_btn->TabIndex = 1;
			this->loadQueries_btn->Text = L"Load Queries";
			this->loadQueries_btn->UseVisualStyleBackColor = true;
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
			this->mapView_panel->Location = System::Drawing::Point(10, 10);
			this->mapView_panel->Name = L"mapView_panel";
			this->mapView_panel->Size = System::Drawing::Size(1026, 681);
			this->mapView_panel->TabIndex = 0;
			this->mapView_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::mapView_panel_Paint);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1374, 761);
			this->Controls->Add(this->cover_panel);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->cover_panel->ResumeLayout(false);
			this->cover_panel->PerformLayout();
			this->controls_panel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoom_trackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
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
		    

			int status = FIO::ReadMap(file_path, MapData::nodes, MapData::graph);
			if (status != -1) {
				MessageBox::Show("Done");
				printf("\n min_x = %f, max_x = %f,min_y = %f, max_y =%f\n",
					MapData::drawUtil.min_x, MapData::drawUtil.max_x, MapData::drawUtil.min_y, MapData::drawUtil.max_y);

				// show the map info on the console (takes time - debugging only :)).
				//Debug::PrintMapData(MapData::nodes, MapData::graph);
				
				// draw the graph on the map view.
				mapView_panel->Invalidate();
				
			}
			else MessageBox::Show("Some error happened.");
		}


	}
	private: System::Void mapView_panel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		
		

		if (MapData::isLoaded) { // if there exist a map to draw.
			std::cout << "painting" << std::endl;
			Graphics^ g = e->Graphics;

			// Draw map nodes
			for each(DS::Node node in MapData::nodes) {
				
				DS::Point p = Visuals::normalize(node.loc.x, node.loc.y); // normalize coordinates
				

				Brush^ brush = node.properties.isSelected ? Brushes::Red : Brushes::Black;
				g->FillEllipse(brush, p.x - node.properties.radius,
					p.y - node.properties.radius, node.properties.radius * 2, node.properties.radius * 2);

			}


			//TODO// Draw map edges
			std::vector<bool> done(MapData::N+3, false);
			for (int i = 0; i < MapData::N; i++) { // O(M)
				for each (DS::Edge e in MapData::graph[i]) {
					if (!done[e.neighbor_id]) {
						// draw the edge
						DS::Point p1 = Visuals::normalize(MapData::nodes[i].loc);
						DS::Point p2 = Visuals::normalize(MapData::nodes[e.neighbor_id].loc);
						g->DrawLine(gcnew Pen(Color::Black), Point(p1.x, p1.y), Point(p2.x, p2.y));
					}
				}
				done[i] = true;
			}



		}
	}

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		
		// setting zoomCenter


		MapData::zoomCenter = DS::Point(mapView_panel->Width / 2.0, mapView_panel->Height / 2.0);


		double w = mapView_panel->Size.Width;
		double h = mapView_panel->Size.Height;
		MapData::drawUtil = Visuals::DrawUtil(w, h);
		printf("MapPanel (width,height): (%f, %f)\n\n",w, h);
		
		
	}

	private: System::Void zoom_trackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	/*	double currentValue = zoom_trackBar->Value;
		std::cout << "Current Value: " << currentValue << std::endl;*/

	}
	private: System::Void zoom_trackBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		double currentValue = (double)zoom_trackBar->Value;
		printf("TrackBar Value: %f\n\n", currentValue); // Debug output
		//System::Windows::Forms::MessageBox::Show("TrackBar value changed! " + currentValue); // Simple test
		

		MapData::zoomFactor = currentValue/10.0;
		mapView_panel->Invalidate();
	}

};
}
