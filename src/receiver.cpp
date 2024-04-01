#include <iostream>
#include <chrono>
#include "imgui.h"
#include "receiver.h"


NetworkManagerDBUSProxy::NetworkManagerDBUSProxy()
{
    m_dbus_proxy = sdbus::createProxy(DBUSAddress::service_networkmanager, DBUSAddress::networkmanager_path);
}

bool NetworkManagerDBUSProxy::future_finished()
{
    if (m_call_result.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        return true;
    else
        return false;
}

void NetworkManagerDBUSProxy::set_future()
{
    m_call_result = m_dbus_proxy->getPropertyAsync(DBUSAddress::wireless_enabled)
                                    .onInterface(DBUSAddress::service_networkmanager)
                                    .getResultAsFuture();
}


bool NetworkManagerDBUSProxy::read_wireless_status()
{
    if (m_call_result.valid()) {
        if (future_finished()) {
            wireless_enabled = m_call_result.get().get<bool>();
            set_future();
        }
    }
    else {
        set_future();
    }

    return wireless_enabled;
}

NetworkReceiver::NetworkReceiver()
{
    //is_connected = network_dbus_proxy.wireless_enabled();
}

bool NetworkReceiver::wireless_enabled()
{
    bool result = false;
    try {
        if (network_dbus_proxy.read_wireless_status())
            result = true;
    }
    catch(sdbus::Error& error) {
        std::cerr << "ERR: on scanAndConnect(): " << error.getName() << " with message " << error.getMessage() << std::endl;
    }
    return result;
}

void NetworkReceiver::display()
{
    // std::string answer;
    // if (network_dbus_proxy.wireless_enabled()) {
    //     answer = "enabled";
    // }
    // else {
    //     answer = "disabled";
    // }
    // //std::string answer = "Wireless error: " + network_dbus_proxy.error_name;
    // ImGui::Text(answer.c_str());

    if (wireless_enabled())
        ImGui::Text("connected");
    else
        ImGui::Text("not connected");
}

// std::vector<std::string> NetworkReceiver::get_network_names()
// {
//     ;
// }

// std::string NetworkReceiverget_connected_network_name()
// {
//     ;
// }


//('org.freedesktop.NetworkManager.AccessPoint', 'Ssid')
//('org.freedesktop.NetworkManager', 'WirelessEnabled')
