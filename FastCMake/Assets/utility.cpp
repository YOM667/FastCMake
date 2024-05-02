#include "utility.h"

namespace youm::utility
{
    NanoTime getNowNanoTime()
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());

        return ns.count();
    }
    string getTime(const char* format)
    {
        std::chrono::time_point<std::chrono::system_clock> now_time = std::chrono::system_clock::now();
        time_t t_time = std::chrono::system_clock::to_time_t(now_time);
        tm tm = *gmtime(&t_time);
        stringstream time_stream;
        time_stream << put_time(&tm, format);
        return time_stream.str();
    }
}
