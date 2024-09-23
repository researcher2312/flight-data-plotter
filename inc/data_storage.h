#pragma once

#include <vector>
#include <array>
#include <random>
#include "imgui.h"


struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset  = 0;
        Data.reserve(MaxSize);
    }
    float* begin_x() {
        return &Data[0].x;
    }
    float* begin_y() {
        return &Data[0].y;
    }
    size_t size() {
        return Data.size();
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


class DataStorage {
public:
    void generate_random_data();
    void add_point(float time, std::array<float, 3> acceleration, std::array<float, 3> rotation, std::array<float, 3> magnetic);
    float get_highest_time();
    std::array<ScrollingBuffer, 3> acceleration;
    std::array<ScrollingBuffer, 3> rotation;
    std::array<ScrollingBuffer, 3> magnetic;
private:
    std::mt19937_64 generator = std::mt19937_64{std::random_device{}()};
    std::uniform_real_distribution<float> distribution = std::uniform_real_distribution<float>(0,5);
};
    