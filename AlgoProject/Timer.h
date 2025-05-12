#include <chrono>
#include <iostream>

class ElapsedTimeTimer {
public:
    // Starts the timer
    void start() {
        start_time = std::chrono::steady_clock::now();
    }

    // Stops the timer and returns the elapsed time in seconds
    double stop() {
        auto end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        return elapsed.count();
    }

private:
    std::chrono::steady_clock::time_point start_time;
};
