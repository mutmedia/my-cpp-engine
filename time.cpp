#include "time.h"
#include "stdio.h"

namespace {
    float delta_time = 0.0f;
    float total_time = 0.0f;
}

void Time::Update(const float totaltime) {
    delta_time = totaltime - total_time;
    total_time = totaltime;
}

void Time::Init(const float totaltime) {
    total_time = totaltime;
}

float Time::GetDelta() { return delta_time/1000.0f; }

float Time::GetTotal() { return total_time/1000.0f; }


