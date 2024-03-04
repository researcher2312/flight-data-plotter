#include <array>
#include "app.h"
#include "receiver.h"
#include "control_panel.h"
#include "graph.h"
#include "windows.h"

int main(int, char**)
{
    std::array<UIWidget*, 3> widgets{new NetworkReceiver, new Graph, new ControlPanel};
    GlobalWindow global_window = GlobalWindow(widgets);
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

