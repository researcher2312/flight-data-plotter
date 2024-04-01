#pragma once

#include <vector>
#include <string>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include "windows.h"

namespace DBUSAddress {
    const std::string wireless_enabled {"WirelessEnabled"};
    const std::string service_networkmanager {"org.freedesktop.NetworkManager"};
    const std::string networkmanager_path {"/org/freedesktop/NetworkManager"};
    const std::string interface_properties {"org.freedesktop.DBus.Properties"};
}

class NetworkManagerDBUSProxy {
public:
    NetworkManagerDBUSProxy();
    bool read_wireless_status();
    std::string error_name {};
private:
    bool future_finished();
    void set_future();
    bool wireless_enabled;
    std::future<sdbus::Variant> m_call_result;
    std::unique_ptr<sdbus::IProxy> m_dbus_proxy;
};

class NetworkReceiver: public UIWidget {
public:
    NetworkReceiver();
    virtual void display();
    bool wireless_enabled();
    //std::string get_connected_network_name();
    //std::vector<std::string> get_network_names();
private:
    NetworkManagerDBUSProxy network_dbus_proxy;
};

