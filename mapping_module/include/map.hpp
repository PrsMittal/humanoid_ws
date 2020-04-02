#include<utility>
#include<vector>

#ifndef _MAP_H__
#define _MAP_H__

enum TYPE{WALL, WELL, GATE, WEIGHT, GOAL_LINE, GOAL_POINT};
enum BOT_STATUS{STANDING, SITTING, GROUNDED};

class vect {		//vector implementation of point.
	public:
		vect(double x=0.0, double y=0.0): x(x), y(y), radial(true){}
		vect(bool radial): x(0.0), y(0.0), radial(radial){}
		vect(double x, double y, bool radial): x(x), y(y), radial(radial){}

		double length();
		
		friend vect operator+(vect a, vect b);
		
		//friend vect operator*(double scalar);

		//friend vect operator/(double scalar);
	
		//friend double operator*(vect p);	//dot product
		//friend vect operator^(vect p);	//cross product
	private:
	double x, y;
	bool radial;
};

class object{
	public:
		const TYPE type;	
		virtual object(vect p, TYPE type): center(p), type(type){}
		virtual double potential(vect p);
		virtual vect center(){return _center;}
	protected:
		const vect _center;
};


class wall : public object {
	public:
		wall(vect p, vect bp1, double w, double h, double t): center(p), bp1(bp1), w(w), h(h), t(t){}
		wall(vect bp1, vect bp2, double h, double t): bp1(bp1), bp2(bp2), h(h), t(t){
			center = (bp1 + bp2)/2;
		}

		double potential(vect p); //elliptical potential field 

	private:
		const double w, h, t;
		vect bp1, bp2;
};

/*
class well : public object {
	public: 
		well(vect p, double r): center(p), r(r){}

	private:
		const double r;
};

class door : public object {
	public:
		door(vect p, double w, double h): center(p), w(w), h(h){}
	
	private:
		const double w, h;
};

class weight : public object {
	public:
		weight(vect p, double len)
	
	private:
		const double len;
};

class goal_point : public object {
	public: 
		goal_point(vect p);
		potential()
};

class goal_line : public object {

};

class bot{
	public:
		bot(vect loc, double theta=0): loc(loc), theta(theta){}
		
		vect location(){return loc};
		double orientation(){return theta};	

	protected:
		vect loc;		//position in field coordiantes
		double theta;		//orientation in self coordiantes
		BOT_STATUS stat;	//the condition bot is in rn
};

class field{
	public:
		virtual field() = 0;
		virtual void update(vect loc, Type type, bool bot_coordinates=true);
		//virtual void update_bot_position(vect loc);
		virtual std::vector <std::Pair <object, double>> get_nearest_objects(double range, bool iscircle=true);
		virtual bool within_field(vect p)
	protected:
		std::vector <std::Pair <object, double>> Obstacles;
		bot automi;
		object goal;
};

class square_field : public field {
	public: 
		square_field(double w, double len): w(w), len(len){}
		void update();
		void update_bot_position();

	private: 
		double w, len;
		
};	


*/
#endif 	// header _MAP_H__
