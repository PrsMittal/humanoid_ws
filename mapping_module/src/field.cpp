//#include<map.hpp>
#include<field.hpp>
#include<vector>  
#include<iostream>
namespace huroiitk{
enum class METHOD{GAUSSIAN,COULOMBIC};
const int THRESH = 30;

void bot :: update_bot_position(const vect& dp){
	pos = pos + dp;
	return;
}

void bot :: update_bot_orientation(const vect& dtheta){
	orient = orient + dtheta;
	orient = orient/(orient.length());
	return;
}

void bot :: update_bot_orientation(const double& rot_angle){
	orient = 0; 	//complete this
	return;
}

vect obstacle_field :: total_potential(const vect& p, METHOD Method){
 	//run over all obstacles in the field -_- 
 	vect potential(0,0);
 	for (auto wall : walls){
 		if (wall.distance(p) < THRESH)
		potential = potential + wall.potential(p);	
 	}
	for (auto well : wells){
                if (well.distance(p) < THRESH)
		potential = potential + well.potential(p);
        }
	for (auto door : doors){
		if (door.distance(p) < THRESH)
                potential = potential + door.potential(p);
        }

	potential = potential + goal.potential(p);
 	return potential;
}

vect obstacle_field :: total_potential(const vect& p, const double& size, const int& n, METHOD Method){

	vect potential;
	int unit=int(size/n);
	
	for(auto wall: walls){
		if (wall.distance(p) > THRESH){
			continue;
		}
		for(int i=0 ;i<int(size/2) ;i+=unit ){
			for(int j=0; j<int(size/2); j+=unit ){
			
				potential = potential + wall.potential(make_vect( p.x-i,p.y-j));
				potential = potential + wall.potential(make_vect( p.x+i,p.y+j));
				potential = potential + wall.potential(make_vect( p.x-i,p.y+j));
				potential = potential + wall.potential(make_vect( p.x+i,p.y-j));
			}
		}
	}

	for(auto well: wells){
                if (well.distance(p) > THRESH){
                        continue;
                }
		for(int i=0 ;i<int(size/2) ;i+=unit ){
                        for(int j=0; j<int(size/2); j+=unit ){

                                potential = potential + well.potential(make_vect( p.x-i,p.y-j));
                                potential = potential + well.potential(make_vect( p.x+i,p.y+j));
                                potential = potential + well.potential(make_vect( p.x-i,p.y+j));
                                potential = potential + well.potential(make_vect( p.x+i,p.y-j));
                        }
                }
        }

	for(auto door: doors){
                if (door.distance(p) > THRESH){
                        continue;
                }
		for(int i=0 ;i<int(size/2) ;i+=unit ){
                        for(int j=0; j<int(size/2); j+=unit ){

                                potential = potential + door.potential(make_vect( p.x-i,p.y-j));
                                potential = potential + door.potential(make_vect( p.x+i,p.y+j));
                                potential = potential + door.potential(make_vect( p.x-i,p.y+j));
                                potential = potential + door.potential(make_vect( p.x+i,p.y-j));
                        }
                }
        }

	for(int i=0 ;i<int(size/2) ;i+=unit ){
		for(int j=0; j<int(size/2); j+=unit ){
			potential = potential + goal.potential(make_vect( p.x-i,p.y-j));
			potential = potential + goal.potential(make_vect( p.x+i,p.y+j));
			potential = potential + goal.potential(make_vect( p.x-i,p.y+j));
			potential = potential + goal.potential(make_vect( p.x+i,p.y-j));
                }
        }

	return potential;
}

vect obstacle_field :: gradient(const vect& p){
	vect grad;
	// double potential[3][3];
	// for (int i=0; i<3; i++){
	// 	potential[i][0] = total_potential(make_vect(p.x-range, py+(i-1)*range), size, n);
	// 	potential[i][1] = total_potential(make_vect(p.x, py+(i-1)*range), size, n);
	//        	potential[i][2] = total_potential(make_vect(p.x+range, py+(i-1)*range), size, n);
	// }
	// int x, y;

	return grad;
}
}
 


