#pragma once

#include "data_storage.h"
#include "windows.h"


class Graph: public UIWidget {
public:
    Graph(DataStorage* _data):data(_data){};
    virtual void display();
    float refresh_time = 0.0;
private:
    DataStorage* data;
};
