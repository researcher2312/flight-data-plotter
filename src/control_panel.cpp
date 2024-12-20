#include <string>
#include <format>
#include <iostream>
#include "imgui.h"
#include "madgwick.h"
#include "control_panel.h"

using namespace std::chrono;

ControlPanel::ControlPanel(DataStorage* _data)
{
    data = _data;
    start_time = system_clock::now();
    print_time = system_clock::now();
    std::cerr << "t,x,y,z,X,Y,Z,q0,q1,q2,q3,dq0,dq1,dq2,dq3,a\n";
}

void ControlPanel::display()
{
    float roll_m, pitch_m, yaw_m;
    float roll_k, pitch_k, yaw_k;
    float q0, q1, q2, q3;
    float dq0, dq1, dq2, dq3;
    float a = data->acceleration_norm;
    eulerAngles(&roll_m, &pitch_m, &yaw_m);

    std::string madgwick_data = std::format("roll: {: 6.2f}, pitch: {: 6.2f}, yaw: {: 6.2f}", roll_m, pitch_m, yaw_m);

    data->kalman_filter.get_euler_angles(roll_k, pitch_k, yaw_k);
    std::string kalman_data = std::format("roll: {: 6.2f}, pitch: {: 6.2f}, yaw: {: 6.2f}", roll_k, pitch_k, yaw_k);

    if (system_clock::now() > print_time + 20ms) {
        print_time = system_clock::now();
        auto time_diff = duration_cast<std::chrono::milliseconds>(system_clock::now() - start_time);
        
        data->kalman_filter.get_quaternion(q0, q1, q2, q3);
        data->kalman_filter.get_deviation(dq0, dq1, dq2, dq3);

        std::cerr << std::format(
            "{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}\n",
            time_diff.count(), roll_m, pitch_m, yaw_m, roll_k, pitch_k, yaw_k, q0, q1, q2, q3, dq0, dq1, dq2, dq3, a
        );
    }

    ImGui::Text("Madgwick data:");
    ImGui::Text("%s", madgwick_data.c_str());
    ImGui::Text("Kalman data:");
    ImGui::Text("%s", kalman_data.c_str());
    ImGui::Button("Control");
}
  
