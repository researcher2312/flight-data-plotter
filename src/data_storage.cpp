#include "data_storage.h"
#include "madgwick.h"

void DataStorage::add_point(float time,
                            std::array<float, 3> _acceleration,
                            std::array<float, 3> _rotation,
                            std::array<float, 3> _magnetic)
{
    for (int i=0; i<3; ++i) {
        acceleration.at(i).AddPoint(time, _acceleration.at(i));
        rotation.at(i).AddPoint(time, _rotation.at(i));
        magnetic.at(i).AddPoint(time, _magnetic.at(i));
    }
    MadgwickAHRSupdate(_rotation.at(0),
                       _rotation.at(1),
                       _rotation.at(2),
                       _acceleration.at(0),
                       _acceleration.at(1),
                       _acceleration.at(2),
                       _magnetic.at(0),
                       _magnetic.at(1),
                       _magnetic.at(2));
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
