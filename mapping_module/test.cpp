#include<iostream>
#include<map.hpp>
using namespace std;

int main(){
	vect v1(10.0, 20.0), v2(20.0, 30.0);
	vect v = v1+v2;
	cout << v.x;
	return 0;
}
