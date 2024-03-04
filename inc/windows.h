#pragma once

#include <array>

class UIWidget {
public:
    virtual void display() = 0;
};

class GlobalWindow {
public:
    GlobalWindow(std::array<UIWidget*, 3> widgets);
    void display();
private:
    std::array<UIWidget*, 3> widgets;
};
