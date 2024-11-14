#include <numbers>
#include "kalman.h"


// Convert degrees to radians
double deg_to_rad(double deg)
{
    return deg * std::numbers::pi / 180.0f;
}


// Quaternion normalization
void normalizeQuaternion(Vector4d &quat) {
    quat.normalize();
}

KalmanFilter::KalmanFilter() {
    // Initialize state (quaternion) to represent no rotation
    q << 1, 0, 0, 0;

    // Initialize covariance matrix P
    P = 0.01 * Matrix4d::Identity();

    // Set process noise covariance Q
    Q = 0.01 * Matrix4d::Identity();

    // Set measurement noise covariance R (for accelerometer)
    R = 0.1 * Matrix3d::Identity();
}

ExtendedKalmanFilter::ExtendedKalmanFilter() {
    // Initialize quaternion state (no rotation)
    q << 1, 0, 0, 0;

    // Initialize covariance matrix P
    P = 0.01 *  Matrix4d::Identity();

    // Set process noise covariance Q
    Q = 0.1 * Matrix4d::Identity();

    // Set measurement noise covariance R (for accelerometer and magnetometer)
    R = Matrix<double, 6, 6>::Identity();
    R.topLeftCorner(3, 3) *= 0.1;  // Accelerometer noise
    R.bottomRightCorner(3, 3) *= 0.05;  // Magnetometer noise (typically lower than accelerometer)
}

// Predict step using gyroscope data (angular velocities)
void KalmanFilter::predict(const Vector3d &gyro, double dt) {
    // Convert angular velocity to quaternion derivative
    Matrix4d Omega;
    Omega <<      0, -gyro(0), -gyro(1), -gyro(2),
            gyro(0),        0,  gyro(2), -gyro(1),
            gyro(1), -gyro(2),        0,  gyro(0),
            gyro(2),  gyro(1), -gyro(0),        0;

    // Compute the new state quaternion using small-angle approximation
    q = q + 0.5 * Omega * q * dt;
    normalizeQuaternion(q);

    // State transition matrix approximation: F ≈ I (small-angle assumption)
    Matrix4d F = Matrix4d::Identity();

    // Update covariance
    P = F * P * F.transpose() + Q;
}

void ExtendedKalmanFilter::predict(const Vector3d &gyro, double dt) {
    // Convert angular velocity to quaternion derivative
    Matrix4d Omega;
    Omega <<  0,      -gyro(0), -gyro(1), -gyro(2),
                gyro(0), 0,       gyro(2), -gyro(1),
                gyro(1), -gyro(2), 0,       gyro(0),
                gyro(2), gyro(1), -gyro(0), 0;

    // Update quaternion state using small-angle approximation
    q = q + 0.5 * Omega * q * dt;
    normalizeQuaternion(q);

    // State transition matrix approximation: F ≈ I
    Matrix4d F = Matrix4d::Identity();

    // Update covariance
    P = F * P * F.transpose() + Q;
}

// Update step using accelerometer data (for gravity direction)
void KalmanFilter::update(const Vector3d &accel) {
    // Normalize accelerometer data to get gravity direction
    Vector3d z = accel.normalized();

    // Predicted gravity vector based on current orientation (quaternion)
    Vector3d h;
    h << 2 * (q(1) * q(3) - q(0) * q(2)),
            2 * (q(0) * q(1) + q(2) * q(3)),
            q(0) * q(0) - q(1) * q(1) - q(2) * q(2) + q(3) * q(3);

    // Innovation or measurement residual
    Vector3d y = z - h;

    // Jacobian matrix H (partial derivatives of h with respect to quaternion q)
    Matrix<double, 3, 4> H;
    H << -2 * q(2),  2 * q(3), -2 * q(0),  2 * q(1),
            2 * q(1),  2 * q(0),  2 * q(3),  2 * q(2),
            2 * q(0), -2 * q(1), -2 * q(2),  2 * q(3);

    // Innovation covariance
    Matrix3d S = H * P * H.transpose() + R;

    // Kalman gain
    Matrix<double, 4, 3> K = P * H.transpose() * S.inverse();

    // Update quaternion state
    q = q + K * y;
    normalizeQuaternion(q);

    // Update covariance matrix
    P = (Matrix4d::Identity() - K * H) * P;
}

// Update step using accelerometer and magnetometer data
void ExtendedKalmanFilter::update(const Vector3d &accel, const Vector3d &magnet) {
    // Normalize accelerometer and magnetometer data
    Vector3d z_acc = accel.normalized();
    Vector3d z_mag = magnet.normalized();

    // Predicted gravity direction based on quaternion state
    Vector3d h_acc;
    h_acc << 2 * (q(1) * q(3) - q(0) * q(2)),
                2 * (q(0) * q(1) + q(2) * q(3)),
                q(0) * q(0) - q(1) * q(1) - q(2) * q(2) + q(3) * q(3);

    // Predicted magnetic north direction based on quaternion state
    Vector3d h_mag;
    h_mag << q(0) * q(0) + q(1) * q(1) - q(2) * q(2) - q(3) * q(3),
                2 * (q(1) * q(2) - q(0) * q(3)),
                2 * (q(1) * q(3) + q(0) * q(2));

    // Measurement residual (innovation)
    Vector<double, 6> y;
    y.head<3>() = z_acc - h_acc;
    y.tail<3>() = z_mag - h_mag;

    // Jacobian matrix H (partial derivatives of h_acc and h_mag with respect to quaternion q)
    Matrix<double, 6, 4> H;
    H.setZero();
    H.block<3, 4>(0, 0) << -2 * q(2),  2 * q(3), -2 * q(0),  2 * q(1),
                            2 * q(1),  2 * q(0),  2 * q(3),  2 * q(2),
                            2 * q(0), -2 * q(1), -2 * q(2),  2 * q(3);

    H.block<3, 4>(3, 0) << 2 * q(0),  2 * q(1), -2 * q(2), -2 * q(3),
                            -2 * q(3),  2 * q(2),  2 * q(1), -2 * q(0),
                            2 * q(2),  2 * q(3),  2 * q(0),  2 * q(1);

    // Innovation covariance
    Matrix<double, 6, 6> S = H * P * H.transpose() + R;

    // Kalman gain
    Matrix<double, 4, 6> K = P * H.transpose() * S.inverse();

    // Update quaternion state
    q = q + K * y;
    normalizeQuaternion(q);

    // Update covariance matrix
    P = (Matrix4d::Identity() - K * H) * P;
}

void KalmanFilter::get_euler_angles(float &roll, float &pitch, float &yaw) const
{
    // Extract quaternion components
    double q0 = q(0);
    double q1 = q(1);
    double q2 = q(2);
    double q3 = q(3);

    // Calculate roll (x-axis rotation)
    roll = atan2(2.0 * (q0 * q1 + q2 * q3), 1.0 - 2.0 * (q1 * q1 + q2 * q2));

    // Calculate pitch (y-axis rotation)
    double sinp = 2.0 * (q0 * q2 - q3 * q1);
    if (std::abs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp);  // Use 90 degrees if out of range
    else
        pitch = asin(sinp);

    // Calculate yaw (z-axis rotation)
    yaw = atan2(2.0 * (q0 * q3 + q1 * q2), 1.0 - 2.0 * (q2 * q2 + q3 * q3));

    yaw *= (180.0f / std::numbers::pi);
    pitch *= (180.0f / std::numbers::pi);
    roll *= (180.0f / std::numbers::pi);
}

void ExtendedKalmanFilter::get_euler_angles(float &roll, float &pitch, float &yaw) const {
        double q0 = q(0);
        double q1 = q(1);
        double q2 = q(2);
        double q3 = q(3);

        roll = atan2(2.0 * (q0 * q1 + q2 * q3), 1.0 - 2.0 * (q1 * q1 + q2 * q2)) * (180.0 / std::numbers::pi);
        double sinp = 2.0 * (q0 * q2 - q3 * q1);
        if (std::abs(sinp) >= 1)
            pitch = copysign(90.0, sinp);
        else
            pitch = asin(sinp) * (180.0 / std::numbers::pi);

        yaw = atan2(2.0 * (q0 * q3 + q1 * q2), 1.0 - 2.0 * (q2 * q2 + q3 * q3)) * (180.0 / std::numbers::pi);
    }

    void ExtendedKalmanFilter::get_quaternion(float& q0, float& q1, float& q2, float& q3) const
    {
        q0 = q(0);
        q1 = q(1);
        q2 = q(2);
        q3 = q(3);
    }

void ExtendedKalmanFilter::get_deviation(float& q0, float& q1, float& q2, float& q3) const
{
    q0 = std::sqrt(P(0, 0));  // Standard deviation for q0
    q1 = std::sqrt(P(1, 1));  // Standard deviation for q1
    q2 = std::sqrt(P(2, 2));  // Standard deviation for q2
    q3 = std::sqrt(P(3, 3));  // Standard deviation for q3
}


