#include "ogrsf_frmts.h"

#include "command_line_parser.h"
#include "navi2pg.h"
#include "logger.h"

class MapObject
{
public:
    const CPLString Name_;
public:
    MapObject(CPLString name):Name_(name){}
    void printSelf()
    {
        std::cout << "I am " << Name_ << " tag " << std::endl;
    }
};

void parseMapFile(std::ifstream& F)
{

}

/**
 * @brief Чтение параметров командной строки, инициализация процедуры импорта данных из s57 в PostgresSQL
 *
 * Вызов
 *  navi2pg [-h] [--help] [-v] [--version] <pg_connection_string> <S57_datasource_name> <mapconfig_template_filename>
 *
 * Описание
 *  Утилита производит импорт данных из файла формата S57 в БД PostgreSQL,
 *  для дальнейшего ипользования этих данных при построении карт средствами
 *  серверной геоинформационной системы MapServer.
 *
 *  Утилита использует в своей работе библиотеку GDAL\OGR
 *
 *  -h (или --help):
 *      Вывод справки на экран
 *
 *  -v (или --version):
 *      Вывод версии утилиты на экран
 *
 *  pg_connection_string:
 *      Источник данных PostgreSQL в формате поддерживаемом OGR
 *
 *  S57_datasource_name:
 *      Источник данных S57 в формате поддерживаемом OGR
 *
 *  mapconfig_template_filename
 *      Полный путь до файла-шаблона конфигурации MapServer
 *
 * Пример использования:
 *  1. Импорт данных из файла RU5NSKO0.000 в локальную БД с именем RU5NSKO0
 *
 *      navi2pg PG:"dbname='RU5NSKO0' user='postgres' password='tochange'" ..\S57\RU5NSKO0.000
 *
 *  2. Просмотр версии утилиты
 *
 *      navi2pg -v
 *
 */
int main(int nArgc, char ** papszArgv)
{   

    NAVI2PG::ValuesCollection valuesCollection = NAVI2PG::CommandLineParse(nArgc, papszArgv);

    const char  *pszS57DataSource =
            valuesCollection[NAVI2PG::CommandLineKeys::S57_DATASOURCE_NAME].c_str();
    const char  *pszPGConnectionString =
            valuesCollection[NAVI2PG::CommandLineKeys::PG_CONNECTION_STRING].c_str();
    const char  *mapConfigTemplateFilename =
            valuesCollection[NAVI2PG::CommandLineKeys::MAPCONFIG_TEMPLATE_FILENAME].c_str();

    NAVI2PG::Import(pszS57DataSource, pszPGConnectionString, mapConfigTemplateFilename);

    return 0;
}

