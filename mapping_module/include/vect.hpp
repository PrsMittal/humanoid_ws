#pragma once
#include<utility>
#include<vector>
#include<cmath>
namespace huroiitk{
	
	class vect {		//vector implementation of point.
		public:
			vect(double x=0.0, double y=0.0): x(x), y(y){}

			double length();
			double arg();
			
			friend vect operator+(const vect& a, const vect& b);
			
			friend vect operator*(const vect& a, const double& scalar);
			friend vect operator*(const double& scalar, const vect& a);

			friend vect operator/(const vect& a, const double& scalar);
		
			friend double operator*(const vect& a, const vect& b);	//dot product
			
			friend vect operator-(const vect& a);		//negation 

			friend vect operator-(const vect& a, const vect& b);

		//	friend vect operator^(vect p);	//cross product //lol not viable for 2D
		
		double x, y;
	};
}
