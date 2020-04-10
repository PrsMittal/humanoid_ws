#pragma once
#include<utility>
#include<vector>
#include<cmath>
#include<vect.hpp>
#include<obstacle.hpp>
#include<functions.hpp>
namespace huroiitk{

enum class TYPE{WALL, WELL, GATE, WEIGHT, GOAL_LINE, GOAL_POINT};
enum class BOT_STATUS{STANDING, SITTING, GROUNDED};
enum class METHOD{GAUSSIAN,COULOMBIC};

//////////////////////// class field ///////////////////////////////

class field{
	public:
		field(bot automi): automi(automi){}
		virtual void update(vect loc, TYPE type, bool bot_coordinates=true) = 0;
		//virtual std::vector <std::Pair <object, double>> get_nearest_objects(double range, double spread=360) = 0; //vector <object, distance from bot>  
		//simple potential for short area
		virtual vect total_potential(const vect& p,METHOD Method) = 0;
		//integre for a large area
		virtual vect total_potential(const vect& p, const double& size, const int& n,METHOD Method) = 0;

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
		vect total_potential(const vect& p, METHOD Method);
		vect total_potential(const vect& p, const double& size, const int& n,METHOD Method);

		vect gradient(const vect& p);

	double w, len;
	std::vector <wall> walls;
	std::vector <well> wells;
	std::vector <door> doors;
	goal_line goal;
};
}