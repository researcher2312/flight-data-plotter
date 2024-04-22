#include <iostream>
#include <string>
#include "imgui.h"
#include "receiver.h"


void NetworkReceiver::update_data()
{
    if (m_network_proxy.wireless_enabled()) {
        m_ssid = m_network_proxy.network_name();
        m_wireles_enabled = true;
    }
    else {
        m_ssid = "not available";
        m_wireles_enabled = false;
    }
    m_hostname = m_network_proxy.hostname();
}

void NetworkReceiver::display()
{
    static double refresh_time = ImGui::GetTime();
    if (ImGui::GetTime() > refresh_time + m_frame_time) {
        refresh_time += m_frame_time;
        update_data();
    }
    std::string hostname = "hostname: " + m_hostname;
    std::string ssid = "Ssid: " + m_ssid;
    ImGui::Text(hostname.c_str());
    ImGui::Text(ssid.c_str());

    if (m_wireles_enabled)
        ImGui::Text("Wireless connected");
    else
        ImGui::Text("Wireless not connected");
}
