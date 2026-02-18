#include "SaveAnimation01.h"

const uint8_t SaveAnimation01::picture00[PIXEL_COUNT][2] PROGMEM = {
    {6, 1}, {28, 1}, {42, 1}, {43, 1}, {44, 1}, {53, 0}, {54, 0}, {55, 0}, {60, 0},
    {17, 2}, {18, 2}, {19, 2}, {35, 2}, {36, 2}, {37, 2},
    {48, 2}, {49, 2}, {50, 2}, {57, 2}, {58, 2}, {59, 2}
};

const uint8_t SaveAnimation01::picture01[PIXEL_COUNT][2] PROGMEM = {
    {6, 1}, {28, 1}, {42, 0}, {43, 1}, {44, 0}, {54, 1}, {55, 1}, {53, 1}, {60, 1},
    {17, 2}, {18, 2}, {19, 2}, {35, 2}, {36, 2}, {37, 2},
    {48, 2}, {49, 2}, {50, 2}, {57, 2}, {58, 2}, {59, 2}
};

const uint8_t SaveAnimation01::picture02[PIXEL_COUNT][2] PROGMEM = {
    {6, 0}, {28, 1}, {42, 0}, {43, 1}, {44, 0}, {53, 1}, {54, 1}, {55, 1},  {60, 1},
    {17, 2}, {18, 2}, {19, 2}, {35, 2}, {36, 2}, {37, 2},
    {48, 2}, {49, 2}, {50, 2}, {57, 1}, {58, 1}, {59, 1}
};

const uint8_t SaveAnimation01::picture03[PIXEL_COUNT][2] PROGMEM = {
    {6, 0}, {28, 1}, {42, 0}, {43, 1}, {44, 0}, {53, 1},  {54, 1}, {55, 1}, {60, 1},
    {17, 2}, {18, 2}, {19, 2}, {35, 2}, {36, 2}, {37, 2},
    {48, 1}, {49, 1}, {50, 1}, {57, 1}, {58, 1}, {59, 1}
};

const uint8_t SaveAnimation01::picture04[PIXEL_COUNT][2] PROGMEM = {
    {6, 0}, {28, 0}, {42, 0}, {43, 1}, {44, 0}, {53, 1}, {54, 1}, {55, 1}, {60, 1},
    {17, 2}, {18, 2}, {19, 2}, {35, 1}, {36, 1}, {37, 1},
    {48, 1}, {49, 1}, {50, 1}, {57, 1}, {58, 1}, {59, 1}
};

const uint8_t SaveAnimation01::picture05[PIXEL_COUNT][2] PROGMEM = {
    {6, 0}, {28, 0}, {42, 0}, {43, 0}, {44, 0}, {54, 0}, {55, 0},{53, 0}, {60, 1},
    {17, 1}, {18, 1}, {19, 1}, {35, 1}, {36, 1}, {37, 1},
    {48, 1}, {49, 1}, {50, 1}, {57, 1}, {58, 1}, {59, 1}
};

static const PictureFlashPtr pictures[FRAME_COUNT] PROGMEM = {
    SaveAnimation01::picture00,
    SaveAnimation01::picture01,
    SaveAnimation01::picture02,
    SaveAnimation01::picture03,
    SaveAnimation01::picture04,
    SaveAnimation01::picture05
};

// ===== SRAM БУФЕР =====

uint8_t SaveAnimation01::buffer[PIXEL_COUNT][2];

// ===== КОЛИЧЕСТВО ЭЛЕМЕНТОВ =====

uint8_t SaveAnimation01::getPixelCount()
{
    return PIXEL_COUNT;
}

// ===== ПОЛУЧИТЬ УКАЗАТЕЛЬ НА FLASH =====

PictureFlashPtr SaveAnimation01::getPicture(uint8_t pictureNummer)
{
    if (pictureNummer >= FRAME_COUNT) return nullptr;

    return (PictureFlashPtr)pgm_read_ptr(&pictures[pictureNummer]);
}

// ===== КОПИРОВАНИЕ В SRAM =====

PictureRamPtr SaveAnimation01::getPictureRam(uint8_t pictureNummer)
{
    PictureFlashPtr src = getPicture(pictureNummer);
  
    if (src == nullptr) return nullptr;
    for (uint8_t i = 0; i < PIXEL_COUNT; i++)
    {
        buffer[i][0] = pgm_read_byte(&(src[i][0]));
        buffer[i][1] = pgm_read_byte(&(src[i][1]));
    }

    return buffer;
}


