#pragma once

#include <vector>
#include <string>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include "windows.h"
#include "network_proxy.h"

namespace DBUSAddress {
    const std::string wireless_enabled {"WirelessEnabled"};
    const std::string ssid {"Driver"};
    const std::string service_networkmanager {"org.freedesktop.NetworkManager"};
    const std::string service_device {"org.freedesktop.NetworkManager.Device"};
    const std::string networkmanager_path {"/org/freedesktop/NetworkManager"};
}


template<class T>
class DBUSRequest {
public:
    DBUSRequest(std::shared_ptr<sdbus::IProxy> proxy, std::string interface_name, std::string property_name);
    DBUSRequest() = default;
    T get_value();
private:
    bool future_finished();
    void set_future();
    std::string m_interface_name;
    std::string m_property_name;
    std::future<sdbus::Variant> m_call_result;
    std::shared_ptr<sdbus::IProxy> m_proxy;
    T result;
};

class DeviceDBUSProxy {
public:
    DeviceDBUSProxy();
    std::string ssid();

private:
    DBUSRequest<std::string> m_ssid;
    std::shared_ptr<sdbus::IProxy> m_dbus_proxy;
};

class NetworkManagerDBUSProxy {
public:
    NetworkManagerDBUSProxy();
    bool wireless_is_enabled();
private:
    DBUSRequest<bool> m_wireless_enabled;
    std::shared_ptr<sdbus::IProxy> m_dbus_proxy;
};

class NetworkReceiver: public UIWidget {
public:
    virtual void display();
private:
    NetworkManagerProxy network_proxy;
};
