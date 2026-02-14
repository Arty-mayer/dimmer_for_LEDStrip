#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "Lib_Timer.h"
#include "NotifyInputsListener.h"
#include "InputsControl.h"
#include "LedStrip.h"
#include "LightTimer.h"
#include <EEPROM.h>

#define TIMERS_SETTINGS_TIMEOUT 3000 

#define EEPROM_BRIGHTNESS_ADDR 0x00
#define EEPROM_TIMER_ADDR 0x01

class Maincontrol : public NotifyInputsListener, public NotifyLightModesListener
{
public:
  Maincontrol(uint8_t buttonPin, uint8_t pwmPin, uint8_t levelsCount, uint16_t stripsLong, const uint8_t *brightnessLevels);
  void setup();
  void loop();
  void notifyInput(Inputs inputState, Inputs inputLastState) override;
  void notifyTimer() override;

private:
  uint8_t brightnessLevel = 0;
  bool isLightOn = false;
  const uint8_t *brightnessLevels;
  uint8_t levelsCount;

  LedStrip ledStrip;
  InputsControl inputsControl;
  LightTimer lightTimer;
  Timer helpTimer = Timer(3000);

  void inputsHandler(Inputs inputState);
  void switchOff();
  void switchOn();
  void switchBrightness();
  void saveBrightnessToEEPROM();
  void saveTimerToEEPROM();
};

#endif