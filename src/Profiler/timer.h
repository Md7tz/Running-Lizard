#ifndef TIMER_H
#define TIMER_H

#include <chrono>           // Time
#include <iostream>  	    // Debugging

class Timer {
private:
    static float total_elapsed;                             // Time gone since start of executions
    static int frame;                                       // Tracks the number of frame
    std::chrono::_V2::system_clock::time_point start, end;  // 
    std::chrono::duration<float> elapsed;                   // Time gone between every frame
    std::time_t end_time;
public:
    Timer();
    ~Timer();
};

#endif