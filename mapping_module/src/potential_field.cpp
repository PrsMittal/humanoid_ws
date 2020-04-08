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

// double field :: total_potential(const vect& p){
// 	//run over all obstacles in the field -_- 
// 	double potential = 0;
// 	for (auto obstacle : obstacles){
// 		potential += obstacle.potential(p);	
// 		//should we use integral over an area instead?
// 	}
// 	return potential;
// }
double field :: total_potential(const vect& p,double size,int n){

	double potential=0;
	int i,j,k;
	int unit=int(size/n)
	//vect temp=vect make_vect(p.x,p.y);
	//object obstacle;
	//std::vector <object*> Obstacles;
	int l=Obstacles.size();
	
	
	for( k=0;k<l;k++){

		
		for( i=0 ;i<int(size/2) ;i+=unit ){

			for( j=0; j<int(size/2); j+=unit ){
			
				potential+=Obstacles[k]->potential(make_vect( p.x-i,p.y-j));
				potential+=Obstacles[k]->potential(make_vect( p.x+i,p.y+j));
				potential+=Obstacles[k]->potential(make_vect( p.x-i,p.y+j));
				potential+=Obstacles[k]->potential(make_vect( p.x+i,p.y-j));
			}
		}
	}

	return potential;
}

vect field :: gradient(const vect p){
	
 


