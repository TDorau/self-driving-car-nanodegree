#include "kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
  TODO:
    * predict the state
  */
	// x = F * x_ section 8 in lesson 5
	//MaitrxXd Ft = F_.transpose(); section 9 in lesosn 5
	// P_ = F_*P_*Ft+Q_;  	
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
  TODO:
    * update the state by using Kalman Filter equations (LIDAR)
  */
	/*
	In Section 7 of lesson 5
	VectorXd y = z - H * x;
	MatrixXd Ht = H.transpose();
	MatrixXd S = H * P * Ht + R;
	MatrixXd Si = S.inverse();
	MatrixXd K = P * Ht * Si;

	// new state

	x = x + (K * y);
	P = (I - K * H) * P;

	//KF Prediction step

	x = F * x + u;
	MatrixXd Ft = F.transpose();
	P = F * P * Ft + Q;


	*/
}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
  TODO:
    * update the state by using Extended Kalman Filter equations (RADAR)
  */
    /*
	// Section 14 of lesson 5.
	float x = ekf_.x(0);
	float y = ekf_.x_(1);
	float vx = ekf_.x_(2);
	float vy = ekf_.x_(3);

	float rho =  sqrt(x*x+y*y);
	float theta = atan2(y,x);
	float ro_dot = (x*vx+y*vy)/rho
	VectorXd z_pred = VectorXd(3);
	z_pred << rho, theta, ro_dot;

	VectorXd y = z - z_pred;

	// In section 7 of lesson 5
	MatrixXd Ht = H.transpose();
	MatrixXd S = H * P * Ht + R;
	MatrixXd Si = S.inverse();
	MatrixXd K = P * Ht * Si;

	// new state

	x = x + (K * y);
	P = (I - K * H) * P;

	x = F * x + u;
	MatrixXd Ft = F.transpose();
	P = F * P * Ft + Q;
    */

}
