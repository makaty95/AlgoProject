#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Types.h"
using namespace std;

//using namespace System;
//using namespace System::ComponentModel;
//using namespace System::Collections;
//using namespace System::Windows::Forms;
//using namespace System::Data;
//using namespace System::Drawing;
//using namespace System::Collections::Generic;

namespace Geometry {
    double EuclideanDistance(double x1, double y1, double x2, double y2);
    double EuclideanDistance(DS::Point a, DS::Point b);
}



namespace Debug {
    void PrintMapData(
                    std::vector<DS::Node>&              nodes,
                    std::vector<std::vector<DS::Edge>>& graph
    );

    void PrintQueriesData(std::vector<DS::Query>& queries);

}


namespace Visuals {
    //void setMapDrawing(bool toSet);

    
    
    std::vector<DS::Point>  zoom();
    DS::Point               zoom(DS::Point p);
    DS::Point               normalize(DS::Point p);
    DS::Point               normalize(double x, double y);
}

