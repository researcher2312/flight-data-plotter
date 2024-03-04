#pragma once

#include "windows.h"

class NetworkReceiver: public UIWidget {
public:
    virtual void display();
    bool is_connected = false;
};
