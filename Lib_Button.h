#ifndef lib_button_h
#define lib_button_h

#include <Arduino.h>
#include "Lib_Timer.h"

class Button
{

public:
    Button(byte pin, bool mode);

    void buttonListener();
    void speedyMode(bool mode);
    bool btnState();
    void setDebPause(unsigned int time);

private:
    uint8_t pin;
    bool state;
    bool timerKey;
    bool speedy;
    Timer debouncerTimer = Timer(30);
};
#endif