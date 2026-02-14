#include "Maincontrol.h"

Maincontrol::Maincontrol(uint8_t buttonPin, uint8_t pwmPin, uint8_t levelsCount, uint16_t stripsLong, const uint8_t *brightnessLevels) : inputsControl(buttonPin), ledStrip(stripsLong, pwmPin), levelsCount(levelsCount), brightnessLevels(brightnessLevels)
{
    inputsControl.setNotifyListener(this);
}

void Maincontrol::setup()
{

    ledStrip.setup();
    // pinMode(pwmPin, OUTPUT);
    brightnessLevel = EEPROM.read(EEPROM_BRIGHTNESS_ADDR);
    if (brightnessLevel >= levelsCount)
    {
        brightnessLevel = brightnessLevels[levelsCount - 1];
    }
}

void Maincontrol::loop()
{
    helpTimer.tick();
    lightTimer.loop();
    inputsControl.loop();
    if (helpTimer.isTimerEnd())
    {
       if (lightTimer.isSettingsMode())
        {
            lightTimer.setTimerOn();
        }
    }
}

void Maincontrol::notifyInput(Inputs inputState, Inputs inputLastState)
{
    inputsHandler(inputState);
}

void Maincontrol::notifyTimer()
{
    switchOff();
}

void Maincontrol::inputsHandler(Inputs inputState)
{

    if (isLightOn)
    {
        if (inputState == Inputs::BUTTON_1)
        {
            helpTimer.timerStart();
            switchBrightness();
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
            if (helpTimer.isTimerOn())
            {
                helpTimer.timerStop();
                saveTimerToEEPROM();
            }
            else
            {
                switchOff();
            }
        }
    }
    else
    {
        if (inputState == Inputs::BUTTON_1)
        {
            if (helpTimer.isTimerOn())
            {
                helpTimer.timerStart();
                lightTimer.TimerPlus();
            }
            else
            {
                lightTimer.setTimerOff();
            }
            switchOn();
        }
        else if (inputState == Inputs::BUTTON_1_LONG)
        {
            if (helpTimer.isTimerOn())
            {
                saveTimerToEEPROM();
                helpTimer.timerStart();
            }
            else
            {
                lightTimer.enterSettingsMode();
                helpTimer.timerStart();
            }
        }
    }
}

void Maincontrol::switchOff()
{
    isLightOn = false;
    ledStrip.setMode(LedStrip::FunctionsMode::OFF);
    lightTimer.setTimerOff();
}

void Maincontrol::switchOn()
{
    isLightOn = true;
    ledStrip.setMode(LedStrip::FunctionsMode::ON);
}

void Maincontrol::switchBrightness()
{
    if (!isLightOn)
    {
        return;
    }
    brightnessLevel = (brightnessLevel + 1) % levelsCount; // вместо конструкции с if для цикличного перебора уровней яркости
    ledStrip.setBrightness(brightnessLevels[brightnessLevel]);
}

void Maincontrol::saveBrightnessToEEPROM()
{
    EEPROM.update(EEPROM_BRIGHTNESS_ADDR, brightnessLevel);
    // визуализация сохранения яркости (мигание текущим уровнем яркости)
    // TODO: переписать под LED Strip
    
    
}

void Maincontrol::saveTimerToEEPROM()
{


}
