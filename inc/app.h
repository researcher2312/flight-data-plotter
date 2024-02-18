#pragma once

#include "receiver.h"
#include "graph.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>


class App {
public:
  bool setup();
  void close();
  void update();
  void process_events();
  bool wants_to_close = false;
  NetworkReceiver receiver;
  Graph graph;
private:
  void display();
  SDL_GLContext gl_context;
  SDL_Window* window;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  bool show_demo_window = true;
};

