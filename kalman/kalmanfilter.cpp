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

void KalmanFilter::updateF(const double dt){
  /*code*/
}

VectorXd KalmanFilter::get_resulting_state() const{
  return _x;
}

void KalmanFilter::predict(){
  _x = _F * _x;
  _P = _F * _P * _F.transpose() + _Q;
}

void KalmanFilter::update(const VectorXd& z, const MatrixXd& H, const VectorXd& Hx, const MatrixXd& R){

  const MatrixXd PHt = _P * H.transpose();
  const MatrixXd S = H * PHt + R;
  const MatrixXd K = PHt * S.inverse();
  VectorXd y = z - Hx;

  _x = _x + K * y;
  _P = (_I - K * H) * _P;
}