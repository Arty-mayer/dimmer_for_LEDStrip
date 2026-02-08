#ifndef ledstrip_h
#define ledstrip_h

#include <Adafruit_NeoPixel.h>
// #include "Lib_Timer.h"

#define LED_Default_Brightness 96
#define LED_Maximal_Brightness 254
#define LED_Minimal_Brightness 2
#define LED_Brightness_Step 14

class LedStrip
{
public:
    enum class FunctionsMode
    {
        OFF,
        ON
        //      SETTINGS_TEMPERATURE,
        //      SETTINGS_TIMER
    };

    const bool haveSattingsMode = true;

    LedStrip(uint16_t numPixels, uint8_t pin, uint8_t type = NEO_GRB + NEO_KHZ800)
        : strip(numPixels, pin, type)
    {
    }
    void setup();              // вызывается в setup()   (при старте)
    void loop();               // петля, вызывается в loop() и вызывает тригеры обновления ленты
    void setBrightnessPluss(); // установка настроек ленты (яркость+)
    void setBrightnessMinus();
    void setBrightness(uint8_t brightness); // установка настроек ленты (яркость)

    void setMode(FunctionsMode mode);                // установка режима работы ленты
    FunctionsMode getMode() { return currentMode; }; // получение текущего режима работы ленты
private:
    Adafruit_NeoPixel strip;

    // Timer updateTimer = Timer(25); // Таймер обновления ленты каждые 25 мс
    uint8_t currentBrightness = LED_Default_Brightness;
    FunctionsMode currentMode = FunctionsMode::OFF;
    // FunctionsMode previousMode = FunctionsMode::OFF;

    uint32_t bgColor = 0x00FFFFFF; // Белый цвет по умолчанию
    // uint32_t pixelColor01 = 0x00000000; // Черный цвет по умолчанию
    // uint32_t pixelColor02 = 0x00FF0000; // Черный цвет по умолчанию

    // void stripUpdate();
};

#endif