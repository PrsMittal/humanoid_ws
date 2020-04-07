#include<map.hpp>
#include<cmath>

double wall :: potential(const vect& p) {
	double d = (bp1 - p).length() + (bp2 - p).length();
	double gauss = _gaussian(d - std::sqrt(w*w + t*t), 0.7071);
	return gauss;
}


double well :: potential(const vect& p) {
	double d = (p-center).length()
	double gauss = _gaussian(max(d-r, 0), 0.7071);
	return gauss;
}

double door :: potential(const vect& p) {
	double d = (p-center).length());
	double gauss = (d**2)*_gaussian(d, 0.7071); //sigma will most probably be w/(2^(1.5))
	return gauss;
}