#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:
    static bool enabled; // Флаг для включения/выключения логирования

    static void log(const char *message, bool newLine = true);

    static void enableLogging(uint32_t speed = 115200);
   
};

#endif