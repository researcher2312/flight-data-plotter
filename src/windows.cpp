#include "imgui.h"
#include "windows.h"

GlobalWindow::GlobalWindow(std::array<UIWidget*, 3> new_widgets)
{
    widgets = new_widgets;
}


void GlobalWindow::display()
{
    static bool open_window = true;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGui::Begin("Window", &open_window, flags);
    ImGui::BeginTable("window_table", 2);
    
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    widgets.at(0)->display();
    
    ImGui::TableSetColumnIndex(1);
    widgets.at(1)->display();
    
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    widgets.at(2)->display();

    
    ImGui::EndTable();
    
    ImGui::End();
}
