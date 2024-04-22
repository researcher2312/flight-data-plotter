#pragma once

#include <vector>
#include <string>
#include <sdbus-c++/sdbus-c++.h>


namespace DBUSInterface {
    const std::string device {"org.freedesktop.NetworkManager.Device"};
    const std::string device_wireless {"org.freedesktop.NetworkManager.Device.Wireless"};
    const std::string networkmanager {"org.freedesktop.NetworkManager"};
    const std::string settings {"org.freedesktop.NetworkManager.Settings"};
    const std::string access_point {"org.freedesktop.NetworkManager.AccessPoint"};
}

namespace DBUSPath {
    const sdbus::ObjectPath networkmanager {"/org/freedesktop/NetworkManager"};
    const sdbus::ObjectPath settings {"/org/freedesktop/NetworkManager/Settings"};
}

namespace DBUSProperty {
    const std::string wireless_enabled {"WirelessEnabled"};
    const std::string ssid {"Ssid"};
    const std::string devices {"Devices"};
    const std::string device_type {"DeviceType"};
    const std::string hostname {"Hostname"};
    const std::string active_access_point {"ActiveAccessPoint"};
}

namespace DBUSError {
    const std::string unknown_method {"org.freedesktop.DBus.Error.UnknownMethod"};
}

class NetworkManagerDBUSProxy {
public:
    NetworkManagerDBUSProxy() = default;
    NetworkManagerDBUSProxy(sdbus::ObjectPath path_to_device);
    template<class T>
    T read_parameter(std::string interface_name, std::string property_name);
    std::string read_type(std::string interface_name, std::string property_name);
private:
    std::shared_ptr<sdbus::IProxy> m_dbus_proxy;
};

class NetworkManagerProxy {
public:
    NetworkManagerProxy();
    bool wireless_enabled();
    std::string hostname();
    std::string network_name();
private:
    sdbus::ObjectPath get_wireless_device_path();
    void set_wireless_device();
    NetworkManagerDBUSProxy m_networkmanager_proxy;
    NetworkManagerDBUSProxy m_wireless_device_proxy;
    NetworkManagerDBUSProxy m_settings_proxy;
};
