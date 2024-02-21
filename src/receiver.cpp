#include "imgui.h"
#include "receiver.h"

void NetworkReceiver::display()
{
    if(is_connected)
        ImGui::Text("connected");
    else
        ImGui::Text("not connected");
    if(ImGui::Button("Connect")){
        is_connected = !is_connected;
    }
}
