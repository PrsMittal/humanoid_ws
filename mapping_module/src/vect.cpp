#include<map.hpp>
#include<cmath>
#include<stdexcept>
#include<iostream>
using namespace std;

double vect :: length(){
	return sqrt(x*x + y*y);
}

double vect :: arg(){
	return atan(y/(x+1e-7)) * (180/M_PI);
}

vect operator+(const vect& a, const vect& b){	
	vect sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return sum;
}

vect operator*(const vect& a, const double& scalar){	
	vect prod;
	prod.x = a.x*scalar;
	prod.y = a.y*scalar;
	return prod;
}

vect operator*(const double& scalar, const vect& a){
        vect prod;
        prod.x = a.x*scalar;
        prod.y = a.y*scalar;
        return prod;
}

vect operator/(const vect& a, const double& scalar){	
	vect div;
	double eps = 1e-7;
	if (abs(scalar) < eps) {
		//throw runtime_error("Math error: divide by 0 encountered");
	}
	div.x = a.x/(scalar+eps);
	div.y = a.y/(scalar+eps);
	return div;
}

double operator*(const vect& a, const vect& b){	
	double dot;
	dot = a.x*b.x + a.y*b.y;
	return dot;
}

vect operator-(const vect& a){
	vect neg;
	neg.x = -a.x;
	neg.y = -a.y;
	return neg;
}

vect operator-(const vect& a, const vect& b){
	vect sum;
	sum.x = a.x - b.x;
	sum.y = a.y - b.y;
	return sum;
}





