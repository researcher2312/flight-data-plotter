#pragma once

#include "Eigen/Dense"
using namespace Eigen;

double deg_to_rad(double);

class KalmanFilter {
public:
    Vector4d q;       // Quaternion state [q0, q1, q2, q3]
    Matrix4d P;       // State covariance matrix
    Matrix4d Q;       // Process noise covariance matrix
    Matrix3d R;       // Measurement noise covariance matrix

    KalmanFilter();
    void predict(const Vector3d &gyro, double dt);
    void update(const Vector3d &accel);
    void getEulerAngles(float &roll, float &pitch, float &yaw) const;
};

class ExtendedKalmanFilter {
public:
    Vector4d q;       // Quaternion state [q0, q1, q2, q3]
    Matrix4d P;       // State covariance matrix
    Matrix4d Q;       // Process noise covariance matrix
    Matrix<double, 6, 6> R; // Measurement noise covariance matrix (now for both accelerometer and magnetometer)

    ExtendedKalmanFilter();
    void predict(const Vector3d &gyro, double dt);
    void update(const Vector3d &accel, const Vector3d &magnet);
    void getEulerAngles(float &roll, float &pitch, float &yaw) const;
};