#include "ogr_api.h"
#include "ogrsf_frmts.h"

#include "logger.h"
#include "navi2pg.h"

void NAVI2PG::Import(const char  *pszS57DataSource, const char  *pszPGConnectionString)
{
    CPLString msg;

    msg.Printf("pszS57DataSource: %s", pszS57DataSource);
    LOG(msg);

    msg.Printf("pszPGConnectionString: %s", pszPGConnectionString);
    LOG(msg);

    OGRRegisterAll();

    const char *pszSrcDriverName = "S57";
    const char *pszDstDriverName = "PostgreSQL";

    OGRSFDriver *poSrcDriver = NULL;
    OGRSFDriver *poDstDriver = NULL;

    OGRRegisterAll();

    poSrcDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
                pszSrcDriverName );

    if( poSrcDriver == NULL )
    {
        CPLString msg;
        msg.Printf("%s driver not available.", pszSrcDriverName);
        LOG(msg);
        exit( 1 );
    }

    OGRDataSource *poSrcDatasource = NULL;

    CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_PRIMITIVES=ON,RETURN_LINKAGES=ON,LNAM_REFS=ON,SPLIT_MULTIPOINT=ON,ADD_SOUNDG_DEPTH=ON,RECODE_BY_DSSI=ON");
    poSrcDatasource = poSrcDriver->Open(pszS57DataSource);

    if( poSrcDatasource == NULL )
    {
        CPLString msg;
        msg.Printf("Open S57 failed.");
        LOG(msg);
        exit( 1 );
    }

    poDstDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
                pszDstDriverName );

    if( poDstDriver == NULL )
    {
        CPLString msg;
        msg.Printf("%s driver not available.", pszDstDriverName);
        LOG(msg);
        exit( 1 );
    }

    OGRDataSource *poDstDatasource = NULL;

    poDstDatasource = poDstDriver->Open(pszPGConnectionString);


    if( poDstDatasource == NULL )
    {
        CPLString msg;
        msg.Printf("Creation of table in PG Database failed.");
        LOG(msg);
        exit( 1 );
    }

    CPLString newLayerName;
    for(int layerIndex = 0; layerIndex < poSrcDatasource->GetLayerCount(); layerIndex++)
    {
        OGRLayer *l = poSrcDatasource->GetLayer(layerIndex);
        poDstDatasource->CopyLayer(l, newLayerName.Printf("S57_%s",l->GetName()).c_str());
    }


    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}
