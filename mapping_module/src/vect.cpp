#include<map.hpp>
#include<cmath>
#include<stdexcept>
using namespace std;

double vect :: length(){
	return sqrt(x*x + y*y);
}

vect operator+(vect a, vect b){	
	vect sum;
	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return sum;
}

vect operator*(vect a, double scalar){	
	vect prod;
	prod.x = a.x*scalar;
	prod.y = a.y*scalar;
	return prod;
}

vect operator/(vect a, double scalar){	
	vect div;
	double eps = 1e-9;
	if (abs(scalar) < eps) {
		throw runtime_error("Math error: divide by 0 encountered");
	}
	div.x = a.x/scalar;
	div.y = a.y/scalar;
	return div;
}

double operator*(vect a, vect b){	
	double dot;
	dot = a.x*b.x + a.y*b.y;
	return dot;
}

