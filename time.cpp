#include "time.h"

void Time::Update(const float totaltime) {
    delta_time = totaltime - total_time;
    total_time = total_time;
}

void Time::Init(const float totaltime) {
    total_time = totaltime;
}

float Time::DeltaTime() { return delta_time/1000.0f; }

float Time::TotalTime() { return total_time/1000.0f; }


