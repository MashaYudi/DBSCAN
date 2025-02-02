#pragma once
#include <vector>
using namespace std;
class point {
public:
	float x;
	float y;
	int cluster = 0;
	int pointType = 1;//1 noise 2 border 3 core
	int pts = 0;//points in MinPts 
	vector<int> corepts;
	int visited = 0;
	point() {}

	point(float a, float b, int c = 1){
		x = a;
		y = b;
		cluster = c;
	}
};



struct BBox
{
	double xMin;
	double xMax;
	double yMin;
	double yMax;
	int cluster;
};


float stringToFloat(string i);

vector<point> clustering(vector<point> dataset, float Eps, int MinPts);

vector<point> openFile(const char* dataset);

vector<point> noiseRemoval(vector<point> clusteredData, int threshold);

vector<BBox> boundingBox(vector<point> noisedRemovedResults);