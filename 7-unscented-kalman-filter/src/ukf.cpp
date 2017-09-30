#include "ukf.h"
#include "Eigen/Dense"
#include <iostream>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

/**
 * Initializes Unscented Kalman filter
 */
UKF::UKF() {
  // if this is false, laser measurements will be ignored (except during init)
  use_laser_ = true;

  // if this is false, radar measurements will be ignored (except during init)
  use_radar_ = true;

  // initial state vector
  x_ = VectorXd(5);

  // initial covariance matrix
  P_ = MatrixXd(5, 5);

  // Process noise standard deviation longitudinal acceleration in m/s^2
  // need to be adjusted
  std_a_ = 30;

  // Process noise standard deviation yaw acceleration in rad/s^2
  // need to be adjusted
  std_yawdd_ = 30;

  // Laser measurement noise standard deviation position1 in m
  std_laspx_ = 0.15;

  // Laser measurement noise standard deviation position2 in m
  std_laspy_ = 0.15;

  // Radar measurement noise standard deviation radius in m
  std_radr_ = 0.3;

  // Radar measurement noise standard deviation angle in rad
  std_radphi_ = 0.03;

  // Radar measurement noise standard deviation radius change in m/s
  std_radrd_ = 0.3;

  /**
  TODO:

  Complete the initialization. See ukf.h for other member properties.

  Hint: one or more values initialized above might be wildly off...

  to initialize x and P see "What to expect form the project"
  */
}

UKF::~UKF() {}

/**
 * @param {MeasurementPackage} meas_package The latest measurement data of
 * either radar or laser.
 */
void UKF::ProcessMeasurement(MeasurementPackage meas_package) {
  /**
  TODO:

  Complete this function! Make sure you switch between lidar and radar
  measurements.

  For each line in the data file, ProcessMeasurement() gets called
  sending the sensor data to ukf.cpp
  */

	// Initialization structure similar to EKF project

	/*	
	if (!is_initialized_) {
		//Initialize x_, P_, previous_time, anything else needed.

		if (measurement_pack.sensor_type_ == MeasurementPackage::LASER) {
			// Initialize here
		}
		else if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
			// Initialize here
		}

		//Initialize anything else here(e.g. P_, anything else needed)
		previous_t = meas_package.timestamp_;
		is_initialized_ = true;
		return;		
	}
	
	// Control structure similar to EKF project
	delta_t = (meas_package.timestamp_ - previous_t)/1000000.0;
	Prediction(delta_t);

	if (meas_package.sensor_type_ == MeasurementPackage::LASER) {
		UpdateLidar(meas_package);
	}
	else if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
		UpdateRadar(meas_package);
	}
	previous_t = meas_package.timestamp_;
	*/
}

/**
 * Predicts sigma points, the state, and the state covariance matrix.
 * @param {double} delta_t the change in time (in seconds) between the last
 * measurement and this one.
 */
void UKF::Prediction(double delta_t) {
  /**
  TODO:

  Complete this function! Estimate the object's location. Modify the state
  vector, x_. Predict sigma points, the state, and the state covariance matrix.
  */
	/*
	//create Augmented Sigma Points
	//Lesson 7, section 18: Augmentation Assignment 2

	//create augmented mean state
	x_aug.head(5) = x;
	x_aug(5) = 0;
	x_aug(6) = 0;

	//create augmented covariance matrix
	P_aug.fill(0.0);
	P_aug.topLeftCorner(5,5) = P;
	P_aug(5,5) = std_a_*std_a_;
	P_aug(6,6) = std_yawdd_*std_yawdd_;

	//create squre root matrix
	MatrixXd L = P_aug.llt().matrixL();

	//create augmented sigma points
	Xsig_aug.col(0) = x_aug;
	for (int i = 0; i < n_aug; i++) {
		Xsig_aug.col(i+1) 		= x_aug + sqrt(lambda+n_aug) * L.col(i);
		Xsig_aug.col(i+1+n_aug) = x_aug - sqrt(lambda+n_aug) * L.col(i);
	}
	*/
	/*
	//Predict Sigma Points
	//Lesson 7, section 21: Sigma Point Prediction Assignment 2

	//predict sigma points
	for (int i = 0; i < 2*n_aug+1; i++) {
		//extract values for better readability
		double p_x = Xsig_aug(0,i);
		double p_y = Xsig_aug(1,i);
		double v = Xsig_aug(2,i);
		double yaw = Xsig_aug(3,i);
		double yawd = Xsig_aug(4,i);
		double nu_a = Xsig_aug(5,i);
		double nu_yawdd = Xsig_aug(7,i);

		//predicted state values
		double px_p, py_p;

		//avoid division by zero
		if (fabs(yawd) > 0.001) {
			px_p = p_x + v/yawd * (sin(yaw + yawd*delta_t) - sin(yaw));
			py_p = p_y + v/yawd * (cos(yaw) - cos(yaw + yawd*delta_t));
		}
		else {
			px_p = p_x + v * delta_t * cos(yaw);
			py_p = p_y + v * delta_t * sin(yaw);
		}

		double v_p = v;
		double yaw_p = yaw + yawd * delta_t;
		double yawd_p = yawd;

		//add noise
		px_p = px_p + 0.5*nu_a*delta_t*delta_t*cos(yaw);
		py_p = py_p + 0.5*nu_a*delta_t*delta_t*sin(yaw);
		v_p = v_p + nu_a * delta_t;

		yaw_p = yaw_p + 0.5*nu_yawdd*delta_t*delta_t;
		yawd_p = yawd_p + nu_yawdd * delta_t;

		//write predicted sigma point into right column
		Xsig_aug(0,i) = px_p;
		Xsig_aug(1,i) = py_p;
		Xsig_aug(2,i) = v_p;
		Xsig_aug(3,i) = yaw_p;
		Xsig_aug(4,i) = yawd_p;
	}
	*/

	/*
	//Predict mean and covariance
	//Lesson 7, section 24: Predicted Mean and Covariance Assignment 2

	//set weights
	double weight_0 = lambda/(lambda+n_aug);
	weights(0) = weight_0;
	for (int i=1; i<2*n_aug+1; i++) {
		//2n+1 weights
		double weight = 0.5/(n_aug+lambda);
		weights(i) = weight;
	}

	//predicted state mean
	x.fill(0.0);
	for ( int i = 0; i<2*n_aug+1; i++) {
		//iterate over sigma points
		x = x + weights(i) * Xsig_pred.col(i);
	}

	//predicted state covariance matrix
	P.fill(0.0);
	for (int i = 0; i<2*n_aug+1; i++) {
		//iterate over sigma points
		//state difference
		VectorXd x_diff = Xsig_pred.col(i) - x;
		//angle normalization
		while (x_diff(3) > M_PI) x_diff(3) -=2.*M_PI;
		while (x_diff(3) < M_PI) x_diff(3) +=2.*M_PI;

		P = P + weights(i) * x_diff * x_diff.transpose();
	}
	*/

}


/**
 * Updates the state and the state covariance matrix using a laser measurement.
 * @param {MeasurementPackage} meas_package
 */
void UKF::UpdateLidar(MeasurementPackage meas_package) {
  /**
  TODO:

  Complete this function! Use lidar data to update the belief about the object's
  position. Modify the state vector, x_, and covariance, P_.

  You'll also need to calculate the lidar NIS. NIS to be stored in NIS_laser_
  */
	//The mapping from state space to Lidar is linear.
	// bei der H Initialisierung Matrix(2,5) -> state space additional component
}

/**
 * Updates the state and the state covariance matrix using a radar measurement.
 * @param {MeasurementPackage} meas_package
 */
void UKF::UpdateRadar(MeasurementPackage meas_package) {
  /**
  TODO:

  Complete this function! Use radar data to update the belief about the object's
  position. Modify the state vector, x_, and covariance, P_.

  You'll also need to calculate the radar NIS. NIS to be stored in NIS_radar_
  */

	/*
	// Predict Radar Sigma Points
	//Lesson 7, section 27: Predict Radar Measurement Assignment 2

	//transform sigma points into measurement space
	for (int i=0; i<2*n_aug+1; i++) {
		//2n+1 sigma points

		//extra values for better readability
		double p_x = Xsig_pred(0,i);
		double p_y = Xsig_pred(1,i);
		double v = Xsig_pred(2,i);
		double yaw = Xsig_pred(3,i);

		double v1 = cos(yaw)*v;
		double v2 = sin(yaw)*v;

		//measurement model r, phi, r_dot
		Zsig(0,i) = sqrt(p_x*p_x + p_y*p_y);
		Zsig(1,i) = atan2(p_y, p_x);
		Zsig(2,i) = (p_x*v1 + p_y*v2) / sqrt(p_x*p_x + p_y*p_y);
	}

	//mean predicted measurement
	VectorXd z_pred = VectorXd(n_z);
	z_pred.fill(0.0);
	for (int i=0; i<2*n_aug+1; i++) {
		//2n+1 sigma points
		z_pred = z_pred + weights(i) * Zsig.col(i);
	}

	//measurement covariance matrix S
	MatrixXd S = MatrixXd(n_z,n_z);
	S.fill(0.0);
	for (int i=0; i<2*n_aug+1; i++) {
		//2n+1 sigma points
		//residual
		VectorXd z_diff = Zsig,col(i) - z_pred;
		//angle normalization
		while (z_diff(1)>M_PI) z_diff(1)-=2.M_PI;
		while (z_diff(1)<-M_PI) z_diff(1) +=2.M_PI;

		S = S + weights(i) * z_diff * z_diff.transpose();
	}

	//add measurement noise covariance matrix
	MatrixXd R = MatrixXd(n_z, n_z);
	R << std_radr_*std_radr_, 0, 0,
		 0, std_radphi_*std_radphi_, 0,
		 0, 0, std_radrd_*std_radrd_;
	S = S + R; 
	*/

	//Update Radar
	//Lesson 7, section 30: UKF Update Assignment 2

	//calculate cross correlation matrix
	Tc.fill(0.0);
	for (int i =0; i<2*n_aug+1; i++) {
		//2n+1 sigma points
		//residual
		VectorXd z_diff = Zsig.col(i) - z_pred;
		//angle normalization
		while(z_diff(1)>M_PI) z_diff(1)-=2.*M_PI;
		while(z_diff(1)<-M_PI) z_diff(1) +=2.M_PI;

		Tc = Tc + weights(i) * x_diff * z_diff.transpose();
	}

	//Kalman gain K;
	MatrixXd K = Tc * S.inverse();

	//residual
	VectorXd z_diff = z - z_pred;

	//angle normalization
	while (z_diff(1)>M_PI) z_diff(1)-=2.*M_PI;
	while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;

	//update state mean and covariance matrix
	x = x + K * z_diff;
	P = P - K*S*K.transpose();
}