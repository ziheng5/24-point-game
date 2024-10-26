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

    // ��ʼ��ʱ
    void start() {
        running = true;
        start_time = clock::now();
    }

    // ֹͣ��ʱ
    void stop() {
        if (running) {
            running = false;
            elapsed_time = clock::now() - start_time;
        }
    }

    // ������ʱ��
    void reset() {
        stop();
        start();
    }

    // ��ȡ������ʱ�䣨�룩
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