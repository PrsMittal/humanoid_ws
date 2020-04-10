#pragma once
#include<utility>
#include<vector>
#include<cmath>
#include<vect.hpp>
#include<functions.hpp>

namespace huroiitk{
    
    double _gaussian(const double& d, const double& sig);
    vect make_vect(double x, double y);
    inline double _inverse(const double d, const double k);
}
