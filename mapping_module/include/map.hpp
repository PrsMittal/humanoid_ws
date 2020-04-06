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
		
		friend vect operator+(const vect& a, const vect& b);
		
		friend vect operator*(const vect& a, const double& scalar);

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
		virtual double potential(const vect& p) = 0;
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

		double potential(const vect& p); //elliptical potential field 
		double distance(const vect& p){double d = (p - center).length(); return d;}
	
	const double w, h, t;
	const vect bp1, bp2;
};

/*

class well : public object {
	public: 
		well(vect p, double r): center(p), r(r){}

	const double r;
};

class door : public object {
	public:
		door(vect p, double w, double h): center(p), w(w), h(h){}
	
	const double w, h;
};

class weight : public object {
	public:
		weight(vect p, double len)
	
	const double len;
};

class goal_point : public object {
	public: 
		goal_point(vect p);
		potential()
};

class goal_line : public object {

};

///////////////////////// class robot /////////////////////////////

class bot{
	public:
		bot(vect loc, double theta=0): loc(loc), theta(theta){}
		
		//vect location(){return loc};			//not needed now, baad me dekhege
		//double orientation(){return theta};	

	vect loc;		//position in field coordiantes
	double theta;		//orientation in self coordiantes
	BOT_STATUS stat;	//the condition bot is in rn
};


//////////////////////// class field ///////////////////////////////

class field{
	public:
		virtual field() = 0;
		virtual void update(vect loc, Type type, bool bot_coordinates=true);
		//virtual void update_bot_position(vect loc);
		virtual std::vector <std::Pair <object, double>> get_nearest_objects(double range, bool iscircle=true);
		virtual bool within_field(vect p)
	
	std::vector <std::Pair <object, double>> Obstacles;
	bot automi;
	object goal;
};

class square_field : public field {
	public: 
		square_field(double w, double len): w(w), len(len){}
		void update();
		void update_bot_position();

	double w, len;
		
};	
*/

#endif 	// header _MAP_H__
