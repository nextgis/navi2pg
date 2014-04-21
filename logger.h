/******************************************************************************
 * Project:  navi2pg
 * Purpose:  tool to export s57 files into PstGIS and generate map file and mapnik xml
 * Author:   Alexandr Lisovenko, alexander.lisovenko@gmail.com
 ******************************************************************************
*   Copyright (C) 2013-2014 NextGIS
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
 
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

/**
* namespace NAVI2PG
* @brief Импортирование данных из файла формата s57 в БД PostgreSQL
*/
namespace NAVI2PG {

/**
* namespace LOGGER
* @brief Логгирование
*/
    namespace LOGGER {

        enum LOG_LEVEL
        {
            LOG_LEVEL_ERROR = 0,
            LOG_LEVEL_WARNING,
            LOG_LEVEL_INFO,
            LOG_LEVEL_DEBUG,
            LOG_LEVEL_DEBUG_1,
            LOG_LEVEL_DEBUG_2
        };

        void printLogMessage(LOG_LEVEL logLevel, const char* msg);

        static NAVI2PG::LOGGER::LOG_LEVEL LogLevel = NAVI2PG::LOGGER::LOG_LEVEL_INFO;

        void SetLogLevel(LOG_LEVEL logLevel);
    }
}

#define LOG(msg) std::cout << msg << std::endl;
#define LLOG(logLevel, msg) NAVI2PG::LOGGER::printLogMessage(logLevel, msg)


#endif // LOGGER_H
