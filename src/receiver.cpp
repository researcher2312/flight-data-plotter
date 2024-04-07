#include <string>
#include "imgui.h"
#include "receiver.h"


void NetworkReceiver::display()
{
    std::string hostname = "hostname: " + network_proxy.hostname();
    std::string ssid = "Ssid: " + network_proxy.network_name();
    ImGui::Text(hostname.c_str());
    ImGui::Text(ssid.c_str());

    if (network_proxy.wireless_enabled())
        ImGui::Text("Wireless connected");
    else
        ImGui::Text("Wireless not connected");
}
