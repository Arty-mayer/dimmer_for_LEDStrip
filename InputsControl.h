#ifndef inputscontrol_h
#define inputscontrol_h

#include <Arduino.h>
#include "Lib_Button.h"
#include "NotifyInputsListener.h"

#define BTN_SHORT_TIME 40
#define BTN_LONG_TIME 1000
#define NEWSTATE_TIME 300

enum class Inputs
{
    NONE,
    BUTTON_1,
    BUTTON_1_LONG
};

class InputsControl
{
private:
    // для версии с механическими кнопками
    Button button1;

    // для версии с сенсорными кнопками
    // uint8_t pinBtn1;

    Timer timerButton1;

    Timer timerNewState;
    NotifyInputsListener *notifyListener = nullptr;

    Inputs currentState = Inputs::NONE;
    Inputs lastState = Inputs::NONE;

    bool btn1lock = false;

    void btnListener();
    void setNewState(Inputs newState);
    void stateReset();

public:
    InputsControl(uint8_t pin1);
    void loop();
    Inputs getCurrentState();
    Inputs getLastState();
    void setNotifyListener(NotifyInputsListener *listener);
};

#endif