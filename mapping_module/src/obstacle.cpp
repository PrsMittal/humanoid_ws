#include<map.hpp>
#include<cmath>

double wall :: potential(const vect& p) {
	double d = (bp1 - p).length() + (bp2 - p).length();
	double gauss = _gaussian(d - std::sqrt(w*w + t*t), 0.7071);
	return gauss;
}


double well :: potential(const vect& p) {
	double d = (p-center).length();
	double gauss = _gaussian(std::max(d-r, 0.0), 0.7071);
	return gauss;
}

double door :: potential(const vect& p) {
	double d = (p-center).length();
	double gauss = (d*d)*_gaussian(d, w/(std::pow(2, 1.5)))/(w*w); //sigma will most probably be w/(2^(1.5))
	return gauss;
}

double goal_line :: distance(const vect& p) {
	double d = (p-center).length()*std::cos(orient*M_PI/180.0);
	return d;
}

double goal_line :: potential(const vect& p){
	double d = distance(p);
	double gauss = _gaussian(d, 1.414);
	return -gauss;
}
