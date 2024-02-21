#pragma once

#include "receiver.h"
#include "graph.h"
#include "control_panel.h"

class GlobalWindow {
public:
    void display();
private:
    NetworkReceiver receiver;
    Graph graph;
    ControlPanel panel;
};
