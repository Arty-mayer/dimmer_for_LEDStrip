#include "SerialLogger.h"

bool Logger::enabled = false; // ОБЯЗАТЕЛЬНО вне класса!

void Logger::log(const char *message, bool newLine = true)
{
    if (Logger::enabled)
    {
        if (newLine)
        {
            Serial.println();
        }
        else
        {
            Serial.print(message);
        }
    }
}

void Logger::enableLogging(uint32_t speed)
{
    enabled = true;
    Serial.begin(speed); // Инициализация Serial при включении логирования
    Serial.println("Logging activated");
    Serial.println("Start Setup");
}
