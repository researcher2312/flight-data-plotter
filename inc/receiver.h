#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include "windows.h"
#include "network_proxy.h"


class NetworkReceiver: public UIWidget {
public:
    virtual void display();
private:
    NetworkManagerProxy network_proxy;
};
