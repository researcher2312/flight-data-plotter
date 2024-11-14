#include "Eigen/Dense"
#include "data_storage.h"
#include "madgwick.h"

void DataStorage::add_point(float time,
                            std::array<float, 3> _acceleration,
                            std::array<float, 3> _rotation,
                            std::array<float, 3> _magnetic)
{
    //magnetometer y and z are reversed
    _magnetic.at(1) *= -1;
    _magnetic.at(2) *= -1;

    for (int i=0; i<3; ++i) {
        acceleration.at(i).AddPoint(time, _acceleration.at(i));
        rotation.at(i).AddPoint(time, _rotation.at(i));
        magnetic.at(i).AddPoint(time, _magnetic.at(i));
    }
    Vector3d gyro(deg_to_rad(_rotation.at(0)),
                  deg_to_rad(_rotation.at(1)),
                  deg_to_rad(_rotation.at(2)));   //gyroscope data (in rad/s)
    Vector3d accel(_acceleration.at(0), _acceleration.at(1), _acceleration.at(2));           //accelerometer data (gravity vector)
    Vector3d magnet(_magnetic.at(0), _magnetic.at(1), _magnetic.at(2));

    kalman_filter.predict(gyro, 0.02);
    kalman_filter.update(accel, magnet);

    MadgwickAHRSupdate(_rotation.at(0),
                       _rotation.at(1),
                       _rotation.at(2),
                       _acceleration.at(0),
                       _acceleration.at(1),
                       _acceleration.at(2),
                       _magnetic.at(0),
                       _magnetic.at(1),
                       _magnetic.at(2));
    acceleration_norm = accel.norm();
}

void DataStorage::generate_random_data()
{
    auto acceleration = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    auto rotation = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    auto magnetic = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    add_point(ImGui::GetTime(), acceleration, rotation, magnetic);
}

float DataStorage::get_highest_time()
{
    if (acceleration.size() > 0) {
        return acceleration.at(0).Data.back().x;
    }
    return 0.0;
}
