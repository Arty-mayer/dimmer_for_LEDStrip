#ifndef notifyinputsrecepient_h
#define notifyinputsrecepient_h

// Forward declaration to avoid circular include with InputsControl.h
enum class Inputs;

class NotifyInputsListener
{
public:
    virtual void notify(Inputs inputState, Inputs inputLastState) = 0;
};  
#endif
