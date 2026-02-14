#include "LightTimer.h"
#include "MainControl.h"

LightTimer::LightTimer() : mainTimer(0), timerMode(false), settingsMode(false), time(0)
{
}

void LightTimer::loop()
{
    if (timerMode)
    {
        mainTimer.tick();
        if (mainTimer.isTimerEnd())
        {
            timerEndAction();
        }
    }
}

void LightTimer::TimerPlus()
{
    if (!settingsMode)
    {
        return;
    }

    unsigned long timeSaved = time;

    if (time == MAX_TIME)
    {
        time = 0;
        return;
    }

    if (time < LS_SEPARATOR_TIME)
    {
        time += STEP_SHORT;
    }
    else
    {
        time += STEP_LONG;
    }

    if (time > MAX_TIME || time < timeSaved) // overflow
    {
        time = MAX_TIME;
    }
}

void LightTimer::setTimerOn()
{
    if (time == 0)
    {
        timerMode = false;
        return;
    }
    settingsMode = false;
    timerMode = true;
    mainTimer.setTime(time);
    mainTimer.timerStart();
}

void LightTimer::setTimerOff()
{
    timerMode = false;
    mainTimer.timerStop();
}

void LightTimer::setNotifyListener(NotifyLightModesListener *lstnr)
{
    listener = listener;
}

unsigned long LightTimer::getRemainingTime()
{
    return mainTimer.getRemaining();
}

void LightTimer::timerEndAction()
{
    if (listener != nullptr)
    {
        listener->notifyTimer();
    }
}

void LightTimer::enterSettingsMode()
{
    setTimerOff();
    settingsMode = true;
}

void LightTimer::setTimeInMinutes(uint8_t minutes)
{
    setTimerOff();
    time = minutes * 60000;
}

/*
void LightTimer::TimerMinus()
{
    if (startSettings())
    {
        return;
    }
    // Serial.println("TimerMinus");
    unsigned long timeSaved = time;

    if (time == 0)
    {
        time = maxTime;
        return;
    }

    if (time <= LS_SEPARATOR_TIME)
    {
        time -= STEP_SHORT;
    }
    else
    {
        time -= STEP_LONG;
    }

    if (time > timeSaved)
    { // underflow
        time = 0;
    }
}
*/