#ifndef ledstrip_h
#define ledstrip_h

#include <Adafruit_NeoPixel.h>
#include "SerialLogger.h"
#include "Lib_Timer.h"
#include "SaveAnimation01.h"

#define LED_Default_Brightness 96
#define LED_Maximal_Brightness 250
#define LED_Minimal_Brightness 2

#define LED_Brightness_Step 1
#define LED_Brightness_Step_time 5

#define CA_COLORS_MAX_COUNT 3

class LedStrip
{
public:
    enum class Mode
    {
        OFF,
        ON
    };

    enum class Animation
    {
        NO,
        BRIGHTNESS_PLUS,
        BRIGHTNESS_MINUS,
        FADE_IN,
        FADE_OUT,
        TIMER_SETTINGS
    };

    const bool haveSattingsMode = true;
    const uint32_t colors[4] = {0x00000000, 0x00dfef63, 0x003ccd3b, 0x004b4ff1};

    LedStrip(uint16_t numPixels, uint8_t pin, uint8_t type = NEO_GRB + NEO_KHZ800)
        : strip(numPixels, pin, type), timerForAnimation(LED_Brightness_Step_time), h(0), m(0), s(0)
    {
    }

    void setup();
    void loop();

    void setBrightness(uint8_t brightness); // установка настроек ленты (яркость)

    void setMode(Mode mode); // установка режима работы ленты
    void forceBritnessAnimation();
    void ShowAnimationsFrameFortimer(uint32_t time);
    void ShowAnimationsFrameFortimer();
    void showSaveAnimation();
    void showCommandAcceptionAnimation();
    Mode getMode() { return currentMode; }; // получение текущего режима работы ленты

private:
    const char *moduleName = "LedStrip";
    Adafruit_NeoPixel strip;
    Timer timerForAnimation;
    uint8_t h, m, s;
    uint8_t brightness = LED_Default_Brightness;
    int16_t currentBrightness = 0;
    Mode currentMode = Mode::OFF;

    uint32_t LigthColor = 0x00FFFFFF; // Белый цвет по умолчанию

    Animation animation = Animation::NO;

    void fadeInTakt();
    void fadeOutTakt();
    void brightnessPlusTakt();
    void brightnessMinusTakt(bool toNull = false);
    bool isBrightnessChenged(uint8_t target);

    void timeReformation(uint32_t time, uint8_t *h, uint8_t *m, uint8_t *s);
};

#endif