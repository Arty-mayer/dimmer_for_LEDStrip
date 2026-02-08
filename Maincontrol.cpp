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
    inputsControl.loop();
}

void Maincontrol::notify(Inputs inputState, Inputs inputLastState)
{
    inputsHandler(inputState);
}

void Maincontrol::inputsHandler(Inputs inputState)
{
    switch (inputState)
    {
    case Inputs::BUTTON_1:
        if (isLightOnstate)
        {
            switchBrightness();
        }
        else
        {
            switchOnOff();
        }
        break;
    case Inputs::BUTTON_1_LONG:
        if (isLightOnstate)
        {
            switchOnOff();
        }
        else
        {
            saveBrightnessToEEPROM();
        }
        break;

    default:
        break;
    }
}

void Maincontrol::switchOnOff()
{
    isLightOnstate = !isLightOnstate;
    if (!isLightOnstate)
    {
        ledStrip.setMode(LedStrip::FunctionsMode::OFF);
    }
    else
    {
        ledStrip.setMode(LedStrip::FunctionsMode::ON);
    }
}

void Maincontrol::switchBrightness()
{
    if (!isLightOnstate)
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
    bool switchKey = false;
    for (uint8_t i = 0; i < 6; i++)
    {
        if (switchKey)
        {
            switchKey = false;
            // analogWrite(pwmPin, 0);
        }
        else
        {
            switchKey = true;
            // analogWrite(pwmPin, brightnessLevels[brightnessLevel]);
        }
        delay(200);
    }
}