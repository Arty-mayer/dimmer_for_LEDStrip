#include "InputsControl.h"

InputsControl::InputsControl(uint8_t pin1) : button1(pin1, true),         // button2(pin2, true), // для механических кнопок                                                                          //  pinBtn1(pin1), pinBtn2(pin2), // для сенсорных кноп
                                             timerButton1(BTN_LONG_TIME), // timerButton2(BTN_LONG_TIME),
                                             timerNewState(NEWSTATE_TIME)
{
}

Inputs InputsControl::getCurrentState()
{
    return currentState;
}

Inputs InputsControl::getLastState()
{
    return lastState;
}

void InputsControl::setNotifyListener(NotifyInputsListener *listener)
{
    notifyListener = listener;
}

void InputsControl::loop()
{
    timerNewState.tick();
    timerButton1.tick();
    // для механических кнопок
    button1.buttonListener();
    btnListener();
    stateReset();
}

void InputsControl::btnListener()
{
    if (!btn1lock)
    {
        if (button1.btnState())
        // if (digitalRead(pinBtn1) == HIGH) // для сенсорных кнопок
        {
            btn1lock = true;
            timerButton1.setTime(BTN_LONG_TIME);
            timerButton1.timerStart();
        }
    }

    else if (btn1lock)
    {
        if (!button1.btnState())
        // if (digitalRead(pinBtn1) == LOW)     // для сенсорных кнопок
        {
            btn1lock = false;
            timerButton1.timerStop();
            setNewState(Inputs::BUTTON_1);
        }
        if (timerButton1.isTimerEnd())
        {
            btn1lock = false;
            setNewState(Inputs::BUTTON_1_LONG);
        }
    }
}

void InputsControl::setNewState(Inputs newState)
{
    if (timerNewState.isTimerEnd())
    {
        timerNewState.timerStart();

        currentState = newState;
        if (notifyListener != nullptr)
            notifyListener->notifyInput(currentState, lastState);
    }
}

void InputsControl::stateReset()
{
    if (!timerNewState.isTimerEnd())
        return;

    if (btn1lock)
        return;

    if (currentState != Inputs::NONE)
    {
        lastState = currentState;
        currentState = Inputs::NONE;
    }
}
