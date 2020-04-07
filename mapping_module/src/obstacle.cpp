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
	double d = abs((p-f1).length() - (p-f2).length());
	double gauss = _gaussian(max(d- std::sqrt(w*w+h*h), 0), 0.7071);
	return gauss;
}