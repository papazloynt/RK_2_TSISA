#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

//14 variant
// 25% ; 6 points


double Function(const double x, const double y)
{
	return (-log(1 + x * x + y * y) + x * x / 2);
}


bool max(std::pair<double, double> lhs, std::pair<double, double> rhs)
{ return Function(lhs.first, lhs.second) > Function(rhs.first, rhs.second); }

void mutation(std::pair<double, double>& p) {
	if (rand() % 100 < 25) {
		p.first = (rand() % 100)/100.0;
		p.second = (rand() % 100)/100.0;
	}
}

void crossover(const std::pair<double, double>& lhs, std::pair<double, double>& rhs, std::vector<std::pair<double, double>>& vec) {
	std::pair<double, double> buf1, buf2;
	buf1.first = lhs.first;
	buf1.second = rhs.second;
	buf2.first = rhs.first;
	buf2.second = lhs.second;
	mutation(buf1);
	mutation(buf2);
	vec.push_back(buf1);
	vec.push_back(buf2);
}


void R_I_P(std::vector<std::pair<double, double>>& vec) {
	std::sort(vec.begin(), vec.end(), max);
	vec.erase(vec.begin() + 4, vec.end());
}


void print(std::vector<std::pair<double, double>>& vec) {

	double sum = 0;
	for (size_t i = 0; i < 4; i++) {
		std::cout << "X = " << vec[i].first << "   Y = " << vec[i].second
			<< "   Fit  function = " << Function(vec[i].first, vec[i].second) << std::endl;
		sum += Function(vec[i].first, vec[i].second);
	}
	double mid = sum / 4;
	std::cout << "Middle Fit = " << mid
		<< "   Max Fit = " << Function(vec[0].first, vec[0].second) << std::endl
		<< std::endl;
}


int main() {
	std::vector<std::pair<double, double>> vec(6);
	srand(time(NULL));

	for (size_t i = 0; i < 6; i++) {
		vec[i].first = (rand() % 100)/100.0;
		vec[i].second = (rand() % 100)/100.0;
	}

	std::sort(vec.begin(),vec.end(), max);

	for (size_t i = 0; i < 100; i++) {
		print(vec);
		crossover(vec[0], vec[1], vec);
		crossover(vec[0], vec[2], vec);
		crossover(vec[0], vec[3], vec);
		crossover(vec[0], vec[4], vec);
		crossover(vec[0], vec[5], vec);
		R_I_P(vec);
	}


}
