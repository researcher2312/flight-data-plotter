#include "imgui.h"
#include "receiver.h"


NetworkManagerDBUSProxy::NetworkManagerDBUSProxy()
{
    dbus_proxy = sdbus::createProxy(SERVICE_NETWORKMANAGER, NETWORKMANAGER_PATH);
}

bool NetworkManagerDBUSProxy::wireless_enabled()
{
    const std::string WIRELESS_ENABLED {"WirelessEnabled"};

    dbus_proxy->callMethodAsync("Get")
    .onInterface(INTERFACE_PROPERTIES)
    .withArguments(SERVICE_NETWORKMANAGER, WIRELESS_ENABLED)
    .uponReplyInvoke([this](const sdbus::Error* error, uint32_t status){read_wireless_status(error, status);});

    return wireless_is_enabled;
}

void NetworkManagerDBUSProxy::read_wireless_status(const sdbus::Error* error, uint32_t status)
{
    wireless_is_enabled = static_cast<bool>(status);
}


NetworkReceiver::NetworkReceiver()
{
    is_connected = network_dbus_proxy.wireless_enabled();
}

void NetworkReceiver::display()
{
    if (network_dbus_proxy.wireless_enabled())
        ImGui::Text("Wireless enabled");
    else
        ImGui::Text("Wireless disabled");
    if (is_connected)
        ImGui::Text("connected");
    else
        ImGui::Text("not connected");
    if (ImGui::Button("Connect")){
        is_connected = !is_connected;
    }
}

std::vector<std::string> NetworkReceiver::get_network_names()
{
    ;
}

std::string NetworkReceiverget_connected_network_name()
{
    ;
}


//('org.freedesktop.NetworkManager.AccessPoint', 'Ssid')
//('org.freedesktop.NetworkManager', 'WirelessEnabled')
