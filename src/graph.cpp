#include "implot.h"
#include "graph.h"

constexpr size_t f2size = 2*sizeof(float);

void Graph::display()
{
    // while(refresh_time < ImGui::GetTime()) {
    //     data->generate_random_data();
    //     refresh_time += 1.0 / 20.0;
    // }

    float history = 5.0f;
    float right_bound = data->get_highest_time();
    static ImPlotSubplotFlags sub_flags = ImPlotSubplotFlags_LinkRows;

    ImPlot::BeginSubplots("test", 3, 1, ImVec2(-1,-1), sub_flags);
    
    ImPlot::BeginPlot("Acceleration");
    ImPlot::SetupAxes("t(s)", "a(m/s²)");
    ImPlot::SetupAxisLimits(ImAxis_X1, right_bound - history, right_bound, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", data->acceleration.at(0).begin_x(), data->acceleration.at(0).begin_y(), data->acceleration.at(0).size(), 0, data->acceleration.at(0).Offset, f2size);
    ImPlot::PlotLine("y", data->acceleration.at(1).begin_x(), data->acceleration.at(1).begin_y(), data->acceleration.at(1).size(), 0, data->acceleration.at(1).Offset, f2size);
    ImPlot::PlotLine("z", data->acceleration.at(2).begin_x(), data->acceleration.at(2).begin_y(), data->acceleration.at(2).size(), 0, data->acceleration.at(2).Offset, f2size);
    ImPlot::EndPlot();

    ImPlot::BeginPlot("Rotation");
    ImPlot::SetupAxes("t(s)", "r(1/s)");
    ImPlot::SetupAxisLimits(ImAxis_X1, right_bound - history, right_bound, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", data->rotation.at(0).begin_x(), data->rotation.at(0).begin_y(), data->rotation.at(0).size(), 0, data->rotation.at(0).Offset, f2size);
    ImPlot::PlotLine("y", data->rotation.at(1).begin_x(), data->rotation.at(1).begin_y(), data->rotation.at(1).size(), 0, data->rotation.at(1).Offset, f2size);
    ImPlot::PlotLine("z", data->rotation.at(2).begin_x(), data->rotation.at(2).begin_y(), data->rotation.at(2).size(), 0, data->rotation.at(2).Offset, f2size);
    ImPlot::EndPlot();

    ImPlot::BeginPlot("Magnetic");
    ImPlot::SetupAxes("t(s)", "M(H)");
    ImPlot::SetupAxisLimits(ImAxis_X1, right_bound - history, right_bound, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 6);
    ImPlot::PlotLine("x", data->magnetic.at(0).begin_x(), data->magnetic.at(0).begin_y(), data->magnetic.at(0).size(), 0, data->magnetic.at(0).Offset, f2size);
    ImPlot::PlotLine("y", data->magnetic.at(1).begin_x(), data->magnetic.at(1).begin_y(), data->magnetic.at(1).size(), 0, data->magnetic.at(1).Offset, f2size);
    ImPlot::PlotLine("z", data->magnetic.at(2).begin_x(), data->magnetic.at(2).begin_y(), data->magnetic.at(2).size(), 0, data->magnetic.at(2).Offset, f2size);
    ImPlot::EndPlot();

    ImPlot::EndSubplots();
}
