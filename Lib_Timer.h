#ifndef lib_timer_h
#define lib_timer_h

#include <Arduino.h>

 class Timer {
  public: 

  Timer (unsigned long time) ; 
 
  void setTime (unsigned long time);
  void timerStart();
  void timerStop();
  void tick ();
  bool isTimerEnd();
  bool isTimerOn();
  
  
  protected: 
  
  bool timerEnd;
  bool timerOn;
  unsigned long ttime;
  unsigned long t0;
};
#endif