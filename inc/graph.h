#pragma once

#include <vector>
#include <array>
#include "imgui.h"

struct SensorDataFrame{
  float time;
  float acceleration;
  float rotation;
  float magnetic;
};

class Graph {
 public:
  void display();
  void add_point(SensorDataFrame new_data);
 private:
  std::array<std::vector<float>, 3> sensor_data;
};

