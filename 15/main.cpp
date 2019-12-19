#include <iostream>
#include "full_graph.h"
#include <random>
#include <cmath>
#include <math.h>


int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1.0, 0);
	int maxN = 9;
	const double pi = std::acos(-1);
	int sample_size = 10;
	std::cout << "sample size = " << sample_size << std::endl << std::endl;
	for (int n = 2; n < maxN; ++n)
	{
		std::cout << "n = " << n << std::endl;
		double mean = 0.0;
		double mean_sqr = 0.0;
		for (int j = 0; j < sample_size; j++)
		{
			std::vector<point> init_vector;
			for (int i = 0; i < n; ++i)
			{
				double x = abs(dis(gen));
				double y = abs(dis(gen));
				x = cos(2.0 * pi * x) * pow((-2.0)*log(y), 0.5);
				x = sin(2.0 * pi * x) * pow((-2.0)*log(y), 0.5);
				init_vector.push_back({ x,y });
			}
			FullGraph graph(init_vector);
			graph.CalculateDistance();
			double approximate = graph.GetApproximateWeightGraphPath();
			double minimal = graph.GetMinimalWeightGraphPath();
			mean += approximate - minimal;
			mean_sqr += pow(approximate - minimal,2);
		}
		mean /= double(sample_size);
		mean_sqr /= double(sample_size);
		if(mean_sqr!=0)
			mean_sqr = pow(mean_sqr, 0.5);
		std::cout << "mean = " << mean << std::endl;
		std::cout << "mean_sqr = " << mean_sqr << std::endl << std::endl;
	}

	return 0;
}