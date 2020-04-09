#include<utility>
#include<vector>
#include<cmath>

#ifndef _MAP_H__
#define _MAP_H__

enum TYPE{WALL, WELL, GATE, WEIGHT, GOAL_LINE, GOAL_POINT};
enum BOT_STATUS{STANDING, SITTING, GROUNDED};

double _gaussian(const double& d, const double& sig);

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

vect make_vect(double x, double y);

///////////////////////  class object  ////////////////////////////

class object{
	public:	
		object(vect p, TYPE type): center(p), type(type){}
		virtual vect potential(const vect& p) = 0;
		virtual double distance(const vect& p) = 0;

	const vect center;
	const TYPE type;
};


class wall : public object {
	public:
		wall(vect p, vect bp1, double w, double h, double t): 
			object(p, WALL), bp1(bp1), 
			bp2(bp1 + (p-bp1)*2), 
			w(w), h(h), t(t){}

		wall(vect bp1, vect bp2, double h, double t): 
			object((bp1 + bp2)/2, WALL),	
			bp1(bp1), bp2(bp2), h(h), t(t), 
			w((bp1-bp2).length()){}

		vect potential(const vect& p); //elliptical potential field 
		double distance(const vect& p){double d = (p - center).length(); return d;}
	
	const double w, h, t;
	const vect bp1, bp2;
};

class well : public object {
	public: 
		well(vect p, double r): 
			object(p, WELL), r(r){}

		vect potential(const vect& p); //circular potential field
		double distance(const vect& p){double d = (p-center).length(); return d;}


	const double r;
};

class door : public object {
	public:
		door(vect p, vect f1, double w, double h): 
			object(p, GATE), w(w), f1(f1),   
			f2(f1 + (p-f1)*2), h(h){}

		door(vect f1, vect f2, double h):
			object((f1+f2)/2, GATE), 
			f1(f1), f2(f2), w((f2-f1).length()), 
			h(h){}

	vect potential(const vect& p); //potential = d^2 * gaussian(d, sig), d= distance of point from center. Can something work better?? 
	double distance(const vect& p){double d = (p-center).length(); return d;}

	const double w, h;
	const vect f1, f2;	//f1 and f2 are the mid extreme points on the door(focal points for the hyperbola)
};

class goal_line : public object {
	public: 
		goal_line(vect c, double l, double theta): 
			object(c, GOAL_LINE), length(l), orient(theta){}	
		goal_line(vect p1, vect p2):
			object((p1+p2)/2.0, GOAL_LINE), 
			length((p1-p2).length()), orient((p1-p2).arg()){}
	    	double distance(const vect& p);
		vect potential(const vect& p);

	double orient, length;
};

///////////////////////// class robot /////////////////////////////

class bot{
	public:
		bot(const vect& loc=make_vect(0, 0), const vect& orient=make_vect(0, 1)): pos(pos), orient(orient), stat(STANDING){}
		
		//bot(){}
		//vect location(){return loc};			//not needed now, baad me dekhege
		//double orientation(){return theta};
		void update_bot_position(const vect& dp);
		void update_bot_orientation(const vect& dtheta);
		void update_bot_orientation(const double& rot_angle); 		//angle in radians.

	vect pos;		//position in field coordiantes
	vect orient;		//unit vector in direction the bot is facing.
	BOT_STATUS stat;	//the condition bot is in rn
};


//////////////////////// class field ///////////////////////////////

class field{
	public:
		field(bot automi): automi(automi){}
		virtual void update(vect loc, TYPE type, bool bot_coordinates=true) = 0;
		//virtual std::vector <std::Pair <object, double>> get_nearest_objects(double range, double spread=360) = 0; //vector <object, distance from bot>  
		//simple potential for short area
		virtual vect total_potential(const vect& p) = 0;
		//integre for a large area
		virtual vect total_potential(const vect& p, const double& size, const int& n) = 0;

		virtual vect gradient(const vect& p) = 0;		// returns gradient of potential in a 3x3 grid around given point. 
			
	//std::vector <object*> Obstacles;
	bot automi;
	//object* goal;
};


class obstacle_field : public field {
	public: 
		obstacle_field(const bot& automi, const goal_line& goal, const double& w, const double& len):
			field(automi), goal(goal), w(w), len(len){}
		void update(vect loc, TYPE type, bool bot_coordinates=true){return;}
		vect total_potential(const vect& p);
		vect total_potential(const vect& p, const double& size, const int& n);

		vect gradient(const vect& p);

	double w, len;
	std::vector <wall> walls;
	std::vector <well> wells;
	std::vector <door> doors;
	goal_line goal;
};

#endif 	// header _MAP_H__
