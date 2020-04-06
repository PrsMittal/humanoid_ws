#include<map.hpp>
#include<cmath>

#ifndef _gaussian(double d, double sig)
double _gaussian(double d, double sig){
	double e = -((d/sig)*(d/sig)/2);
	double gauss = (1/(sig * sqrt(M_PI * 2))) * exp(e);
	return gauss;
}
#endif

wall :: potential(vect p){
       vect c = center();

       
