#ifndef COUNTDOWNTIMER_H
#define COUNTDOWNTIMER_H

#include "Lib_Timer.h"

class CountdownTimer : public Timer {
public:
    CountdownTimer(unsigned long time) : Timer(time) {}

    unsigned long getRemaining() {
        if (!timerOn || timerEnd) return 0;
        unsigned long elapsed = millis() - t0;
        if (elapsed >= ttime) return 0;
        return ttime - elapsed;
    }
};

#endif