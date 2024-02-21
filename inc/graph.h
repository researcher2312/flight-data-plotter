#pragma once

#include <vector>
#include <array>

struct SensorDataFrame{
    double time;
    std::array<double, 3> acceleration;
    std::array<double, 3> rotation;
    std::array<double, 3> magnetic;
};

class Graph {
public:
    void display();
    void add_point(SensorDataFrame new_data);
private:
    std::array<std::vector<double>, 3> acceleration;
    std::array<std::vector<double>, 3> rotation;
    std::array<std::vector<double>, 3> magnetic;
};

