#pragma once

#include "data_storage.h"
#include "windows.h"

class ControlPanel: public UIWidget {
public:
    ControlPanel(DataStorage* data): data(data){};
    virtual void display();
private:
    DataStorage* data;
};
