#include "app.h"

int main(int, char**)
{
    App myapp;
    myapp.setup();

    while (!myapp.wants_to_close)
    {
        myapp.process_events();
        myapp.update();
    }
    myapp.close();
    return 0;
}

