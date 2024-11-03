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
    auto network_receiver = NetworkReceiver(&data_storage);
    auto graph = Graph(&data_storage);
    auto panel = ControlPanel(&data_storage);
    std::array<UIWidget*, 3> widgets{&network_receiver, &graph, &panel};
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

