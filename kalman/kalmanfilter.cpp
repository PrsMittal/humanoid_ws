/*
    state variables => X=[x,y,θ].T 
    measuerement => Z=[x,y,θ].T
    process => rotate_by_theta then move_n_steps
    constants => step_length = l ± e
    model update equations
        θ := θ + rotation
        x := x + n*l*sinθ
        y := y + n*l*cosθ
*/


#include "kalmanfilter.h"
#include <cmath>

void KalmanFilter::start(
  const int nin, const VectorXd& xin, const MatrixXd& Pin, const MatrixXd& Fin, const MatrixXd& Qin){

  _n = nin;
  _I = MatrixXd::Identity(_n, _n);
  _x = xin;
  _P = Pin;
  _F = Fin;
  _Q = Qin;
}

void KalmanFilter::setQ(const MatrixXd& Qin){
  _Q = Qin;
}

void KalmanFilter::updateF(VectorXd u){
  _F(0,0)= 1;
  _F(0,1)= 0;
  _F(0,2)= step_length * u[0] * cos(_x(2));
  _F(1,0)= 0;
  _F(1,1)= 1;
  _F(1,2)= (-1) * step_length * u[0] * sin(_x(2));
  _F(2,0)= 0;
  _F(2,1)= 0;
  _F(2,2)= 1;
}

VectorXd KalmanFilter::get_resulting_state() const{
  return _x;
}

void KalmanFilter::predict(VectorXd u){
  VectorXd temp((step_length*u[0]*sin(u[1])),(step_length*u[0]*cos(u[1])),(u[1])];
  _x = _x + temp;
  KalmanFilter::updateF(VectorXd u);
  _P = _F * _P * _F.transpose() + _Q;
}

void KalmanFilter::update(const VectorXd& z, const MatrixXd& R){

  // const MatrixXd PHt = _P * H.transpose();
  const MatrixXd S = _P + R;
  const MatrixXd K = _P * S.inverse();
  VectorXd y = z - _x;

  _x = _x + K * y;
  _P = (_I - K) * _P;
}
