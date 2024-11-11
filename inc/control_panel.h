#pragma once

#include <chrono>
#include "data_storage.h"
#include "windows.h"

class ControlPanel: public UIWidget {
public:
    ControlPanel(DataStorage* data);
    virtual void display();
private:
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> print_time;
    DataStorage* data;
};
