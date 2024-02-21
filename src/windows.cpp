#include "imgui.h"
#include "windows.h"

void GlobalWindow::display()
{
    ImGui::Begin("Window");
    ImGui::BeginTable("window_table", 2);
    
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    receiver.display();
    
    ImGui::TableSetColumnIndex(1);
    panel.display();
    
    ImGui::TableSetColumnIndex(0);
    ImGui::TableNextRow();
    ImGui::Button("Button4");
    ImGui::Button("Button5");
    ImGui::Button("Button6");
    
    ImGui::EndTable();
    
    ImGui::End();
}
    
