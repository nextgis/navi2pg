#include "ogrsf_frmts.h"

#include "command_line_parser.h"
#include "navi2pg.h"
#include "logger.h"

int main(int nArgc, char ** papszArgv)
{   

    NAVI2PG::ValuesCollection valuesCollection = NAVI2PG::CommandLineParse(nArgc, papszArgv);

    const char  *pszS57DataSource =
            valuesCollection[NAVI2PG::CommandLineKeys::S57_DATASOURCE_NAME].c_str();
    const char  *pszPGConnectionString =
            valuesCollection[NAVI2PG::CommandLineKeys::PG_CONNECTION_STRING].c_str();

    NAVI2PG::Import(pszS57DataSource, pszPGConnectionString);

    return 0;
}

