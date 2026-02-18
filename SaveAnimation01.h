#ifndef SAVEANIMATION01_H
#define SAVEANIMATION01_H

#include <Arduino.h>
#include <avr/pgmspace.h>

#define FRAME_DURATION 250
#define FRAME_COUNT 6
#define PIXEL_COUNT 21

typedef const uint8_t (*PictureFlashPtr)[2];
typedef uint8_t (*PictureRamPtr)[2];

class SaveAnimation01
{
public:
    // Данные во FLASH
    static const uint8_t picture00[PIXEL_COUNT][2] PROGMEM;
    static const uint8_t picture01[PIXEL_COUNT][2] PROGMEM;
    static const uint8_t picture02[PIXEL_COUNT][2] PROGMEM;
    static const uint8_t picture03[PIXEL_COUNT][2] PROGMEM;
    static const uint8_t picture04[PIXEL_COUNT][2] PROGMEM;
    static const uint8_t picture05[PIXEL_COUNT][2] PROGMEM;

    static uint8_t getFrameCont() { return FRAME_COUNT; }
    static uint8_t getFrameDuration() { return FRAME_DURATION; }

    static uint8_t getPixelCount();

    // Получить указатель на FLASH (внутреннее использование)
    static PictureFlashPtr getPicture(uint8_t pictureNummer);

    // 🔥 Получить обычный массив в RAM
    static PictureRamPtr getPictureRam(uint8_t pictureNummer);

private:
    // Буфер в SRAM (максимальный размер = 19)
    static uint8_t buffer[PIXEL_COUNT][2];
};

#endif