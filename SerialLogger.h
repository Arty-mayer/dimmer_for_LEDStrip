#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

#define LOG(module, msg) Logger::log(module, msg)
#define LOGV(module, msg, value) Logger::log(module, msg, value)

class Logger
{
public:
    static void log(const char *module, const char *message);
    static void log(const char *module, const char *message, uint8_t value);
    static void log(const char *module, const char *message, int8_t value);
    static void log(const char *module, const char *message, uint16_t value);
    static void log(const char *module, const char *message, int16_t value);
    static void log(const char *module, const char *message, uint32_t value);
    static void log(const char *module, const char *message, int32_t value);
    static void log(const char *module, const char *message, const char *value);

    static void enableLogging(uint32_t speed = 115200);

private:
    static bool enabled; // Флаг для включения/выключения логирования
    static bool printPrefix(const char *module, const char *message);
    static void printSeparator();
};

#endif