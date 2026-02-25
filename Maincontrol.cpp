#include "Maincontrol.h"

void Maincontrol::setup()
{

    ledStrip.setup();

    loadBrightnessFromEEPROM();
    loadTimerFromEEPROM();
}

void Maincontrol::loop()
{
    if (inputsLock && helpTimer.isTimerEnd())
    {
        inputsLock = false;
    }
    helpTimer.tick();
    lightTimer.loop();
    inputsControl.loop();
    ledStrip.loop();
    if (helpTimer.isTimerEnd())
    {
        StateControl();
    }
}

void Maincontrol::notifyInput(Inputs inputState, Inputs inputLastState)
{
    if (inputsLock)
        return;
    inputsHandler(inputState);
}

void Maincontrol::notifyTimer()
{
    switchOff();
}

void Maincontrol::showTimerSettings()
{
    uint32_t time = lightTimer.getTime();
    ledStrip.ShowAnimationsFrameFortimer(time);
}

void Maincontrol::StateControl()
{
    switch (currentState)
    {
    case State::SETTINGS_TIMER:
        switchOn();
        lightTimer.setTimerOn();
        currentState = State::STANDING_BY;
        break;

    case State::BRITHNESS_CHANGE:
        currentState = State::STANDING_BY;
        break;

    default:
        break;
    }
}

void Maincontrol::inputsHandler(Inputs inputState)
{
    if (ledStrip.getMode() == LedStrip::Mode::ON)
    {
        if (inputState == Inputs::BUTTON_1)
        {
            helpTimer.timerStart();
            currentState = State::BRITHNESS_CHANGE;
            switchBrightness();
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
            if (currentState == State::BRITHNESS_CHANGE)
            {
                currentState = State::SAVE_BRIGHTNESS;
                helpTimer.timerStop();
                saveBrightnessToEEPROM();
            }
            else if (currentState == State::STANDING_BY)
            {
                ledStrip.showCommandAcceptionAnimation();
                switchOff();
            }
        }
    }
    else
    {
        if (inputState == Inputs::BUTTON_1)
        {
            if (currentState == State::SETTINGS_TIMER)
            {

                helpTimer.timerStart();
                lightTimer.TimerPlus();
                showTimerSettings();
            }
            else if (currentState == State::STANDING_BY)
            {
                lightTimer.setTimerOff();
                switchOn();
            }
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
            if (currentState == State::SETTINGS_TIMER)
            {

                helpTimer.timerStart();
                saveTimerToEEPROM();
            }
            else if (currentState == State::STANDING_BY)
            {
                helpTimer.timerStart();
                lightTimer.enterSettingsMode();
                currentState = State::SETTINGS_TIMER;
                showTimerSettings();
                delay(700);
            }
        }
    }
}

void Maincontrol::switchOff()
{
    LOG("MainControl", "Switching off light");
    ledStrip.setMode(LedStrip::Mode::OFF);
    lightTimer.setTimerOff();
    helpTimer.timerStart();
    inputsLock = true;
    delay(1000);
}

void Maincontrol::switchOn()
{
    LOG("MainControl", "Switching on light");
    ledStrip.setMode(LedStrip::Mode::ON);
}

void Maincontrol::switchBrightness()
{
    if (ledStrip.getMode() == LedStrip::Mode::OFF)
    {
        LOG("MainControl", "Brightness change ignored because light is off");
        return;
    }

    brightnessLevel = (brightnessLevel + 1) % levelsCount; // вместо конструкции с if для цикличного перебора уровней яркости
    LOGV("MainControl", "Change brightness to", brightnessLevel);
    ledStrip.setBrightness(brightnessLevels[brightnessLevel]);
}

void Maincontrol::saveBrightnessToEEPROM()
{
    EEPROM.update(EEPROM_BRIGHTNESS_ADDR, brightnessLevel);
    LOGV("MainControl", "Saving brightness to EEPROM", brightnessLevel);
    ledStrip.showSaveAnimation();
}

void Maincontrol::saveTimerToEEPROM()
{
    unsigned long timerValue = lightTimer.getTimeInMinutes();
    EEPROM.update(EEPROM_TIMER_ADDR, timerValue);
    LOGV("MainControl", "Saving timer to EEPROM", brightnessLevel);
    ledStrip.showSaveAnimation();
}

void Maincontrol::loadBrightnessFromEEPROM()
{
    brightnessLevel = EEPROM.read(EEPROM_BRIGHTNESS_ADDR);
    if (brightnessLevel >= levelsCount)
    {
        brightnessLevel = brightnessLevels[levelsCount - 1];
    }
    ledStrip.setBrightness(brightnessLevels[brightnessLevel]);
    LOGV("MainControl", "Loading brightness from EEPROM:", brightnessLevel);
}

void Maincontrol::loadTimerFromEEPROM()
{
    uint8_t timerValue = EEPROM.read(EEPROM_TIMER_ADDR);
    uint32_t timerValueInMillis = timerValue * 60000;

    if (timerValueInMillis > lightTimer.getMaxTime())
    {
        timerValueInMillis = lightTimer.getMaxTime();
    }
    lightTimer.setTimeInMinutes(timerValue);
    LOGV("MainControl", "Loading timer from EEPROM:", timerValue);
}
