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
#ifndef NAVI2PG_COMMAND_LINE_PARSER_H
#define NAVI2PG_COMMAND_LINE_PARSER_H

#include <map>
#include <string>

#define VERSION "1.0.0"

namespace NAVI2PG
{
/**
 * @brief Параметры командной строки
 */
    namespace CommandLineKeys
    {
        const std::string PG_CONNECTION_STRING = "pg_connection_string";
        const std::string S57_DATASOURCE_NAME = "S57_datasource_name";

        const std::string MAPCONFIG_TEMPLATE_FILENAME = "mapconfig_template_filename";
    }

    typedef std::map<std::string, std::string> ValuesCollection;

/**
 * @brief Чтение параметров командной строки
 *
 * @param argc - количество параметров
 * @param argv - массив параметров
 *
 * @return значения параметров запуска приложения
 */
    ValuesCollection CommandLineParse(int argc, char* argv[]);
}
#endif // COMMAND_LINE_PARSER_H
