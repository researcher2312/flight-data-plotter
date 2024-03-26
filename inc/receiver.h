#pragma once

#include <vector>
#include <string>
#include <memory>
#include <sdbus-c++/sdbus-c++.h>
#include "windows.h"


class NetworkManagerDBUSProxy {
public:
    NetworkManagerDBUSProxy();
    bool wireless_enabled();
private:
    void read_wireless_status(const sdbus::Error* error, uint32_t status);
    const std::string SERVICE_NETWORKMANAGER {"org.freedesktop.NetworkManager"};
    const std::string NETWORKMANAGER_PATH {"/org/freedesktop/NetworkManager"};
    const std::string INTERFACE_PROPERTIES {"org.freedesktop.DBus.Properties"};
    bool wireless_is_enabled;
    std::unique_ptr<sdbus::IProxy> dbus_proxy;
};

class NetworkReceiver: public UIWidget {
public:
    NetworkReceiver();
    virtual void display();
    std::string get_connected_network_name();
    std::vector<std::string> get_network_names();
    NetworkManagerDBUSProxy network_dbus_proxy;
    bool is_connected;
};

