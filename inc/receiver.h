#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include "windows.h"
#include "network_proxy.h"
#include "client.h"


class NetworkReceiver: public UIWidget {
public:
    virtual void display();
private:
    void update_data();
    std::string m_hostname;
    std::string m_ssid;
    bool m_wireles_enabled;
    int m_frame_time = 1.0f / 20.0f;
    NetworkManagerProxy m_network_proxy;
    DataClient m_data_client;
};
