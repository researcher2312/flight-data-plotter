#include <string>
#include <format>
#include "imgui.h"
#include "madgwick.h"
#include "control_panel.h"


void ControlPanel::display()
{
    float roll, pitch, yaw;
    float q0, q1, q2, q3;
    eulerAngles(&roll, &pitch, &yaw);
    get_quaternion(&q0, &q1, &q2, &q3);
    std::string madgwick_data = std::format("roll: {: 4.2f}, pitch: {: 4.2f}, yaw: {: 4.2f}", roll, pitch, yaw);

    ImGui::Text("%s", madgwick_data.c_str());
    ImGui::Button("Control");
}
  
