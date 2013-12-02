#include <map>

#include "logger.h"
#include "navi2pg.h"

namespace
{
    typedef struct
    {
        CPLString layerName;
        std::vector<CPLString> srcLayers;
        OGRwkbGeometryType geomType;

    }NaviLayerConfuguration;

    typedef std::vector<NaviLayerConfuguration> Navi2PGConfig;

    Navi2PGConfig configurate()
    {
        Navi2PGConfig configuration;

        NaviLayerConfuguration layerConf;

        layerConf.srcLayers.push_back("BCNLAT");
        layerConf.srcLayers.push_back("BCNSPP");
        layerConf.srcLayers.push_back("BOYCAR");
        layerConf.srcLayers.push_back("BOYLAT");
        layerConf.srcLayers.push_back("BOYSAW");
        layerConf.srcLayers.push_back("LIGHTS");
        layerConf.geomType = wkbPoint;
        layerConf.layerName = "beacon";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("ACHARE");
        layerConf.geomType = wkbPolygon;
        layerConf.layerName = "anchor_parking_plg";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("ACHARE");
        layerConf.geomType = wkbPoint;
        layerConf.layerName = "anchor_parking_pt";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("DYKCON");
        layerConf.srcLayers.push_back("SLCONS");
        layerConf.geomType = wkbLineString;
        layerConf.layerName = "building_ln";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("BUAARE");
        layerConf.srcLayers.push_back("DOCARE");
        layerConf.srcLayers.push_back("SLCONS");
        layerConf.geomType = wkbPolygon;
        layerConf.layerName = "building_plg";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("SEAARE");
        layerConf.geomType = wkbPolygon;
        layerConf.layerName = "called_sea_parts";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("COALNE");
        layerConf.geomType = wkbLineString;
        layerConf.layerName = "coastline";
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        layerConf.srcLayers.push_back("DEPARE");
        layerConf.srcLayers.push_back("DEPCNT");
        layerConf.geomType = wkbLineString;
        layerConf.layerName = "depths_area_ln";
        configuration.push_back(layerConf);


        return configuration;
    }
}

NAVI2PG::NAVILayer::NAVILayer(
            const CPLString& layerName,
            OGRwkbGeometryType geomType,
            OGRDataSource *poSrcDatasource,
            std::vector<CPLString> srcLayerNames)
    : LayerName_(layerName),
      LayerGeometryType_(geomType)
{
    for(size_t iLayerName = 0; iLayerName < srcLayerNames.size(); ++iLayerName)
    {
        //TODO Сheck for NULL layer
        SrcLayers_.push_back(poSrcDatasource->GetLayerByName(srcLayerNames[iLayerName]));
    }
}

void NAVI2PG::NAVILayer::CopyTo(OGRDataSource *poDstDatasource)
{
    if( !checkSpatialReferences() )
    {
        //TODO set exception
        CPLString errMsg;
        errMsg.Printf("Error. %s layer creation error. Spatial references are not equal", LayerName_.c_str());
        LOG(errMsg);

        return;
    }

    OGRLayer *poLayer =
        poDstDatasource->CreateLayer( LayerName_.c_str(), SrcLayers_[0]->GetSpatialRef(), LayerGeometryType_, NULL );

    InitFields(poLayer);

    for(size_t iLayer = 0; iLayer < SrcLayers_.size(); ++iLayer)
    {
        OGRLayer *poSrcLayer = SrcLayers_[iLayer];

        poSrcLayer->ResetReading();

        OGRFeature *poFeatureFrom;
        OGRFeature *poFeatureTo;

        while( (poFeatureFrom = poSrcLayer->GetNextFeature()) != NULL )
        {
            poFeatureTo = OGRFeature::CreateFeature(poLayer->GetLayerDefn());

            OGRGeometry *poGeometry = poFeatureFrom->GetGeometryRef();

            if( poGeometry == NULL
                || wkbFlatten(poGeometry->getGeometryType()) != poLayer->GetLayerDefn()->GetGeomType() )
            {
                LOG("Warrning. Feature hav bad GeometryType");
                continue;
            }

            poFeatureTo->SetGeometry(poGeometry);

            SetFields(poSrcLayer, poFeatureTo);

            poLayer->CreateFeature(poFeatureTo);

            OGRFeature::DestroyFeature( poFeatureFrom );
            OGRFeature::DestroyFeature( poFeatureTo );
        }
    }
}

bool NAVI2PG::NAVILayer::checkSpatialReferences()
{
    for(size_t iLayer = 1; iLayer < SrcLayers_.size(); ++iLayer)
    {
        OGRSpatialReference *sr1 =  SrcLayers_[iLayer-1]->GetSpatialRef();
        OGRSpatialReference *sr2 =  SrcLayers_[iLayer]->GetSpatialRef();

        if ( !sr1->IsSame(sr2))
            return false;
    }

    return true;
}


NAVI2PG::NAVILayerSimple::NAVILayerSimple(
        const CPLString &layerName,
        OGRwkbGeometryType geomType,
        OGRDataSource *poSrcDatasource,
        std::vector<CPLString> srcLayerNames)
    : NAVILayer(layerName, geomType, poSrcDatasource, srcLayerNames)
{

}

void NAVI2PG::NAVILayerSimple::InitFields(OGRLayer *poLayer)
{
    OGRFieldDefn oFieldType( "type", OFTString );
    oFieldType.SetWidth(32);
    OGRFieldDefn oFieldNameEn( "name_en", OFTString );
    oFieldType.SetWidth(32);
    OGRFieldDefn oFieldNameRu( "name_ru", OFTString );
    oFieldType.SetWidth(32);

    if( poLayer->CreateField( &oFieldType ) != OGRERR_NONE ||
            poLayer->CreateField( &oFieldNameEn ) != OGRERR_NONE ||
            poLayer->CreateField( &oFieldNameRu ) != OGRERR_NONE)
    {
        //TODO Set exception
        LOG( "Creating field failed.\n" );
        return;
    }
}

void NAVI2PG::NAVILayerSimple::SetFields(OGRLayer* layerFrom, OGRFeature* featureTo)
{
    SetTypeField(layerFrom, featureTo);
    SetNameEnField(layerFrom, featureTo);
    SetNameRuField(layerFrom, featureTo);
}

void NAVI2PG::NAVILayerSimple::SetTypeField(OGRLayer* layerFrom, OGRFeature* featureTo)
{
    featureTo->SetField( "type",  layerFrom->GetName());
}

void NAVI2PG::NAVILayerSimple::SetNameRuField(OGRLayer* layerFrom, OGRFeature* featureTo)
{

}

void NAVI2PG::NAVILayerSimple::SetNameEnField(OGRLayer* layerFrom, OGRFeature* featureTo)
{
    /*
    concat (
        CASE
            WHEN  "LITCHR" =  '2' THEN 'FI'
            WHEN  "LITCHR" =  '3' THEN 'LFI'
            WHEN  "LITCHR" =  '4' THEN 'Q'
            WHEN  "LITCHR" =  '7' THEN 'lso'
            WHEN  "LITCHR" =  '8' THEN 'OcR'
            WHEN  "LITCHR" =  '25' THEN 'Q+LFI'
            ELSE 'NA'
        END,
        "SIGGRP" ,
        CASE
            WHEN  "COLOUR" =  '1' THEN 'W'
            WHEN  "COLOUR" =  '3' THEN 'R'
            ELSE 'G'
        END,
        ' ',
        CASE
            WHEN "SIGPER"  IS NULL THEN ''
            ELSE concat("SIGPER" ,'s')
        END,
        CASE
            WHEN "HEIGHT"  IS NULL THEN ''
            ELSE concat("HEIGHT" ,'m')
        END,
        CASE
            WHEN "VALNMR"  IS NULL THEN ''
            ELSE concat("VALNMR" ,'M')
        END
    )
     */
    /*
    OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
    int litchrInt = featureFrom->GetFieldAsInteger( poFDefn->GetFieldIndex("LITCHR") );
    CPLString litchrStr;
    switch(litchrInt)
    {
        case(2):
        {
            litchrStr.Printf("%s", "FI");
            break;
        }
        case(3):
        {
            litchrStr.Printf("%s", "LFI");
            break;
        }
        case(4):
        {
            litchrStr.Printf("%s", "Q");
            break;
        }
        case(7):
        {
            litchrStr.Printf("%s", "lso");
            break;
        }
        case(8):
        {
            litchrStr.Printf("%s", "OcR");
            break;
        }
        case(25):
        {
            litchrStr.Printf("%s", "Q+LFI");
            break;
        }
    }

    CPLString siggrpStr(featureFrom->GetFieldAsString( poFDefn->GetFieldIndex("SIGGRP") ) );

    int colourInt = featureFrom->GetFieldAsInteger( poFDefn->GetFieldIndex("COLOUR") );
    CPLString colourStr;
    switch(colourInt)
    {
        case(1):
        {
            colourStr.Printf("%s", "W");
            break;
        }
        case(3):
        {
            colourStr.Printf("%s", "R");
            break;
        }
    }

    //int sigperInt = featureFrom->GetFieldAsInteger( poFDefn->GetFieldIndex("SIGPER") );

    CPLString nameEn;
    nameEn.Printf("%s%s%s ",litchrStr.c_str(), siggrpStr.c_str(), colourStr.c_str());

    featureTo->SetField( "name_en",  nameEn.c_str());
    featureTo->SetField( "name_ru",  nameEn.c_str());
    */
}

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


    CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_PRIMITIVES=OFF,RETURN_LINKAGES=OFF,LNAM_REFS=ON,SPLIT_MULTIPOINT=ON,ADD_SOUNDG_DEPTH=OFF,RECODE_BY_DSSI=OFF");

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


    /*
     *  For tests
     */
    /*
    OGRLayer *poLayer = poSrcDatasource->GetLayerByName("LIGHTS");
    OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();

    OGRFeature *poFeature = poLayer->GetNextFeature();

    for( int iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
    {
        std::cout <<   poFeature->GetFieldAsInteger(iField ) << "(" << poFDefn->GetFieldDefn(iField)->GetNameRef() << "), ";
    }
    std::cout << std::endl;

    poFeature = poLayer->GetNextFeature();

    for( int iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
    {
        std::cout <<   poFeature->GetFieldAsInteger( iField ) << "(" << poFDefn->GetFieldDefn(iField)->GetNameRef() << "), ";
    }
    std::cout << std::endl;
    */


    Navi2PGConfig config = configurate();


    for(size_t iConfNode = 0; iConfNode < config.size(); ++iConfNode)
    {

        NAVI2PG::NAVILayerSimple naviLayer(
                    config[iConfNode].layerName,
                    config[iConfNode].geomType,
                    poSrcDatasource,
                    config[iConfNode].srcLayers);

        naviLayer.CopyTo(poDstDatasource);
    }

    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}
