#include<iostream>
#include<map.hpp>
#include<vector>
using namespace std;

int main(){
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
	return 0;
}
