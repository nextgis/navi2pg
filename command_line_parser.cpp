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
#include<iostream>

#include "ogr_p.h"
#include "cpl_vsi.h"

#include "command_line_parser.h"

namespace
{
    void Usage()
    {
        std::cout << "Usage: navi2ogr [-h] [--help] [-v] [--version] [--sign_cp1251] ";
        std::cout << "[--create_schema]" << " ";
        std::cout << "[--schema <schema_name>]" << " ";
        std::cout << NAVI2PG::CommandLineKeys::PG_CONNECTION_STRING << " ";
        std::cout << NAVI2PG::CommandLineKeys::S57_DATASOURCE_NAME << " ";
        std::cout << NAVI2PG::CommandLineKeys::MAPSERVER_CONFIG_TEMPLATE_FILENAME << " ";
        std::cout << NAVI2PG::CommandLineKeys::MAPNIK_CONFIG_TEMPLATE_FILENAME << " ";
        std::cout << NAVI2PG::CommandLineKeys::MAPNIK_PYSCRIPT_TEMPLATE_FILENAME;
        std::cout << std::endl;

        exit( 1 );
    }
}

NAVI2PG::ValuesCollection NAVI2PG::CommandLineParse(int argc, char* argv[])
{
    ValuesCollection values;

    if( argc < 1 )
    {
        Usage();
        exit( -argc );
    }

    if( argc == 1 )
    {
        Usage();
    }

    for( int iArg = 1; iArg < argc; iArg++ )
    {
        if( EQUAL(argv[iArg], "--version") ||
                EQUAL(argv[iArg], "-v"))
        {
            std::cout << "navi2pg version: " << VERSION << std::endl;
            exit(0);
        }

        else if( EQUAL(argv[iArg],"--help") ||
                 EQUAL(argv[iArg],"-h"))
        {
            Usage();
        }

        else if( EQUAL(argv[iArg], "--sign_cp1251" ) )
        {
            CPLSetConfigOption("NEED_CONVERT_SIGN_TO_CP1251","TRUE");
        }

        else if( EQUAL(argv[iArg], "--create_schema" ) )
        {
            CPLSetConfigOption(CommandLineKeys::CREATE_SCHEME_FLAG.c_str(), "TRUE");
        }

        else if( EQUAL(argv[iArg], "--schema" ) )
        {
            CPLSetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), argv[++iArg]);
        }

        else if( argv[iArg][0] == '-' )
        {
            std::cout << "Unknown option name: " << argv[iArg] << std::endl;
            Usage();
        }
        else if( values.find(CommandLineKeys::PG_CONNECTION_STRING) == values.end())
        {
            values[CommandLineKeys::PG_CONNECTION_STRING] = std::string(argv[iArg]);

        }
        else if( values.find(CommandLineKeys::S57_DATASOURCE_NAME) == values.end() )
        {
            values[CommandLineKeys::S57_DATASOURCE_NAME] = std::string(argv[iArg]);
        }
        else if( CPLGetConfigOption(CommandLineKeys::MAPSERVER_CONFIG_TEMPLATE_FILENAME.c_str(), NULL) == NULL)
        {
            CPLSetConfigOption(CommandLineKeys::MAPSERVER_CONFIG_TEMPLATE_FILENAME.c_str(), argv[iArg]);
        }
        else if( CPLGetConfigOption(CommandLineKeys::MAPNIK_CONFIG_TEMPLATE_FILENAME.c_str(), NULL) == NULL)
        {
            CPLSetConfigOption(CommandLineKeys::MAPNIK_CONFIG_TEMPLATE_FILENAME.c_str(), argv[iArg]);
        }
        else if( CPLGetConfigOption(CommandLineKeys::MAPNIK_PYSCRIPT_TEMPLATE_FILENAME.c_str(), NULL) == NULL)
        {
            CPLSetConfigOption(CommandLineKeys::MAPNIK_PYSCRIPT_TEMPLATE_FILENAME.c_str(), argv[iArg]);
        }
    }

    return values;
}
