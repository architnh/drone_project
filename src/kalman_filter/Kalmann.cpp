#include "Kalman.h"

Kalman::Kalman() {
  Q_theta = 0.001;
  Q_theta_dot_bias = 0.003;
  R = 0.03;

  theta = 0.0;
  theta_dot_bias = 0.0;

  P[0][0] = 1000000.0;
  P[0][1] = 1000000.0;
  P[1][0] = 1000000.0;
  P[1][1] = 1000000.0;
};

float Kalman::apply_filter(float theta_measured, float theta_dot, float dt){
  dtheta_dt = theta_dot - theta_dot_bias;
  theta = theta + dt*dtheta_dt;

  P[0][0] = P[0][0] + dt*(dt*P[1][1]-P[0][1]-P[1][0]+Q_theta);
  P[0][1] = P[0][1] - dt*P[1][1];
  P[1][0] = P[1][0] - dt*P[1][1];
  P[1][1] = P[1][1] + dt*Q_theta_dot_bias;

  float innovation = theta_measured - theta; // Innovation --> \hat{y_{k}} = z_{k} - theta_{k|k-1} 

  float S = P[0][0] + R;

  float K[2];
  K[0] = P[0][0]/S;
  K[1] = P[1][0]/S;

  theta          = theta          + K[0]*innovation;
  theta_dot_bias = theta_dot_bias + K[1]*innovation;

  float P_00_old = P[0][0];
  float P_01_old = P[0][1];

  P[0][0] = P[0][0] - K[0]*P_00_old;
  P[0][1] = P[0][1] - K[0]*P_01_old;
  P[1][0] = P[1][0] - K[1]*P_00_old;
  P[1][1] = P[1][1] - K[1]*P_01_old;

  return theta;
};

void Kalman::set_theta(float theta) { this->theta = theta; }; // Used to set angle, this should be set as the starting angle
float Kalman::get_dtheta_dt() { return this->dtheta_dt; }; // Return the unbiased rate

/* These are used to tune the Kalman filter */
void Kalman::set_Q_theta(float Q_theta) { this->Q_theta = Q_theta; };
void Kalman::set_Q_theta_dot_bias(float Q_theta_dot_bias) { this->Q_theta_dot_bias = Q_theta_dot_bias; };
void Kalman::set_R(float R) { this->R = R; };

float Kalman::get_Q_theta() { return this->Q_theta; };
float Kalman::get_Q_theta_dot_bias() { return this->Q_theta_dot_bias; };
float Kalman::get_R() { return this->R; };