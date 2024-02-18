#include "graph.h"
#include <cmath>

void Graph::display()
{
  ImGui::Begin("Graph");
  if(ImGui::Button("Add point")){
    SensorDataFrame data;
    data.acceleration = std::fmod(ImGui::GetTime(), 3.0);
    data.rotation = std::fmod(ImGui::GetTime(), 4.0);
    data.magnetic = std::fmod(ImGui::GetTime(), 5.0);
    add_point(data);    
  }
  ImGui::PlotLines("Acceleration", sensor_data.at(0).data(), sensor_data.at(0).size(), 0, NULL, 0.0f, 5.0f, ImVec2(0, 80.0f));
  ImGui::PlotLines("Rotation", sensor_data.at(1).data(), sensor_data.at(1).size(), 0, NULL, 0.0f, 5.0f, ImVec2(0, 80.0f));
  ImGui::PlotLines("Magnetic", sensor_data.at(2).data(), sensor_data.at(2).size(), 0, NULL, 0.0f, 5.0f, ImVec2(0, 80.0f));
}

void Graph::add_point(SensorDataFrame new_data)
{
  sensor_data.at(0).push_back(new_data.acceleration);
  sensor_data.at(1).push_back(new_data.rotation);
  sensor_data.at(2).push_back(new_data.magnetic);
}

