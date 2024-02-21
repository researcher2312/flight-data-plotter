#pragma once

#include <list>
#include <SDL.h>
#include <SDL_opengl.h>
#include "imgui.h"
#include "windows.h"

class App {
public:
    bool setup();
    void close();
    void update();
    void process_events();
    bool wants_to_close = false;
private:
    void display();
    SDL_GLContext gl_context;
    SDL_Window* window;
    GlobalWindow main_window;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};
