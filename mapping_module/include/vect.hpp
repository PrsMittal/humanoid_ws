#pragma once
#include<utility>
#include<vector>
#include<cmath>
namespace huroiitk{
	
	class vect2D {		//vector implementation of point.
		public:
			vect2D(double x=0.0, double y=0.0): x(x), y(y){}

			virtual double length();
			virtual double arg();
			
			friend vect2D operator+(const vect2D& a, const vect2D& b);
			
			friend vect2D operator*(const vect2D& a, const double& scalar);
			friend vect2D operator*(const double& scalar, const vect2D& a);

			friend vect2D operator/(const vect2D& a, const double& scalar);
		
			friend double operator*(const vect2D& a, const vect2D& b);	//dot product
			
			friend vect2D operator-(const vect2D& a);		//negation 

			friend vect2D operator-(const vect2D& a, const vect2D& b);

		//	friend vect operator^(vect p);	//cross product //lol not viable for 2D
		protected:
			const double x, y;
	};

	class vect3D : public vect2D{
		public:
			vect3D(double x=0.0, double y=0.0, double z=0.0): vect2D(x, y), z(z){}
			double length();
			//note that arg() is not valid for 3D vectors.
			//define operator overloads for 3D vector.


		protected: 
			const double z;
	};
}
