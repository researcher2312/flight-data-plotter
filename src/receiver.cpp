#include "receiver.h"

void NetworkReceiver::display()
{
  ImGui::Begin("Connections");
  if(is_connected)
    ImGui::Text("connected");
  else
    ImGui::Text("not connected");
  ImGui::End();
}
