#include <chrono>
#include <ctime>
#include <string>

std::string fileName(){
    // Get the current time
    auto currentTime = std::chrono::system_clock::now();
    std::time_t fixedTime = std::chrono::system_clock::to_time_t(currentTime);

    // Convert time to the desired format (hour-minute-second)
    char timeBuffer[8];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%H%M%S", std::localtime(&fixedTime));

    // Create the filename with the fixed time value
    std::string filename = "bulk" + std::string(timeBuffer) + ".log";

    return filename; }