#include "SerialLogger.h"

bool Logger::enabled = false; // ОБЯЗАТЕЛЬНО вне класса!

void Logger::log(const char *module, const char *message)
{
    if (printPrefix(module, message))
    {
        Serial.println();
    }
}

void Logger::log(const char *module, const char *message, uint8_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, int8_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, uint16_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, int16_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, uint32_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, int32_t value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

void Logger::log(const char *module, const char *message, const char *value)
{
    if (printPrefix(module, message))
    {
        printSeparator();
        Serial.println(value);
    }
}

bool Logger::printPrefix(const char *module, const char *message)
{
    if (!enabled)
        return false;

    Serial.print(module);
    Serial.print(F(" :> "));
    Serial.print(message);
    return true;
}

void Logger::printSeparator()
{
    Serial.print(F(" -> "));
}

void Logger::enableLogging(uint32_t speed)
{
    if (enabled) return;
    enabled = true;
    Serial.begin(speed); // Инициализация Serial при включении логирования
    Serial.println(F("Logging activated"));
    Serial.println(F("Start Setup"));
}
