#include <Arduino.h>
#include "Maincontrol.h"

// Настройки пинов и уровней яркости перед компиляцией

#define BUTTON_PIN 2 // пин контроллера для подключения кнопки
// #define PWM_PIN 9      // пин ШИМ для подключения MOSFET-транзистора светодиода
#define LED_STRIP_PIN 6   // пин для подключения ленты
#define LED_STRIP_LONG 61 // длина ленты в пикселях
#define LEVELS_COUNT 7    // количество уровней яркости

// 6 уровней яркости (0…255) 7 элемент - заглушка для реализации обратной связи с пользователем
// (яроксть не изменилась, значит достугнито максимальное значение. Следующее нажате переведет на минимальную яркость)
const uint8_t levels[LEVELS_COUNT] = {
    2,   // едва видно
    20,  // тускло
    50,  // комфортно
    110, // ярко
    200,
    255, // максимум, выше смысла нет
    255};

// конец настроек

Maincontrol maincontrol(BUTTON_PIN, LED_STRIP_PIN, LEVELS_COUNT, LED_STRIP_LONG, levels); // создание объекта главного контроллера

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup started");
  maincontrol.setup();
}

void loop()
{
  maincontrol.loop();
}