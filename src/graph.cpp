#include "graph.h"
#include "implot.h"
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
  
  ImPlot::BeginPlot("Flight Data");
  ImPlot::PlotLine("Acceleration", sensor_data.at(0).data(), sensor_data.at(0).size());
  ImPlot::PlotLine("Rotation", sensor_data.at(1).data(), sensor_data.at(1).size());
  ImPlot::PlotLine("Magnetic", sensor_data.at(2).data(), sensor_data.at(2).size());
  ImPlot::EndPlot();
}

void Graph::add_point(SensorDataFrame new_data)
{
  sensor_data.at(0).push_back(new_data.acceleration);
  sensor_data.at(1).push_back(new_data.rotation);
  sensor_data.at(2).push_back(new_data.magnetic);
}

