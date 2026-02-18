#include <Arduino.h>
#include "Maincontrol.h"
#include "SerialLogger.h"

// Настройки пинов и уровней яркости перед компиляцией

#define BUTTON_PIN 7 // пин контроллера для подключения кнопки
// #define PWM_PIN 9      // пин ШИМ для подключения MOSFET-транзистора светодиода
#define LED_STRIP_PIN 10  // пин для подключения ленты
#define LED_STRIP_LONG 61 // длина ленты в пикселях
#define LEVELS_COUNT 6    // количество уровней яркости

#define LOGGING_FORCE_ENABLED false // флаг для принудительного включения логирования (игнорирует нажатия кнопки при включении)

// 6 уровней яркости (0…255) 7 элемент - заглушка для реализации обратной связи с пользователем
// (яроксть не изменилась, значит достугнито максимальное значение. Следующее нажате переведет на минимальную яркость)
const uint8_t levels[LEVELS_COUNT] = {
    5,   // едва видно
    20,  // тускло
    50,  // комфортно
    100, // ярко
    160,
    250
  };

// конец настроек

Maincontrol maincontrol(BUTTON_PIN, LED_STRIP_PIN, LEVELS_COUNT, LED_STRIP_LONG, levels); // создание объекта главного контроллера

void setup()
{
  Serial.begin (115200);
  if (LOGGING_FORCE_ENABLED)
  {
    Logger::enableLogging();
  }
  else
  {
    loggerEnabler();
  }
  maincontrol.setup();
}

void loop()
{
  maincontrol.loop();
}

void loggerEnabler()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(100);

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    delay(300);
    if (digitalRead(BUTTON_PIN) == LOW)
    {
      delay(900);
      if (digitalRead(BUTTON_PIN) == LOW)
      {
        Logger::enableLogging();
      }
    }
  }
}
// TODO: V Добавить реализацию визуальных эффектов для сохранения, окончания таймера (мигание, плавное изменение яркости и т.д.)
// TODO: V Добавить реалиазцию згрузки настроек из eeprom при включении
// TODO: V Реализовать анимацию плавного изменения яркости при переключении уровней яркости
// TODO  V реализовать анимацию настройки таймера
// TODO: V реализовать Serial логирование функций:
//         - переделать логер 
//       V - переключение уровней яркости
//       V - вход в режим настройки таймера
//       V - изменение таймера
//       V - сохранение настроек яркости и таймера
//       V - загрузка настроек из eeprom при включении
//       V - вкл/выкл света
//       V - срабатывание таймера выключения света
//         - другие события по необходимости