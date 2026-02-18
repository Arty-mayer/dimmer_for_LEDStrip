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
    Logger::log("Time changed to: ", false);
    Logger::log(String(time / 60000).c_str(), false);
    Logger::log(" minutes");
}

void LightTimer::setTimerOn()
{
    if (time == 0)
    {
        Logger::log("Timer is set to 0, cannot turn on timer");
        timerMode = false;
        return;
    }
    Logger::log("Turning on timer: ", false);
    Logger::log(String(time / 60000).c_str());
    settingsMode = false;
    timerMode = true;
    mainTimer.setTime(30000);
    mainTimer.timerStart();
    Serial.print("timer start -> ");
    Serial.println(time);
}

void LightTimer::setTimerOff()
{
    Logger::log("Turning off timer");
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
    Serial.println("timer is end in timer...");
    timerMode = false;
    // Logger::log("Timer ended, sending ends-notification... ", false);
    if (listener == nullptr)
    {
        Serial.println("i have no a listener");
       // Logger::log("Listener is null, cannot notify, notification skipped");
        return;
    }
    listener->notifyTimer();
    Logger::log("Done");
}

void LightTimer::enterSettingsMode()
{
    Logger::log("Entering timer settings mode");

    setTimerOff();
    settingsMode = true;
}

void LightTimer::setTimeInMinutes(uint8_t minutes)
{
    Logger::log("Setting time forced in minutes to: ", false);
    Logger::log(String(minutes).c_str(), false);
    Logger::log(" minutes");

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