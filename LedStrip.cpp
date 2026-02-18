#include "LedStrip.h"

void LedStrip::setup()
{
    strip.begin();          // Инициализация ленты
    strip.clear();          // Очистка (все погашены)
    strip.setBrightness(0); // Установка яркости (0-255)
    strip.show();

   // Serial.println("LedStrip setup completed");
}

void LedStrip::loop()
{
    timerForAnimation.tick();
    if (animation == Animation::NO)
        return;
    if (timerForAnimation.isTimerEnd())
    {
        timerForAnimation.timerStart();
        switch (animation)
        {
        case Animation::BRIGHTNESS_PLUS:
            brightnessPlusTakt();
            break;
        case Animation::BRIGHTNESS_MINUS:
            brightnessMinusTakt();
            break;
        case Animation::FADE_IN:
            fadeInTakt();
            break;
        case Animation::FADE_OUT:
            fadeOutTakt();
            break;

        default:
            break;
        }
    }
}

void LedStrip::setBrightness(uint8_t newBrightness)
{

    if (newBrightness > LED_Maximal_Brightness)
    {
        newBrightness = LED_Maximal_Brightness;
    }
    else if (newBrightness < LED_Minimal_Brightness)
    {
        newBrightness = LED_Minimal_Brightness;
    }

    brightness = newBrightness;

    Logger::log("Setting brightness to: ", false);
    Logger::log(String(brightness).c_str());

    if (currentMode == Mode::OFF)
    {
        currentBrightness = brightness;
        return;
    }

    if (currentBrightness > brightness)
    {
        animation = Animation::BRIGHTNESS_MINUS;
    }
    else if (currentBrightness < brightness)
    {
        animation = Animation::BRIGHTNESS_PLUS;
    }
}

void LedStrip::setMode(Mode mode)
{
    currentMode = mode;
    switch (currentMode)
    {
    case Mode::OFF:
        animation = Animation::FADE_OUT;
        break;
    case Mode::ON:
        animation = Animation::FADE_IN;
        currentBrightness = 10;
        strip.setBrightness(currentBrightness);
        for (uint16_t i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, LigthColor);
        }
        strip.show();
        break;

    default:
        break;
    }
}

void LedStrip::forceBritnessAnimation()
{
    currentBrightness = brightness;
}

void LedStrip::ShowAnimationsFrameFortimer(uint32_t time)
{
   // Serial.println((long)(time / 1000));
    timeReformation(time, &h, &m, &s);
    ShowAnimationsFrameFortimer();
}

void LedStrip::ShowAnimationsFrameFortimer()
{
  //  Serial.println(m);
    uint8_t minutsLED = m / 5;
    strip.clear();
    strip.setBrightness(20);
    strip.setPixelColor(40, colors[3]);
    strip.setPixelColor(52, colors[3]);
    strip.setPixelColor(60, colors[3]);
    for (uint8_t i = 0; i < minutsLED; i++)
    {

        if (i + 41 == 43 || i + 41 == 46 || i + 44 == 49)
        {
            strip.setPixelColor(41 + i, colors[2]);
        }
        else
        {
            strip.setPixelColor(41 + i, colors[1]);
        }
    }
    for (uint8_t i = 0; i < h; i++)
    {
        if (i + 53 == 54 || i + 53 == 56 || i + 53 == 58)
        {
            strip.setPixelColor(53 + i, colors[2]);
        }
        else
        {
            strip.setPixelColor(53 + i, colors[1]);
        }
    }
    strip.show();
}

void LedStrip::brightnessMinusTakt(bool toNull = false)
{
    uint8_t targetBrightness;
    if (toNull)
        targetBrightness = 0;
    else
    {
        targetBrightness = brightness;
    }
    if (!isBrightnessChenged(targetBrightness))
        return;

    currentBrightness = currentBrightness - LED_Brightness_Step;
    if (currentBrightness <= targetBrightness)
    {
        currentBrightness = targetBrightness;
        strip.setBrightness(currentBrightness);
        strip.show();
        animation = Animation::NO;
        return;
    }
    strip.setBrightness(currentBrightness);
    strip.show();
}

void LedStrip::brightnessPlusTakt()
{
    if (!isBrightnessChenged(brightness))
        return;

    currentBrightness = currentBrightness + LED_Brightness_Step;
    if (currentBrightness >= brightness)
    {
        currentBrightness = brightness;
        strip.setBrightness(currentBrightness);
        strip.show();
        animation = Animation::NO;
        return;
    }
    strip.setBrightness(currentBrightness);
    strip.show();
}

bool LedStrip::isBrightnessChenged(uint8_t target)
{
    if (target == currentBrightness)
    {
        animation = Animation::NO;
        return false;
    }
    return true;
}

void LedStrip::showSaveAnimation()
{
    strip.setBrightness(20);
    strip.clear();
    PictureRamPtr pic;
    for (uint8_t i = 0; i < 2; i++)
    {
        for (uint8_t frame = 0; frame < SaveAnimation01::getFrameCont(); frame++)
        {
            pic = SaveAnimation01::getPictureRam(frame);

            for (uint8_t pix = 0; pix < SaveAnimation01::getPixelCount(); pix++)
            {
                strip.setPixelColor(pic[pix][0], colors[pic[pix][1]]);
            }
            strip.show();
            delay(SaveAnimation01::getFrameDuration());
        }
    }

    delay(SaveAnimation01::getFrameDuration());
    if (currentMode == Mode::ON)
    {
        for (uint16_t i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, LigthColor);
        }
        strip.setBrightness(brightness);
        strip.show();
    }
    else if (currentMode == Mode::OFF)
    {
        ShowAnimationsFrameFortimer();
    }
}

void LedStrip::timeReformation(uint32_t time, uint8_t *h, uint8_t *m, uint8_t *s)
{
    uint32_t totalSeconds = time / 1000;

    *s = totalSeconds % 60;
    *m = (totalSeconds / 60) % 60;
    *h = (totalSeconds / 3600); // часы без ограничения
}

void LedStrip::fadeInTakt()
{
    brightnessPlusTakt();
}

void LedStrip::fadeOutTakt()
{
    brightnessMinusTakt(true);
    if (animation == Animation::NO)
    {
        strip.clear();
        strip.show();
    }
}