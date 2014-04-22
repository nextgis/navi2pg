#include "logger.h"

void NAVI2PG::LOGGER::printLogMessage(LOG_LEVEL logLevel, const char* msg)
{
    if(logLevel > LogLevel)
        return;



    switch (logLevel)
    {
    case LOG_LEVEL_ERROR:
        std::cout << "ERROR: ";
        break;
    case LOG_LEVEL_WARNING:
        std::cout << "WARNING: ";
        break;
    case LOG_LEVEL_INFO:
        std::cout << "INFO: ";
        break;
    case LOG_LEVEL_DEBUG:
        std::cout << "DEBUG: ";
        break;
    case LOG_LEVEL_DEBUG_1:
        std::cout << "DEBUG_1: ";
        break;
    case LOG_LEVEL_DEBUG_2:
        std::cout << "DEBUG_2: ";
        break;
    default:
        break;
    }

    std::cout << msg << std::endl;
}

void NAVI2PG::LOGGER::SetLogLevel(LOG_LEVEL logLevel)
{
    LogLevel = logLevel;
}
