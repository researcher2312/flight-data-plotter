#pragma once

#include <vector>
#include <array>
#include "imgui.h"

struct SensorDataFrame{
  float time;
  std::array<float, 3> acceleration;
  std::array<float, 3> rotation;
  std::array<float, 3> magnetic;
};

class Graph {
 public:
  void display();
  void add_point(SensorDataFrame new_data);
 private:
  std::array<std::vector<float>, 3> acceleration;
  std::array<std::vector<float>, 3> rotation;
  std::array<std::vector<float>, 3> magnetic;
};

