#include <cmath>
#include "implot.h"
#include "imgui.h"
#include "graph.h"


void Graph::display()
{
    while(refresh_time < ImGui::GetTime()) {
        SensorDataFrame data;
        data.acceleration = std::array<double, 3>{distribution(generator), distribution(generator), distribution(generator)};
        data.rotation = std::array<double, 3>{distribution(generator), distribution(generator), distribution(generator)};
        data.magnetic = std::array<double, 3>{distribution(generator), distribution(generator), distribution(generator)};
        add_point(data, ImGui::GetTime());
        refresh_time += 1.0 / 20.0;
    }

    static float history = 5.0f;
    static ImPlotSubplotFlags sub_flags = ImPlotSubplotFlags_LinkRows;

    ImPlot::BeginSubplots("test", 3, 1, ImVec2(-1,-1), sub_flags);
    
    ImPlot::BeginPlot("Acceleration");
    ImPlot::SetupAxes("t(s)", "a(m/s²)");
    ImPlot::SetupAxisLimits(ImAxis_X1, ImGui::GetTime() - history, ImGui::GetTime(), ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", &acceleration.at(0).Data[0].x, &acceleration.at(0).Data[0].y, acceleration.at(0).Data.size(), 0, acceleration.at(0).Offset, 2*sizeof(float));
    ImPlot::PlotLine("y", &acceleration.at(1).Data[0].x, &acceleration.at(1).Data[0].y, acceleration.at(1).Data.size(), 0, acceleration.at(1).Offset, 2*sizeof(float));
    ImPlot::PlotLine("z", &acceleration.at(2).Data[0].x, &acceleration.at(2).Data[0].y, acceleration.at(2).Data.size(), 0, acceleration.at(2).Offset, 2*sizeof(float));
    ImPlot::EndPlot();

    ImPlot::BeginPlot("Rotation");
    ImPlot::SetupAxes("t(s)", "r(1/s)");
    ImPlot::SetupAxisLimits(ImAxis_X1, ImGui::GetTime() - history, ImGui::GetTime(), ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", &rotation.at(0).Data[0].x, &rotation.at(0).Data[0].y, rotation.at(0).Data.size(), 0, rotation.at(0).Offset, 2*sizeof(float));
    ImPlot::PlotLine("y", &rotation.at(1).Data[0].x, &rotation.at(1).Data[0].y, rotation.at(1).Data.size(), 0, rotation.at(1).Offset, 2*sizeof(float));
    ImPlot::PlotLine("z", &rotation.at(2).Data[0].x, &rotation.at(2).Data[0].y, rotation.at(2).Data.size(), 0, rotation.at(2).Offset, 2*sizeof(float));
    ImPlot::EndPlot();

    ImPlot::BeginPlot("Magnetic");
    ImPlot::SetupAxes("t(s)", "M(H)");
    ImPlot::SetupAxisLimits(ImAxis_X1, ImGui::GetTime() - history, ImGui::GetTime(), ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", &magnetic.at(0).Data[0].x, &magnetic.at(0).Data[0].y, magnetic.at(0).Data.size(), 0, magnetic.at(0).Offset, 2*sizeof(float));
    ImPlot::PlotLine("y", &magnetic.at(1).Data[0].x, &magnetic.at(1).Data[0].y, magnetic.at(1).Data.size(), 0, magnetic.at(1).Offset, 2*sizeof(float));
    ImPlot::PlotLine("z", &magnetic.at(2).Data[0].x, &magnetic.at(2).Data[0].y, magnetic.at(2).Data.size(), 0, magnetic.at(2).Offset, 2*sizeof(float));
    ImPlot::EndPlot();

    ImPlot::EndSubplots();
}

void Graph::add_point(SensorDataFrame& new_data, double time)
{
    for (int i=0; i<3; ++i) {
        acceleration.at(i).AddPoint(time, new_data.acceleration.at(i));
        rotation.at(i).AddPoint(time, new_data.rotation.at(i));
        magnetic.at(i).AddPoint(time, new_data.magnetic.at(i));
    }
}

