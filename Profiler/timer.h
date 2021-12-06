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

float Timer::total_elapsed = 0;
int Timer::frame = 0;

Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}
Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    end_time = std::chrono::system_clock::to_time_t(end);

    // std::cout << elapsed.count();
    // system("Pause");
    float ms = elapsed.count() * 1000.0f;
    float s = uint8_t(elapsed.count() * 1000) / 1000.0f; // 1000th ex 1.000
    total_elapsed += s;
    // std::cout << "duration " << s << "s \n";
    // std::cout << "Time " << std::chrono::high_resolution_clock::duration().count() << "\n";

    frame += 1;
    std::cout << "Frame " << frame << "\nFinished computation at " << std::ctime(&end_time) << "Total elapsed time: " << total_elapsed << "s\nelapsed time: " << s << "s\n";
}