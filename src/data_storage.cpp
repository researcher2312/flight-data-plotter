#include "data_storage.h"

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
}


void DataStorage::generate_random_data()
{
    auto acceleration = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    auto rotation = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    auto magnetic = std::array<float, 3>{distribution(generator), distribution(generator), distribution(generator)};
    add_point(ImGui::GetTime(), acceleration, rotation, magnetic);
}
