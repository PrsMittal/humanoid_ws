#pragma once
#include<utility>
#include<vector>
#include<cmath>
#include<functions.hpp>
#include<vect.hpp>
#include<obstacle.hpp>

namespace huroiitk{

	enum class TYPE{WALL, WELL, GATE, WEIGHT, GOAL_LINE, GOAL_POINT};
	enum class BOT_STATUS{STANDING, SITTING, GROUNDED};
	enum class METHOD{GAUSSIAN,COULOMBIC};

	///////////////////////  class object  ////////////////////////////

	class object{
		public:	
			object(vect p, TYPE type): center(p), type(type){}
			virtual vect potential(const vect& p, METHOD Method=METHOD::COULOMBIC) = 0;
			virtual double distance(const vect& p) = 0;

		const vect center;
		const TYPE type;
	};


	class wall : public object {
		public:
			wall(vect p, vect bp1, double w, double h, double t): 
				object(p, TYPE::WALL), bp1(bp1), 
				bp2(bp1 + (p-bp1)*2), 
				w(w), h(h), t(t){}

			wall(vect bp1, vect bp2, double h, double t): 
				object((bp1 + bp2)/2, TYPE::WALL),	
				bp1(bp1), bp2(bp2), h(h), t(t), 
				w((bp1-bp2).length()){}

			vect potential(const vect& p, METHOD Method=METHOD::COULOMBIC); //elliptical potential field 
			double distance(const vect& p){double d = (p - center).length(); return d;}
		
		const double w, h, t;
		const vect bp1, bp2;
	};

	class well : public object {
		public: 
			well(vect p, double r): 
				object(p, TYPE::WELL), r(r){}

			vect potential(const vect& p, METHOD Method=METHOD::COULOMBIC); //circular potential field
			double distance(const vect& p){double d = (p-center).length(); return d;}


		const double r;
	};

	class door : public object {
		public:
			door(vect p, vect f1, double w, double h): 
				object(p, TYPE::GATE), w(w), f1(f1),   
				f2(f1 + (p-f1)*2), h(h){}

			door(vect f1, vect f2, double h):
				object((f1+f2)/2, TYPE::GATE), 
				f1(f1), f2(f2), w((f2-f1).length()), 
				h(h){}

		vect potential(const vect& p, METHOD Method=METHOD::COULOMBIC); //potential = d^2 * gaussian(d, sig), d= distance of point from center. Can something work better?? 
		double distance(const vect& p){double d = (p-center).length(); return d;}

		const double w, h;
		const vect f1, f2;	//f1 and f2 are the mid extreme points on the door(focal points for the hyperbola)
	};

	class goal_line : public object {
		public: 
			goal_line(vect c, double l, double theta): 
				object(c, TYPE::GOAL_LINE), length(l), orient(theta){}	
			goal_line(vect p1, vect p2):
				object((p1+p2)/2.0, TYPE::GOAL_LINE), 
				length((p1-p2).length()), orient((p1-p2).arg()){}
				double distance(const vect& p);
			vect potential(const vect& p, METHOD method=METHOD::COULOMBIC);

		double orient, length;
	};


}
