#ifndef TIME_H
#define TIME_H

namespace Time {
    void Init(const float totaltime);
    void Update(const float totaltime);
    float GetDelta();
    float GetTotal();
};

#endif
