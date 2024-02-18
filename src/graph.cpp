#include "graph.h"
#include "implot.h"
#include <cmath>

void Graph::display()
{
  ImGui::Begin("Graph");
  if(ImGui::Button("Add point")){
    SensorDataFrame data;
    data.acceleration = std::array<float, 3>{std::fmod(ImGui::GetTime(), 3.0), std::fmod(ImGui::GetTime(), 4.0), std::fmod(ImGui::GetTime(), 5.0)};
    data.rotation = std::array<float, 3>{std::fmod(ImGui::GetTime(), 7.0), std::fmod(ImGui::GetTime(), 2.0), std::fmod(ImGui::GetTime(), 3.0)};
    data.magnetic = std::array<float, 3>{std::fmod(ImGui::GetTime(), 5.0), std::fmod(ImGui::GetTime(), 3.0), std::fmod(ImGui::GetTime(), 4.0)};
    add_point(data);
  }
  
  ImPlot::BeginPlot("Acceleration");
  ImPlot::SetupAxes("t(s)", "a(m/s²)");
  ImPlot::PlotLine("x", acceleration.at(0).data(), acceleration.at(0).size());
  ImPlot::PlotLine("y", acceleration.at(1).data(), acceleration.at(1).size());
  ImPlot::PlotLine("z", acceleration.at(2).data(), acceleration.at(2).size());
  ImPlot::EndPlot();

  ImPlot::BeginPlot("Rotation");
  ImPlot::SetupAxes("t(s)", "r(1/s)");
  ImPlot::PlotLine("x", rotation.at(0).data(), rotation.at(0).size());
  ImPlot::PlotLine("y", rotation.at(1).data(), rotation.at(1).size());
  ImPlot::PlotLine("z", rotation.at(2).data(), rotation.at(2).size());
  ImPlot::EndPlot();

  ImPlot::BeginPlot("Magnetic");
  ImPlot::SetupAxes("t(s)", "M(H)");
  ImPlot::PlotLine("x", magnetic.at(0).data(), magnetic.at(0).size());
  ImPlot::PlotLine("y", magnetic.at(1).data(), magnetic.at(1).size());
  ImPlot::PlotLine("z", magnetic.at(2).data(), magnetic.at(2).size());
  ImPlot::EndPlot();

  ImGui::End();
}

void Graph::add_point(SensorDataFrame new_data)
{
  for (int i=0; i<3; ++i){
    acceleration.at(i).push_back(new_data.acceleration.at(i));
    rotation.at(i).push_back(new_data.rotation.at(i));
    magnetic.at(i).push_back(new_data.magnetic.at(i));
  }
}

