#include<map.hpp>
#include<cmath>
using namespace std;
#ifndef _C_PI__
#define _C_PI__

const double PI = 3.14159265;
#endif	// constant PI 

double vect :: length(){
	return sqrt(x*x + y*y);
}

vect operator+(vect a, vect b){	
	vect sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return sum;
}
