#include<iostream>
#include<map.hpp>
#include<vector>
using namespace std;

int main(){
	/*
	cout << "vect test" << endl;
	vect v1(10.0, 30.0), v2(20.0, 30.0);
	vect v = v1+v2;
	v = v*2;
	v = v/3;
	cout << v.x << endl;
	cout << v*v << endl;
	v1 = make_vect(-10, 0);
	cout << v1.y << endl;
	cout << (v - v1).length() << endl << endl;

	cout << "object :: wall test" << endl;
	vector<object*> obstacles;
	door w(make_vect(10, 20), make_vect(10, 30), 20, 5);
	obstacles.push_back(&w);
	cout << obstacles[0]->distance(make_vect(5, 20)) << endl;
	cout << obstacles[0]->potential(make_vect(10, 20)) << " " << obstacles[0]->potential(make_vect(10, 30)) << endl;
	*/
	
	bot automi;
	goal_line goal(make_vect(-50, 200), make_vect(50, 200));
	
	obstacle_field game(automi, goal, 100, 200);	
	wall w1(make_vect(-11, 50), make_vect(9, 50), 10, 5);
	wall w2(make_vect(-10, 150), make_vect(10, 150), 10, 5);
	wall w3(make_vect(0, 100), make_vect(20, 100), 10, 5);

	game.walls.push_back(w1);
	game.walls.push_back(w2);
	game.walls.push_back(w3);
	double step = 5;

	while (game.automi.pos.y < 200){
		vect grad = game.total_potential(game.automi.pos);
		// cout << game.goal.potential(make_vect(0, 0)).length() << " " << grad.y;
		//cout << grad.length() << endl;
		game.automi.orient = grad/grad.length();
		game.automi.pos = game.automi.pos + step*grad/grad.length();
		cout << game.automi.pos.x << " " << game.automi.pos.y << endl;
	}

	return 0;
}
