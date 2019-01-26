// DBSCAN.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "ProbMap.h"
#include "Funcs.h"


int main()
{
	vector<R_t> sample;
	R_t a{ 1,2,3 }, b{ 2,3,4 }, c{ 4,5,6 };
	

	sample.push_back(a);
	sample.push_back(b);
	sample.push_back(c);

	int tar_num = sample.size();
	float d_N = 1;
	int M = 10, N = 10;
	double delta_x = 0.1, delta_y = 0.1;
	pair<double, double> coords = make_pair(0,0);

	ProbMap parking = ProbMap(M, N, delta_x, delta_y);
	for (int i = 0; i < 5; i++) {
		//compensation(sample, d_N);

		normalization(sample);

		scaling(sample);

		coords = get_vehicle_coords(coords); 

		update_coord(sample, coords);

		parking.fill_target_list(sample);

		parking.fill_grid();

		parking.clean();
	}
}
