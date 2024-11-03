#include <numbers>
#include "kalman.h"


// Convert degrees to radians
double deg_to_rad(double deg)
{
    return deg * 180 / std::numbers::pi;
}


// Quaternion normalization
void normalizeQuaternion(Vector4d &quat) {
    quat.normalize();
}

KalmanFilter::KalmanFilter() {
    // Initialize state (quaternion) to represent no rotation
    q << 1, 0, 0, 0;

    // Initialize covariance matrix P
    P = Matrix4d::Identity();

    // Set process noise covariance Q
    Q = 0.01 * Matrix4d::Identity();

    // Set measurement noise covariance R (for accelerometer)
    R = 0.1 * Matrix3d::Identity();
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

void KalmanFilter::getEulerAngles(float &roll, float &pitch, float &yaw) const
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
}

// Example usage

// int main() {
//     KalmanFilter kf;

//     // Simulate a gyroscope measurement (angular velocities) and accelerometer measurement (gravity direction)
//     Vector3d gyro(0.01, 0.02, 0.015);  // Example gyroscope data (in rad/s)
//     Vector3d accel(0, 0, -1);           // Example accelerometer data (gravity vector)

//     double dt = 0.01; // Time step in seconds

//     // Prediction step
//     kf.predict(gyro, dt);

//     // Update step
//     kf.update(accel);

//     // Output the estimated quaternion
//     std::cout << "Estimated quaternion: " << kf.q.transpose() << std::endl;

//     return 0;
// }
