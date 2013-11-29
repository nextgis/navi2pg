#include<iostream>

#include "ogr_p.h"

#include "command_line_parser.h"

namespace
{
    void Usage()
    {
        std::cout << "Usage: navi2ogr [-h] [--help] [-v] [--version] ";
        std::cout << NAVI2PG::CommandLineKeys::PG_CONNECTION_STRING << " ";
        std::cout << NAVI2PG::CommandLineKeys::S57_DATASOURCE_NAME;
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

        else if( EQUAL(argv[iArg],"--rsc") )
        {
            values[CommandLineKeys::RSC_FILENAME] = std::string(argv[++iArg]);
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
    }

    return values;
}
