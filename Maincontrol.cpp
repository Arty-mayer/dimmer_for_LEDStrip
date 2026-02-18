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
  //  Serial.println("timer is end in main");
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
        // TODO Визуализация изменения яркости (мигание, плавное изменение яркости и т.д.)
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
            //Serial.println("BRITHNESS_CHANGE");
            helpTimer.timerStart();
            currentState = State::BRITHNESS_CHANGE;
            switchBrightness();
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
            if (currentState == State::BRITHNESS_CHANGE)
            {
              //  Serial.println("SAVE_BRIGHTNESS");
                currentState = State::SAVE_BRIGHTNESS;
                // TODO рассмотреть варимант с изменением времени вспомогательного таймера.
                helpTimer.timerStop();
                saveBrightnessToEEPROM();
            }
            else if (currentState == State::STANDING_BY)
            {
                Serial.println("switchOff");
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
               // Serial.println("TimerPlus");
                helpTimer.timerStart();
                lightTimer.TimerPlus();
                showTimerSettings();
            }
            else if (currentState == State::STANDING_BY)
            {
                // lightTimer.setTimerOff();
                Serial.println("switchOn");
                switchOn();
            }
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
          //  Serial.println("Long press detected");
            if (currentState == State::SETTINGS_TIMER)
            {
            //    Serial.println("Saving timer settings");
                helpTimer.timerStart();
                saveTimerToEEPROM();
            }
            else if (currentState == State::STANDING_BY)
            {
                //Serial.println("Entering timer settings mode");
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
    Logger::log("Switching off light");
    // isLightOn = false;
    ledStrip.setMode(LedStrip::Mode::OFF);
    lightTimer.setTimerOff();
    helpTimer.timerStart();
    inputsLock = true;
    delay(1000); // TODO задержка для визуализации выключения (можно убрать или заменить на мигание светодиода)
}

void Maincontrol::switchOn()
{
    Logger::log("Switching on light");
    // isLightOn = true;
    ledStrip.setMode(LedStrip::Mode::ON);
}

void Maincontrol::switchBrightness()
{
    if (ledStrip.getMode() == LedStrip::Mode::OFF)
    {
        Logger::log("Brightness change ignored because light is off");
        return;
    }
    Logger::log("Switching brightness: ");
    brightnessLevel = (brightnessLevel + 1) % levelsCount; // вместо конструкции с if для цикличного перебора уровней яркости
    Logger::log(" -brightness level: ", false);
    Logger::log(String(brightnessLevel).c_str());
    ledStrip.setBrightness(brightnessLevels[brightnessLevel]);
}

void Maincontrol::saveBrightnessToEEPROM()
{

    EEPROM.update(EEPROM_BRIGHTNESS_ADDR, brightnessLevel);
    Logger::log("Saving brightness to EEPROM: ");
    Logger::log(String(brightnessLevel).c_str());
    ledStrip.showSaveAnimation();
}

void Maincontrol::saveTimerToEEPROM()
{
    unsigned long timerValue = lightTimer.getTimeInMinutes();
    EEPROM.update(EEPROM_TIMER_ADDR, timerValue);
    Logger::log("Saving timer to EEPROM: ");
    Logger::log(String(timerValue).c_str());
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
    Logger::log("Loaded brightness from EEPROM: ");
    Logger::log(String(brightnessLevel).c_str());
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
    Logger::log("Loaded timer from EEPROM: ");
    Logger::log(String(timerValue).c_str());
}
