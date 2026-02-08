#include "Lib_Timer.h"

Timer::Timer(unsigned long time) : ttime(time), timerEnd(true)
{
  ttime = time;
  timerEnd = true;
  timerOn = false;
}

void Timer::setTime(unsigned long time)
{
  ttime = time;
}

void Timer::timerStart()
{
  timerEnd = false;
  timerOn = true;
  t0 = millis();
}

void Timer::timerStop()
{
  timerOn = false;
}

void Timer::tick()
{
  if (timerOn)
  {
    if (millis() - t0 >= ttime)
    {
      timerEnd = true;
      timerOn = false;
    }
  }
}

bool Timer::isTimerOn()
{
  return timerOn;
}

bool Timer::isTimerEnd()
{
  return timerEnd;
}
