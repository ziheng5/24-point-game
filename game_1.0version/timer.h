#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>
#include <thread>
class Timer {
public:
    using clock = std::chrono::high_resolution_clock;
    using second = std::chrono::duration<float>;

    // 开始计时
    void start() {
        running = true;
        start_time = clock::now();
    }

    // 停止计时
    void stop() {
        if (running) {
            running = false;
            elapsed_time = clock::now() - start_time;
        }
    }

    // 重启计时器
    void reset() {
        stop();
        start();
    }

    // 获取经过的时间（秒）
    second getElapsedTime() const {
        if (running) {
            return clock::now() - start_time;
        }
        else {
            return elapsed_time;
        }
    }

private:
    bool running = false;
    clock::time_point start_time;
    second elapsed_time;
};

#endif