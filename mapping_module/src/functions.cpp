//#include<map.hpp>
#include<functions.hpp>
#include<cmath>
namespace huroiitk{
double _gaussian(const double& d, const double& sig){
	double e = -((d/sig)*(d/sig)/2);
	double gauss = (1/(sig * std::sqrt(M_PI * 2))) * std::exp(e);
	return gauss;
}

vect make_vect(double x, double y){
	vect v(x, y);
	return v;
}
}

