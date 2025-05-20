#include "Types.h"

// static vars
std::vector<std::vector<DS::Edge>> MapData::graph = std::vector<std::vector<DS::Edge>>();
std::vector<DS::Node> MapData::nodes = std::vector<DS::Node>();
double MapData::zoomFactor = 1.0;
DS::Point MapData::zoomCenter = DS::Point();
DS::DrawInfo MapData::drawInfo = DS::DrawInfo();
std::vector<DS::Query> MapData::queries = std::vector<DS::Query>();
std::vector<Result> MapData::results = std::vector<Result>();
bool MapData::isLoaded = false;
int MapData::N = 0;
int MapData::M = 0;
int MapData::defaultRadius = 1;
int currentQuery = 0;
DS::Point MapData::panOffset = DS::Point(0, 0);
