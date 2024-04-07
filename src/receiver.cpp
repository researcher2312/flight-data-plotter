#include <iostream>
#include <chrono>
#include "imgui.h"
#include "receiver.h"

DeviceDBUSProxy::DeviceDBUSProxy()
{
    //m_dbus_proxy = sdbus::createProxy(DBUSAddress::service_networkmanager, DBUSAddress::device_path);
    m_ssid = DBUSRequest<std::string>(m_dbus_proxy, DBUSAddress::service_device, DBUSAddress::ssid);
}

NetworkManagerDBUSProxy::NetworkManagerDBUSProxy()
{
    m_dbus_proxy = sdbus::createProxy(DBUSAddress::service_networkmanager, DBUSAddress::networkmanager_path);
    m_wireless_enabled = DBUSRequest<bool>(m_dbus_proxy, DBUSAddress::service_networkmanager, DBUSAddress::wireless_enabled);
}

bool NetworkManagerDBUSProxy::wireless_is_enabled()
{
    return m_wireless_enabled.get_value();
}

std::string DeviceDBUSProxy::ssid()
{
    return m_ssid.get_value();
}

template<class T>
DBUSRequest<T>::DBUSRequest(std::shared_ptr<sdbus::IProxy> proxy, std::string interface_name, std::string property_name)
{
    m_proxy = proxy;
    m_interface_name = interface_name;
    m_property_name = property_name;
}

template<class T>
bool DBUSRequest<T>::future_finished()
{
    if (m_call_result.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        return true;
    else
        return false;
}

template<class T>
void DBUSRequest<T>::set_future()
{
    m_call_result = m_proxy->getPropertyAsync(m_property_name)
                                    .onInterface(m_interface_name)
                                    .getResultAsFuture();
    
}

template<class T>
T DBUSRequest<T>::get_value()
{   
    try {
        if (m_call_result.valid()) {
            if (future_finished()) {
                result = m_call_result.get().get<T>();
                set_future();
            }
        }
        else {
            set_future();
        }
    }
    catch (sdbus::Error& error) {
        std::cerr << "ERR: " << error.getName() << " with message " << error.getMessage() << std::endl;
    }

    return result;
}

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
    // network_proxy.register_wireless_devices();
}
