#include<map.hpp>
#include<cmath>

double wall :: potential(const vect& p) {
	double d = (bp1 - p).length() + (bp2 - p).length();
	double gauss = _gaussian(d - std::sqrt(w*w + t*t), 0.7071);
	return gauss;
}

