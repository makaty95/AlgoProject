#include "MainForm.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip> 
#include <fstream>
#include <chrono>
#include "FileHandling.h"
#include "PathFinder.h"
#include "Timer.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;
using namespace std::chrono;



[STAThreadAttribute]
int main(int argc, char argv[])
{
	/*string map_file = "SFMap.txt";
	string queries_file = "SFQueries.txt";*/
	//string map_file = "OLMap.txt";
	   //string queries_file = "OLQueries.txt";
	   /*string map_file = "map1.txt";
	   string queries_file = "queries1.txt";*/

	   string map_file = "testcases\\[1] Sample Cases\\Input\\map5.txt";
	   string queries_file = "testcases\\[1] Sample Cases\\Input\\queries5.txt";




	auto timeWithIO = steady_clock::now();


	ReadInputs(map_file, PathFinder::intersections, PathFinder::graph);
	ReadQueries(queries_file, PathFinder::queries);


	auto timeWithoutIO = steady_clock::now();
	

	Start();

	auto endtimeWithoutIO = steady_clock::now();
	Result::elapsedTimeWithoutIO = duration_cast<duration<double>>(endtimeWithoutIO - timeWithoutIO).count();  // OK

	printResult("output.txt", PathFinder::results, timeWithIO);


	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Replace `MyWinFormsApp` with your actual namespace
	Application::Run(gcnew AlgoProject::MainForm());


	return 0;

}

