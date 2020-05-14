#pragma once
#include<utility>
#include<vector>
#include<cmath>
#include<vect.hpp>
#include<obstacle.hpp>
#include<functions.hpp>
namespace huroiitk{

	template<typename vect_t>
	class bot{
		public:
			bot(const vect_t& loc=make_vect(0, 0), const vect_t& orient=make_vect(0, 1)): pos(pos), orient(orient), stat(BOT_STATUS::STANDING){}
		
			void update_bot_position(const vect_t& dp);
			void update_bot_orientation(const vect_t& dtheta);
			void update_bot_orientation(const double& rot_angle); 		//angle in radians.

		vect_t pos;		//position in field coordiantes
		vect_t orient;		//unit vector in direction the bot is facing.
		BOT_STATUS stat;	//the condition bot is in rn
	};

	//////////////////////// class field ///////////////////////////////

	template<typename vect_t>
	class field{
		public:
			field(bot automi): automi(automi){}
			virtual void update(vect_t loc, TYPE type, bool bot_coordinates=true) = 0; 
			//simple potential for short area
			virtual vect_t total_potential(const vect_t& p, METHOD Method=METHOD::COULOMBIC) = 0;
			//integer for a large area
			virtual vect_t total_potential(const vect_t& p, const double& size, const int& n, METHOD Method=METHOD::COULOMBIC) = 0;

			virtual vect_t gradient(const vect_t& p) = 0;		// returns gradient of potential in a 3x3 grid around given point. 
				
		bot automi;
	};

	template<typename vect_t>
	class obstacle_field : public field {
		public: 
			obstacle_field(const bot& automi, const goal_line& goal, const double& w, const double& len):
				field(automi), goal(goal), w(w), len(len){}
			void update(vect_t loc, TYPE type, bool bot_coordinates=true){return;}
			vect_t total_potential(const vect_t& p, METHOD Method=METHOD::COULOMBIC);
			vect_t total_potential(const vect_t& p, const double& size, const int& n,METHOD Method=METHOD::COULOMBIC);

			vect_t gradient(const vect_t& p);

		double w, len;
		std::vector <wall> walls;
		std::vector <well> wells;
		std::vector <door> doors;
		goal_line goal;
	};
}
