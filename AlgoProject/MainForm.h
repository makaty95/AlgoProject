#pragma once
#include <iostream>
#include "Utility.h"
#include "FileHandling.h"
#include "PathFInder.h"
#include <chrono>
#include "Timer.h"
#include <msclr/marshal_cppstd.h> // Required for marshal_as
using namespace msclr::interop;
using namespace std::chrono;
using namespace std;

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
		bool isDragging = false;
		Point dragStartPos;
		int currentQuery = 0;

		void EnableDoubleBuffering(Control^ ctrl)
		{
			System::Reflection::PropertyInfo^ aProp =
				ctrl->GetType()->GetProperty("DoubleBuffered",
					System::Reflection::BindingFlags::NonPublic |
					System::Reflection::BindingFlags::Instance);
			aProp->SetValue(ctrl, true, nullptr);
		}

		void setMessage(String^ message, Color color) {
			lbl_message->Text = message;
			lbl_message->ForeColor = color;
		}


		void setQueriesInfo() {
			label1->Text = "Queries Count : " + MapData::queries.size().ToString();
			setCurrentQuery(currentQuery);
			std::cout << "queries info has been set.";
		}

		void setCurrentQuery(int query_idx) {
			label3->Text = String::Format("Start : ({0}, {1})  ", 
				MapData::queries[query_idx].S.x,
				MapData::queries[query_idx].S.y
			);
			label4->Text = String::Format("End : ({0}, {1})  ",
				MapData::queries[query_idx].E.x,
				MapData::queries[query_idx].E.y
			);

			label5->Text = String::Format("R : {0}  ", MapData::queries[query_idx].R);
			label8->Text = String::Format("Query ID : {0}  ", currentQuery + 1);


		}

		void setTimeLabels() {
			label6->Text = String::Format("Total time with IO : {0} ms", (Result::elapsedTimeWithIO * 1000).ToString());
			label7->Text = String::Format("Time without IO : {0} ms", (Result::elapsedTimeWithoutIO * 1000).ToString());

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
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ prev_btn;
	private: System::Windows::Forms::Button^ next_btn;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;



	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ lbl_message;
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
			this->lbl_message = (gcnew System::Windows::Forms::Label());
			this->zoom_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->controls_panel = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->indQuery_panel = (gcnew System::Windows::Forms::Panel());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->prev_btn = (gcnew System::Windows::Forms::Button());
			this->next_btn = (gcnew System::Windows::Forms::Button());
			this->exAll_btn = (gcnew System::Windows::Forms::Button());
			this->loadQueries_btn = (gcnew System::Windows::Forms::Button());
			this->loadMap_btn = (gcnew System::Windows::Forms::Button());
			this->mapView_panel = (gcnew System::Windows::Forms::Panel());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->cover_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoom_trackBar))->BeginInit();
			this->controls_panel->SuspendLayout();
			this->indQuery_panel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// cover_panel
			// 
			this->cover_panel->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->cover_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->cover_panel->Controls->Add(this->lbl_message);
			this->cover_panel->Controls->Add(this->zoom_trackBar);
			this->cover_panel->Controls->Add(this->controls_panel);
			this->cover_panel->Controls->Add(this->mapView_panel);
			this->cover_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cover_panel->Location = System::Drawing::Point(0, 0);
			this->cover_panel->Name = L"cover_panel";
			this->cover_panel->Size = System::Drawing::Size(1374, 761);
			this->cover_panel->TabIndex = 0;
			// 
			// lbl_message
			// 
			this->lbl_message->AutoSize = true;
			this->lbl_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_message->Location = System::Drawing::Point(11, 698);
			this->lbl_message->Name = L"lbl_message";
			this->lbl_message->Size = System::Drawing::Size(0, 20);
			this->lbl_message->TabIndex = 3;
			// 
			// zoom_trackBar
			// 
			this->zoom_trackBar->Cursor = System::Windows::Forms::Cursors::Hand;
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
			// controls_panel
			// 
			this->controls_panel->BackColor = System::Drawing::SystemColors::ControlLight;
			this->controls_panel->Controls->Add(this->label7);
			this->controls_panel->Controls->Add(this->label6);
			this->controls_panel->Controls->Add(this->label1);
			this->controls_panel->Controls->Add(this->indQuery_panel);
			this->controls_panel->Controls->Add(this->exAll_btn);
			this->controls_panel->Controls->Add(this->loadQueries_btn);
			this->controls_panel->Controls->Add(this->loadMap_btn);
			this->controls_panel->Location = System::Drawing::Point(1042, 10);
			this->controls_panel->Name = L"controls_panel";
			this->controls_panel->Size = System::Drawing::Size(325, 681);
			this->controls_panel->TabIndex = 1;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(19, 649);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(126, 20);
			this->label7->TabIndex = 5;
			this->label7->Text = L"time without IO:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(15, 623);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(145, 20);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Total time with IO:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(15, 155);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(141, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Queries Count : 0";
			// 
			// indQuery_panel
			// 
			this->indQuery_panel->AutoScroll = true;
			this->indQuery_panel->BackColor = System::Drawing::SystemColors::Window;
			this->indQuery_panel->Controls->Add(this->label8);
			this->indQuery_panel->Controls->Add(this->label5);
			this->indQuery_panel->Controls->Add(this->label4);
			this->indQuery_panel->Controls->Add(this->label3);
			this->indQuery_panel->Controls->Add(this->label2);
			this->indQuery_panel->Controls->Add(this->prev_btn);
			this->indQuery_panel->Controls->Add(this->next_btn);
			this->indQuery_panel->Location = System::Drawing::Point(18, 178);
			this->indQuery_panel->Name = L"indQuery_panel";
			this->indQuery_panel->Size = System::Drawing::Size(286, 363);
			this->indQuery_panel->TabIndex = 3;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 119);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(81, 20);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Query ID:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(6, 225);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(26, 20);
			this->label5->TabIndex = 5;
			this->label5->Text = L"R:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(6, 191);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(43, 20);
			this->label4->TabIndex = 4;
			this->label4->Text = L"End:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(6, 158);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 20);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Start:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(56, 72);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(147, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Current Query Info";
			// 
			// prev_btn
			// 
			this->prev_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->prev_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->prev_btn->Location = System::Drawing::Point(10, 5);
			this->prev_btn->Name = L"prev_btn";
			this->prev_btn->Size = System::Drawing::Size(126, 40);
			this->prev_btn->TabIndex = 1;
			this->prev_btn->Text = L"Previous Query";
			this->prev_btn->UseVisualStyleBackColor = true;
			this->prev_btn->Click += gcnew System::EventHandler(this, &MainForm::prev_btn_Click);
			// 
			// next_btn
			// 
			this->next_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->next_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->next_btn->Location = System::Drawing::Point(142, 4);
			this->next_btn->Name = L"next_btn";
			this->next_btn->Size = System::Drawing::Size(126, 41);
			this->next_btn->TabIndex = 0;
			this->next_btn->Text = L"Next Query";
			this->next_btn->UseVisualStyleBackColor = true;
			this->next_btn->Click += gcnew System::EventHandler(this, &MainForm::next_btn_Click);
			// 
			// exAll_btn
			// 
			this->exAll_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->exAll_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->exAll_btn->Location = System::Drawing::Point(18, 547);
			this->exAll_btn->Name = L"exAll_btn";
			this->exAll_btn->Size = System::Drawing::Size(286, 55);
			this->exAll_btn->TabIndex = 2;
			this->exAll_btn->Text = L"Execute All Queries";
			this->exAll_btn->UseVisualStyleBackColor = true;
			this->exAll_btn->Click += gcnew System::EventHandler(this, &MainForm::exAll_btn_Click);
			// 
			// loadQueries_btn
			// 
			this->loadQueries_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->loadQueries_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->loadQueries_btn->Location = System::Drawing::Point(18, 87);
			this->loadQueries_btn->Name = L"loadQueries_btn";
			this->loadQueries_btn->Size = System::Drawing::Size(286, 55);
			this->loadQueries_btn->TabIndex = 1;
			this->loadQueries_btn->Text = L"Load Queries";
			this->loadQueries_btn->UseVisualStyleBackColor = true;
			this->loadQueries_btn->Click += gcnew System::EventHandler(this, &MainForm::loadQueries_btn_Click);
			// 
			// loadMap_btn
			// 
			this->loadMap_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->loadMap_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
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
			this->mapView_panel->Cursor = System::Windows::Forms::Cursors::Cross;
			this->mapView_panel->Location = System::Drawing::Point(10, 10);
			this->mapView_panel->Name = L"mapView_panel";
			this->mapView_panel->Size = System::Drawing::Size(1026, 681);
			this->mapView_panel->TabIndex = 0;
			this->mapView_panel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::mapView_panel_Paint);
			this->mapView_panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mapView_panel_MouseDown);
			this->mapView_panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mapView_panel_MouseMove);
			this->mapView_panel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::mapView_panel_MouseUp);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoom_trackBar))->EndInit();
			this->controls_panel->ResumeLayout(false);
			this->controls_panel->PerformLayout();
			this->indQuery_panel->ResumeLayout(false);
			this->indQuery_panel->PerformLayout();
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

			setMessage("Reading Map....", Color::Black);
			this->Refresh();

			// begine input time record
			auto mapStartTime = steady_clock::now();
			int status = FIO::ReadMap(file_path, MapData::nodes, MapData::graph);
			auto mapEndTime = steady_clock::now();

			setMessage("Done.", Color::Black);
			this->Refresh();
			

			if (status  == 0) {


				MessageBox::Show("Map Loaded.");
				printf("\n min_x = %f, max_x = %f,min_y = %f, max_y =%f\n",
					MapData::drawInfo.min_x, MapData::drawInfo.max_x, MapData::drawInfo.min_y, MapData::drawInfo.max_y);
				

				// calculate the time and add it to IO time
				Result::elapsedTimeWithIO = duration_cast<duration<double>>(mapEndTime - mapStartTime).count();
				std::cout << "time elapsed with IO: " << Result::elapsedTimeWithIO << std::endl;


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

			//1// draw the nodes for the current query with diff color
			Brush^ brush =  Brushes::Red;
			

			//-------------------Draw Map Nodes----------------------//
			
			vector<bool> taken(MapData::N + 1, false);

			// if we got the results for the query
			if (!MapData::results.empty()) {
				auto currentQueryResult = MapData::results[currentQuery];
				
				for (auto id : currentQueryResult.pathId) {
					DS::Node node = MapData::nodes[id];
					DS::Point p = Visuals::normalize(node.loc.x, node.loc.y); // normalize coordinates
					int r = MapData::nodes[id].properties.radius;
					
					r *= 4; // just for debugging
					g->FillEllipse(brush, (p.x - r), (p.y - r), r * 2, r * 2);
					taken[id] = true; // mark it so we don't paint it again. 
				}
			}

			// Draw the other map nodes
			for (int idx = 0; idx < MapData::N; idx++) {

				// if we already drew it 
				if (taken[idx]) continue;

				DS::Node node = MapData::nodes[idx];
				DS::Point p = Visuals::normalize(node.loc.x, node.loc.y); // normalize coordinates
				
				brush = node.properties.isSelected ? Brushes::Red : Brushes::Black;
				
				g->FillEllipse(brush, p.x - node.properties.radius,
					p.y - node.properties.radius, node.properties.radius * 2, node.properties.radius * 2);

			}

			


			//-------------------Draw Map Edges----------------------//
			std::vector<bool> done(MapData::N+3, false);


			// if the queries results are calculated.
			if (!MapData::results.empty()) {
				// first draw the edges of the path of current query
				int resultsSize = MapData::results[currentQuery].pathId.size();
				printf("resultSize: %d\n", resultsSize);
				for (int idx = 0; idx < (resultsSize - 1); idx++) {
				
					// indices of the nodes that form an edge in the path.
					int cur = MapData::results[currentQuery].pathId[idx];
					int nex = MapData::results[currentQuery].pathId[idx + 1];

					// draw the path edge (cur -> nex)
					DS::Point p1 = Visuals::normalize(MapData::nodes[cur].loc);
					DS::Point p2 = Visuals::normalize(MapData::nodes[nex].loc);
					g->DrawLine(gcnew Pen(Color::Red), Point(p1.x, p1.y), Point(p2.x, p2.y));
				
					// draw all the other edges starting from node idx
					for each(DS::Edge e in MapData::graph[cur]) {
						if (e.neighbor_id != nex && !done[e.neighbor_id]) {
							p2 = Visuals::normalize(MapData::nodes[e.neighbor_id].loc);
							g->DrawLine(gcnew Pen(Color::Black), Point(p1.x, p1.y), Point(p2.x, p2.y));
						}
					}

					// mark the node idx as done
					done[cur] = true;
				}

				// draw the start and end points
				DS::Point ps = MapData::queries[currentQuery].S;
				DS::Point pe = MapData::queries[currentQuery].E;
				DS::Point pss = MapData::nodes[MapData::results[currentQuery].pathId.back()].loc;
				DS::Point pee = MapData::nodes[MapData::results[currentQuery].pathId.front()].loc;

				// normalize the points
				ps = Visuals::normalize(ps);
				pss = Visuals::normalize(pss);
				pe = Visuals::normalize(pe);
				pee = Visuals::normalize(pee);

				int r = 4 * MapData::nodes[MapData::results[currentQuery].pathId.front()].properties.radius;
				
				brush = Brushes::Blue;
				// draw the 2 nodes
				g->FillEllipse(brush, ps.x - r, ps.y - r, r * 2, r * 2);
				g->FillEllipse(brush, pe.x - r, pe.y - r, r * 2, r * 2);


				// draw the 2 edges 
				g->DrawLine(gcnew Pen(Color::Blue), Point(ps.x, ps.y), Point(pss.x, pss.y));
				g->DrawLine(gcnew Pen(Color::Blue), Point(pe.x, pe.y), Point(pee.x, pee.y));


			}

			// the draw the rest of the edges
			for (int i = 0; i < MapData::N; i++) { // O(M)
				if (done[i]) continue; // if i already drew all edges out of this node.

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
		MapData::drawInfo = DS::DrawInfo(w, h);
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

	private: System::Void loadQueries_btn_Click(System::Object^ sender, System::EventArgs^ e) {

		// load the queries
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Text Files (*.txt)|*.txt";
		openFileDialog->Title = "Choose the queries file";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ queriesPath = openFileDialog->FileName;

			// transform the String^ to regular cpp classic string.
			std::string file_path = marshal_as<std::string>(queriesPath);
			
			setMessage("Reading Queries....", Color::Black);
			this->Refresh();

			// record time
			auto qStartTime = steady_clock::now();
			int status = FIO::ReadQueries(file_path, MapData::queries);
			auto qEndTime = steady_clock::now();
			
			setMessage("Done.", Color::Black);
			this->Refresh();

			if (status  == 0) {
				// add time to IO time.
				Result::elapsedTimeWithIO += duration_cast<duration<double>>(qEndTime - qStartTime).count();
				std::cout << "time elapsed with IO: " << Result::elapsedTimeWithIO << std::endl;
				
				//
				currentQuery = 0;
				setQueriesInfo();

				MessageBox::Show("Queries Loaded.");
				

				// show the map info on the console (takes time - debugging only :)).
				Debug::PrintQueriesData(MapData::queries);

				
			}
			else MessageBox::Show("Some error happened.");

			

			
		}
	}
	private: System::Void exAll_btn_Click(System::Object^ sender, System::EventArgs^ e) {

	
		setMessage("Executing All Queries....", Color::Green);
		this->Refresh();

		auto startTime = steady_clock::now();
		// execute all queries
		Start();
		auto endTime = steady_clock::now();

		double time = duration_cast<duration<double>>(endTime - startTime).count();
		Result::elapsedTimeWithoutIO = time;
		Result::elapsedTimeWithIO += time;


		std::cout << ">> time elapsed withoutIO: " << Result::elapsedTimeWithoutIO << std::endl;
		std::cout << ">> time elapsed with IO: " << Result::elapsedTimeWithIO << std::endl;
		
		// output results file.
		auto IOStartTime = steady_clock::now();
		FIO::printResult("output.txt", MapData::results, IOStartTime);
		
		setTimeLabels();

		setMessage("Done.", Color::Black);
		this->Refresh();

		
		
	}
	private: System::Void next_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		int n = MapData::queries.size();
		currentQuery++;
		currentQuery %= n;
		setCurrentQuery(currentQuery);

		/*if (!MapData::results.empty()) {
			printf("\n\n-----------Current query path-------\n");
			auto currentQueryResult = MapData::results[currentQuery];
			for (auto id : currentQueryResult.pathId) {
				printf("<%f, %f> ", MapData::nodes[id].loc.x, MapData::nodes[id].loc.y);

			}
			cout << endl;

		}*/

		// draw the path
		mapView_panel->Invalidate();

	}
	private: System::Void prev_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		int n = MapData::queries.size();
		currentQuery--;
		currentQuery += n;
		currentQuery %= n;
		setCurrentQuery(currentQuery);

		/*if (!MapData::results.empty()) {
			printf("\n\n-----------Current query path-------\n");
			auto currentQueryResult = MapData::results[currentQuery];
			for (auto id : currentQueryResult.pathId) {
				printf("<%f, %f> ", MapData::nodes[id].loc.x, MapData::nodes[id].loc.y);

			}
			cout << endl;

		}*/

		// draw the path
		mapView_panel->Invalidate();
	}
	private: System::Void mapView_panel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	
		// detect if the mouse is clicked, then activate the dragging.
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			isDragging = true;
			dragStartPos = e->Location;
		}

	}


	private: System::Void mapView_panel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (isDragging) {
			// Calculate drag distance
			float delta_x = e->X - dragStartPos.X;
			float delta_y = e->Y - dragStartPos.Y;

			// Update total pan offset
			MapData::panOffset.x += delta_x;
			MapData::panOffset.y += delta_y;

			// Update "last position" for next move event
			dragStartPos = e->Location;

			// Redraw the panel.
			mapView_panel->Invalidate();
		}

	}
	private: System::Void mapView_panel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	
		isDragging = false;
	}
};
}
