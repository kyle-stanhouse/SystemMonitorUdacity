#include <string>
#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 

    int hour = seconds/3600;
    int time = seconds%3600;
    int min = time/60;
    time = time%60;
    int sec = time; 
    string HHMMSS = std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec);

    return HHMMSS;
    }