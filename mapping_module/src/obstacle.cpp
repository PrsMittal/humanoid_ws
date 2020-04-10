#include<vect.hpp>
#include<functions.hpp>
#include<cmath>
#include<iostream>
#include<obstacle.hpp>

namespace huroiitk{
const double K_REP;
const double K_ATR;
vect wall :: potential(const vect& p, METHOD Method) {

	double d = (bp1 - p).length() + (bp2 - p).length();
	switch (Method)
	{
	case METHOD::GAUSSIAN:
	{
	double gauss = _gaussian(d - std::sqrt(w*w + t*t), 0.7071);
	return -gauss*((center-p)/(center-p).length());
	}
		break;
	case METHOD::COULOMBIC:
	{
		double inverse=_inverse(d,K_REP);
		return inverse;
	}
		break;
	// default:
	// 	break;
	}
	
}


vect well :: potential(const vect& p, METHOD Method) {
	double d = (p-center).length();
	switch (Method)
	{
	case METHOD::GAUSSIAN:
	{
	double gauss = _gaussian(std::max(d-r, 0.0), 0.7071);
	return -gauss*((center-p)/(center-p).length());
	}
		break;
	case METHOD::COULOMBIC:
	{
		double inverse= _inverse(d,K_REP);
		return inverse;
	}
		break;	
	// default:
	// 	break;
	}
	
}

vect door :: potential(const vect& p, METHOD Method) {
	double d = (p-center).length();
	switch (Method)
	{
	case METHOD::GAUSSIAN:
	{
	double gauss = (d*d)*_gaussian(d, w/(std::pow(2, 1.5)))/(w*w); //sigma will most probably be w/(2^(1.5))
	return -gauss*((center-p)/(center-p).length());
	}
		break;
	case METHOD::COULOMBIC:
	{
		double inverse=_inverse(d,K_REP);
		return inverse;
	}
		break;
	}
}

double goal_line :: distance(const vect& p) {
	double d = (p-center).length()*std::cos(orient*M_PI/180.0);
	return d;
}

vect goal_line :: potential(const vect& p, METHOD method){
	double d = distance(p);
	switch (Method)
	{
	case METHOD::GAUSSIAN:{
	vect normal = make_vect(-std::sin(orient), std::cos(orient));
	return 0.5*normal;
	}
		break;
	case METHOD::COULOMBIC:{
		double inverse=_inverse(d,K_ATR);
		return inverse;
	}
		break;
	// default:
	// 	break;
	}
	
}

}
