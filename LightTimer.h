#ifndef lichtcontrol_h

#define lichtcontrol_h
#include <Arduino.h>
#include "CountdownTimer.h"
#include "NotifyLightModesListener.h"
#include "SerialLogger.h"
// #include "src/ModulesInterface.h"

class LightTimer
{

public:
    const unsigned long MAX_TIME = 7200000;          // 120 min  больше 240 минут (14 400 000) нельзя!  
    const unsigned long STEP_LONG = 600000;          // 10 min
    const unsigned long STEP_SHORT = 300000;         // 5 min
    const unsigned long LS_SEPARATOR_TIME = 1800000; // 30 min

    LightTimer();

    void loop();

    void TimerPlus();
    void setTimerOn();
    void setTimerOff();
    void setNotifyListener(NotifyLightModesListener *lstnr);
    void enterSettingsMode();
    void setTimeInMinutes(uint8_t minutes);  

    bool isTimerOn() { return timerMode; };
    bool isSettingsMode() { return settingsMode; };

    unsigned long getRemainingTime();
    unsigned long getMaxTime() { return MAX_TIME; }
    unsigned long getTime() { return time; }
    uint8_t getTimeInMinutes() { return time / 60000; }

    void setSettingsNotifyListener(class SettingsInterface *listener) // установка слушателя уведомлений настроек
    {
        settingsListener = listener;
    };

private:
    bool timerMode;    // false - off, true - on
    bool settingsMode; // false - normal, true - settings
    SettingsInterface *settingsListener = nullptr;
    // LightModes lightMode;
    //  LightModes lightState;

    NotifyLightModesListener *listener = nullptr;

    //unsigned long maxTime;
    unsigned long time;
    CountdownTimer mainTimer;
    // Timer settingsTimer;

    void timerEndAction();
};

#endif