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
    LOGV(moduleName, "Time changed to", time / 60000);
}

void LightTimer::setTimerOn()
{
    if (time == 0)
    {
        LOG(moduleName, "Timer is set to 0, cannot turn on timer");
        timerMode = false;
        return;
    }
    settingsMode = false;
    timerMode = true;
    mainTimer.setTime(30000);
    mainTimer.timerStart();
    LOGV(moduleName, "timer start", time / 60000);
}

void LightTimer::setTimerOff()
{
    LOG(moduleName, "Turning off timer");
    timerMode = false;
    mainTimer.timerStop();
}

void LightTimer::setNotifyListener(NotifyLightModesListener *lstnr)
{
    listener = lstnr;
}

unsigned long LightTimer::getRemainingTime()
{
    return mainTimer.getRemaining();
}

void LightTimer::timerEndAction()
{
    LOG(moduleName, "timer is end in timer...");
    timerMode = false;
    if (listener == nullptr)
    {
        LOG(moduleName, "i have no a listener");
        return;
    }
    listener->notifyTimer();
    LOG(moduleName, "Done");
}

void LightTimer::enterSettingsMode()
{
    LOG(moduleName, "Entering timer settings mode");
    setTimerOff();
    settingsMode = true;
}

void LightTimer::setTimeInMinutes(uint8_t minutes)
{
    LOGV(moduleName, "Setting time forced in minutes to (minutes)", minutes);
    setTimerOff();
    time = minutes * 60000;
}