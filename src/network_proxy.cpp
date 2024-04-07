#include <iostream>
#include "network_proxy.h"


NetworkManagerFastDBUSPROXY::NetworkManagerFastDBUSPROXY(sdbus::ObjectPath path_to_device)
{
    m_dbus_proxy = sdbus::createProxy(DBUSInterface::networkmanager, path_to_device);
}

template<class T>
T NetworkManagerFastDBUSPROXY::read_parameter(std::string interface_name, std::string property_name)
{
    T result;
    try {
        result = m_dbus_proxy->getProperty(property_name)
                                .onInterface(interface_name)
                                .get<T>();
    }
    catch (sdbus::Error& error) {
        std::cerr << "ERR: " << error.getName() << " with message " << error.getMessage() << std::endl;
    }
    return result;
}

std::string NetworkManagerFastDBUSPROXY::read_type(std::string interface_name, std::string property_name)
{
    auto result = m_dbus_proxy->getProperty(property_name)
                                .onInterface(interface_name);
    return result.peekValueType();
}

NetworkManagerProxy::NetworkManagerProxy()
{
    m_networkmanager_proxy = NetworkManagerFastDBUSPROXY(DBUSPath::networkmanager);
    m_settings_proxy = NetworkManagerFastDBUSPROXY(DBUSPath::settings);
    m_wireless_device_proxy = NetworkManagerFastDBUSPROXY(get_wireless_device_path());
}

sdbus::ObjectPath NetworkManagerProxy::get_wireless_device_path()
{
    sdbus::ObjectPath result;
    auto devices = m_networkmanager_proxy.read_parameter<std::vector<sdbus::ObjectPath>>(DBUSInterface::networkmanager, DBUSProperty::devices);
    for (auto& device: devices) {
        auto proxy = NetworkManagerFastDBUSPROXY(device);
        auto type = proxy.read_parameter<uint32_t>(DBUSInterface::device, DBUSProperty::device_type);
        if (type == 2) {
            result =  device;
        }
    }
    return result;
}

std::string NetworkManagerProxy::hostname()
{
    return m_settings_proxy.read_parameter<std::string>(DBUSInterface::settings, DBUSProperty::hostname);
}

std::string NetworkManagerProxy::network_name()
{
    auto device = m_wireless_device_proxy.read_parameter<sdbus::ObjectPath>(DBUSInterface::device_wireless, DBUSProperty::active_access_point);
    NetworkManagerFastDBUSPROXY proxy {device};
    auto reading = proxy.read_parameter<std::vector<uint8_t>>(DBUSInterface::access_point, DBUSProperty::ssid);
    return std::string(reading.begin(), reading.end());
}

bool NetworkManagerProxy::wireless_enabled()
{
    return m_networkmanager_proxy.read_parameter<bool>(DBUSInterface::networkmanager, DBUSProperty::wireless_enabled);
}
