#pragma once
#include<utility>
#include<vector>
#include<cmath>
#include<vect.hpp>
#include<obstacle.hpp>
#include<functions.hpp>
namespace huroiitk{

	class bot{
		public:
			bot(const vect& loc=make_vect(0, 0), const vect& orient=make_vect(0, 1)): pos(pos), orient(orient), stat(BOT_STATUS::STANDING){}
		
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
			//simple potential for short area
			virtual vect total_potential(const vect& p, METHOD Method=METHOD::COULOMBIC) = 0;
			//integre for a large area
			virtual vect total_potential(const vect& p, const double& size, const int& n, METHOD Method=METHOD::COULOMBIC) = 0;

			virtual vect gradient(const vect& p) = 0;		// returns gradient of potential in a 3x3 grid around given point. 
				
		bot automi;
	};

	class obstacle_field : public field {
		public: 
			obstacle_field(const bot& automi, const goal_line& goal, const double& w, const double& len):
				field(automi), goal(goal), w(w), len(len){}
			void update(vect loc, TYPE type, bool bot_coordinates=true){return;}
			vect total_potential(const vect& p, METHOD Method=METHOD::COULOMBIC);
			vect total_potential(const vect& p, const double& size, const int& n,METHOD Method=METHOD::COULOMBIC);

			vect gradient(const vect& p);

		double w, len;
		std::vector <wall> walls;
		std::vector <well> wells;
		std::vector <door> doors;
		goal_line goal;
	};
}
