#include "LedStrip.h"

void LedStrip::setup()
{
    strip.begin();                                  // Инициализация ленты
    strip.clear();                                  // Очистка (все погашены)
    strip.setBrightness(currentBrightness);                       // Установка яркости (0-255)
   
    strip.show();
    Serial.println("LedStrip setup completed");
}

void LedStrip::setBrightness(uint8_t brightness)
{
    if (brightness > LED_Maximal_Brightness)
    {
        brightness = LED_Maximal_Brightness;
    }
    else if (brightness < LED_Minimal_Brightness)
    {
        brightness = LED_Minimal_Brightness;
    }

    currentBrightness = brightness;
    strip.setBrightness(currentBrightness);
    strip.show();
}

void LedStrip::setMode(FunctionsMode mode)
{
    currentMode = mode;
    switch (currentMode)
    {
    case FunctionsMode::OFF:
        strip.clear();
        strip.show();
        break;
    case FunctionsMode::ON:
        for (uint16_t i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, bgColor); 
        }
        strip.show();
        break;
    
    default:
        break;
    }
}
