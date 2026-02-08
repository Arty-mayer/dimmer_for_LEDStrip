#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "Lib_Timer.h"
#include "NotifyInputsListener.h"
#include "InputsControl.h"
#include "LedStrip.h"
#include <EEPROM.h>

#define EEPROM_BRIGHTNESS_ADDR 0x00

class Maincontrol : public NotifyInputsListener
{
public:
  Maincontrol(uint8_t buttonPin, uint8_t pwmPin, uint8_t levelsCount, uint16_t stripsLong, const uint8_t *brightnessLevels);
  void setup();
  void loop();
  void notify(Inputs inputState, Inputs inputLastState) override;

private:
  uint8_t brightnessLevel = 0;
  bool isLightOnstate = false;
  InputsControl inputsControl;
  const uint8_t *brightnessLevels;
  uint8_t levelsCount;

  LedStrip ledStrip;

  void inputsHandler(Inputs inputState);
  void switchOnOff();
  void switchBrightness();
  void saveBrightnessToEEPROM();
};

#endif