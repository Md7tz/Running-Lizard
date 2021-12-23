#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <chrono>
#include <cstdint>

inline uint64_t CurrentTime_milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

inline uint64_t CurrentTime_microseconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

inline uint64_t CurrentTime_nanoseconds()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

#endif  /* CURRENT_TIME_H */