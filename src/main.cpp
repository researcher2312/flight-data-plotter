#include <array>
#include "app.h"
#include "receiver.h"
#include "control_panel.h"
#include "graph.h"
#include "windows.h"
#include "data_storage.h"

int main(int, char**)
{
    DataStorage data_storage;
    auto network_receiver = new NetworkReceiver(&data_storage);
    auto graph = new Graph(&data_storage);
    std::array<UIWidget*, 3> widgets{network_receiver, graph, new ControlPanel};
    auto global_window = GlobalWindow(widgets);
    App myapp;
    myapp.add_window(&global_window);
    myapp.setup();

    while (!myapp.wants_to_close)
    {
        myapp.process_events();
        myapp.update();
    }
    myapp.close();
    return 0;
}

