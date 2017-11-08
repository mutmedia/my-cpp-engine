#ifndef TIME_H
#define TIME_H

namespace Time {
    static float delta_time = 0.0f;
    static float total_time = 0.0f;
    void Init(const float totaltime);
    void Update(const float totaltime);
    float DeltaTime();
    float TotalTime();
};

#endif
