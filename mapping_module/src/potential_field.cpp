#include<map.hpp>
#include<vector>  

void bot :: update_bot_position(const vect& dp){
	pos += dp;
	return;
}

void bot :: update_bot_orientation(const vect& dtheta){
	orient += dtheta;
	orient = orient/(orient.length());
	return;
}

void bot :: update_bot_orientation(const double& rot_angle){
	orient = 0; 	//complete this
	return;
}

double field :: total_potential(const vect& p){
	//run over all obstacles in the field -_- 
	double potential = 0;
	for (auto obstacle : obstacles){
		potential += obstacle.potential(p);	
		//should we use integral over an area instead?
	}
	return potential;
}

vect field :: gradient(const vect p){
	
 


