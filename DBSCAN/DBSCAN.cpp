// DBSCAN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <stack>

#include "ProbMap.h"
#include "Funcs.h"
#include "Clustering.h"

int main()
{

	R_t temp;

	ifstream infile("scene_1_all_mod.txt");
	double buff;

	float eps = 4;
	int minPts = 3;
	double current_x, current_y;
	
	vector<R_t> sample;
	/*for (int i = 0; i < 5; i++)
	{
		infile >> buff;
		cout << buff << endl;
	}*/
	
	while (!infile.eof()) {
		infile >> buff;
		temp.id = buff;
		infile >> buff;
		temp.x = buff;
		infile >> buff;
		temp.y = buff;
		infile >> buff;
		temp.z = buff;
		infile >> buff;
		temp.snr = buff;
		infile >> buff;
		temp.A = buff;
		//string temp;
		//infile >> temp;
		//getline(infile, temp);
		//int split = temp.find(' ', 0);
		//R_t p{stringToFloat(temp.substr(0, split)), stringToFloat(temp.substr(split + 1,split)), stringToFloat(temp.substr(split + 1,split)), 
		//	stringToFloat(temp.substr(split + 1,split)),stringToFloat(temp.substr(split + 1,split)), stringToFloat(temp.substr(split + 1, temp.length() - 1))};
		sample.push_back(temp);
	}


	/*for (int i = 0; i < 237; i++) {
		infile >> buff;
		temp.x = buff;
		infile >> buff;
		temp.y = buff;
		infile >> buff;
		temp.A = buff;
		sample.push_back(temp);
	}
	*/
	//vector<R_t> sample;
	/*R_t a{ 1,2,3 }, b{0.5,1,4 }, c{ 2.2,1.4,6 };
	

	sample.push_back(a);
	sample.push_back(b);
	sample.push_back(c);*/

	int tar_num = sample.size();
	float d_N = 50;

	int M = 600, N = 600;
	double delta_x = 0.5, delta_y = 0.5;
	pair<double, double> coords = make_pair(0,0);

	ProbMap parking = ProbMap(M, N, delta_x, delta_y);

	compensation(sample, d_N);

	normalization(sample);

	scaling(sample);

	//coords = get_vehicle_coords(coords); 

	//update_coord(sample, coords);

	parking.fill_target_list(sample);

	parking.fill_grid();

	parking.clean();
	
	vector<point> test = parking.make_list_of_points();

	vector<point> results;
	vector<BBox> final_results;
	vector<point> noisedRemoved_results;

	results = clustering(test, eps, minPts);

	noisedRemoved_results = noiseRemoval(results, 15);
	//cout << "Result size" << final_results.size() << endl;
	final_results = boundingBox(noisedRemoved_results);

	cout << "No of Bounding Boxes" << final_results.size() << endl << endl;

	ofstream myfile("example.txt");

	parking.print(myfile);

}
