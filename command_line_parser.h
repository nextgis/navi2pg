#ifndef NAVI2PG_COMMAND_LINE_PARSER_H
#define NAVI2PG_COMMAND_LINE_PARSER_H

#include <map>
#include <string>

#define VERSION "1.0.0"

namespace NAVI2PG
{
    namespace CommandLineKeys
    {
        const std::string PG_CONNECTION_STRING = "pg_connection_string";
        const std::string S57_DATASOURCE_NAME = "S57_datasource_name";
        const std::string RSC_FILENAME = "rsc filename";
    }

    typedef std::map<std::string, std::string> ValuesCollection;

    ValuesCollection CommandLineParse(int argc, char* argv[]);
}
#endif // COMMAND_LINE_PARSER_H
