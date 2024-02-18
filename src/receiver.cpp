#include "receiver.h"

void NetworkReceiver::display()
{
  ImGui::Begin("Connections");
  if(is_connected)
    ImGui::Text("connected");
  else
    ImGui::Text("not connected");
  if(ImGui::Button("Connect")){
    is_connected = !is_connected;
  }
  ImGui::End();
}
