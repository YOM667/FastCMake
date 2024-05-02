#pragma once

#include <chrono>
#include <ctime>
#include <iostream>
#include <cmath>
#include <chrono>

#include <sstream>
#include <iomanip>

typedef long long NanoTime;

const long NANOSECOND = 1000000000L;
const float FRAMERATE = 0.001f;

using namespace std;

namespace youm::utility
{
    NanoTime getNowNanoTime();

    string getTime(const char* format);
}
