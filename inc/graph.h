#pragma once

#include <vector>
#include <array>
#include <random>
#include "windows.h"


struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset  = 0;
        Data.reserve(MaxSize);
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x,y));
        else {
            Data[Offset] = ImVec2(x,y);
            Offset =  (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset  = 0;
        }
    }
};

struct SensorDataFrame {
    double time;
    std::array<double, 3> acceleration;
    std::array<double, 3> rotation;
    std::array<double, 3> magnetic;
};

class Graph: public UIWidget {
public:
    virtual void display();
    void add_point(SensorDataFrame& new_data, double time);
    std::mt19937_64 generator = std::mt19937_64{std::random_device{}()};
    std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0,5);
    double refresh_time = 0.0;
private:
    std::array<ScrollingBuffer, 3> acceleration;
    std::array<ScrollingBuffer, 3> rotation;
    std::array<ScrollingBuffer, 3> magnetic;
};
