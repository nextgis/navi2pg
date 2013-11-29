#include <vector>

#include "logger.h"
#include "navi2pg.h"

namespace
{
    void addStandartFields(OGRLayer* layer)
    {
        OGRFieldDefn oFieldType( "type", OFTString );
        oFieldType.SetWidth(32);
        OGRFieldDefn oFieldNameEn( "name_en", OFTString );
        oFieldType.SetWidth(32);
        OGRFieldDefn oFieldNameRu( "name_ru", OFTString );
        oFieldType.SetWidth(32);

        if( layer->CreateField( &oFieldType ) != OGRERR_NONE ||
                layer->CreateField( &oFieldNameEn ) != OGRERR_NONE ||
                layer->CreateField( &oFieldNameRu ) != OGRERR_NONE)
        {
            LOG( "Creating field failed.\n" );
            return;
        }
    }
    bool checkSpatialReferences(std::vector<NAVI2PG::NAVILayer*> layers)
    {

        for(size_t iLayer = 1; iLayer < layers.size(); ++iLayer)
        {
            if ( !layers[iLayer-1]->equalSpatialReferences(*layers[iLayer]) )
            {
                return false;
            }
        }

        return true;
    }

    void createBeaconLayer(OGRDataSource *poSrcDatasource, OGRDataSource *poDstDatasource)
    {
        const CPLString newLayerName("beacon");
        OGRwkbGeometryType newLayerGeometry = wkbPoint;

        OGRLayer * ogrLayerBCNLAT = poSrcDatasource->GetLayerByName("BCNLAT");

        NAVI2PG::NAVILayer * layerBCNLAT =
                new NAVI2PG::NAVILayer(ogrLayerBCNLAT);
        NAVI2PG::NAVILayer * layerBCNSPP =
                new NAVI2PG::NAVILayer(poSrcDatasource->GetLayerByName("BCNSPP"));
        NAVI2PG::NAVILayer * layerBOYCAR =
                new NAVI2PG::NAVILayer(poSrcDatasource->GetLayerByName("BOYCAR"));
        NAVI2PG::NAVILayer * layerBOYLAT =
                new NAVI2PG::NAVILayer(poSrcDatasource->GetLayerByName("BOYLAT"));
        NAVI2PG::NAVILayer * layerBOYSAW =
                new NAVI2PG::NAVILayer(poSrcDatasource->GetLayerByName("BOYSAW"));
        NAVI2PG::NAVILayer * layerLIGHTS =
                new NAVI2PG::LightsNAVILayer(poSrcDatasource->GetLayerByName("LIGHTS"));

        std::vector<NAVI2PG::NAVILayer*> layers;
        layers.push_back(layerBCNLAT);
        layers.push_back(layerBCNSPP);
        layers.push_back(layerBOYCAR);
        layers.push_back(layerBOYLAT);
        layers.push_back(layerBOYSAW);
        layers.push_back(layerLIGHTS);

        if( !checkSpatialReferences(layers) )
        {
            LOG("Error. \"beacon\" layer creation error. Spatial references are not equal");
            return;
        }

        OGRLayer *beaconLayer =
            poDstDatasource->CreateLayer( newLayerName.c_str(), ogrLayerBCNLAT->GetSpatialRef(), newLayerGeometry, NULL );

        addStandartFields(beaconLayer);

        for(size_t iLayer = 0; iLayer < layers.size(); ++iLayer)
        {
            layers[iLayer]->copyFeaturesTo(beaconLayer);
        }
    }
    void createAnchorParkingPlg(OGRDataSource *poSrcDatasource, OGRDataSource *poDstDatasource)
    {
        const CPLString newLayerName("anchor_parking_plg");
        OGRwkbGeometryType newLayerGeometry = wkbPolygon;

        OGRLayer * ogrLayerACHARE = poSrcDatasource->GetLayerByName("ACHARE");

        NAVI2PG::NAVILayer * layerACHARE =
                new NAVI2PG::NAVILayer(ogrLayerACHARE);

        OGRLayer *anchorParkingPlgLayer =
            poDstDatasource->CreateLayer( newLayerName.c_str(), ogrLayerACHARE->GetSpatialRef(), newLayerGeometry, NULL );

        addStandartFields(anchorParkingPlgLayer);

        layerACHARE->copyFeaturesTo(anchorParkingPlgLayer);
    }
    void createAnchorParkingPt(OGRDataSource *poSrcDatasource, OGRDataSource *poDstDatasource)
    {
        const CPLString newLayerName("anchor_parking_pt");
        OGRwkbGeometryType newLayerGeometry = wkbPoint;

        OGRLayer * ogrLayerACHARE = poSrcDatasource->GetLayerByName("ACHARE");

        NAVI2PG::NAVILayer * layerACHARE =
                new NAVI2PG::NAVILayer(ogrLayerACHARE);

        OGRLayer *anchorParkingPtLayer =
            poDstDatasource->CreateLayer( newLayerName.c_str(), ogrLayerACHARE->GetSpatialRef(), newLayerGeometry, NULL );

        addStandartFields(anchorParkingPtLayer);

        layerACHARE->copyFeaturesTo(anchorParkingPtLayer);
    }

}


NAVI2PG::NAVILayer::NAVILayer(OGRLayer *layer):poLayer(layer)
{

}

void NAVI2PG::NAVILayer::copyFeaturesTo(OGRLayer *layerTo)
{

    poLayer->ResetReading();
    layerTo->ResetReading();

    OGRFeature *poFeatureFrom;
    OGRFeature *poFeatureTo;

    while( (poFeatureFrom = poLayer->GetNextFeature()) != NULL )
    {
        poFeatureTo = OGRFeature::CreateFeature(layerTo->GetLayerDefn());

        OGRGeometry *poGeometry = poFeatureFrom->GetGeometryRef();

        if( poGeometry == NULL
            || wkbFlatten(poGeometry->getGeometryType()) != layerTo->GetLayerDefn()->GetGeomType() )
        {
            LOG("Warrning. Feature hav bad GeometryType");
            continue;
        }

        poFeatureTo->SetGeometry(poGeometry);

        doCreateFields(poFeatureFrom, poFeatureTo);

        layerTo->CreateFeature(poFeatureTo);

        OGRFeature::DestroyFeature( poFeatureFrom );
        OGRFeature::DestroyFeature( poFeatureTo );
    }
}

void NAVI2PG::NAVILayer::doCreateFields(OGRFeature *featureFrom, OGRFeature *featureTo)
{
    doCreateTypeField(featureFrom, featureTo);
    doCreateNameEnField(featureFrom, featureTo);
    doCreateNameRuField(featureFrom, featureTo);
}

void NAVI2PG::NAVILayer::doCreateTypeField(OGRFeature *featureFrom, OGRFeature *featureTo)
{
    featureTo->SetField( "type",  poLayer->GetName());
}

void NAVI2PG::NAVILayer::doCreateNameEnField(OGRFeature *featureFrom, OGRFeature *featureTo)
{

}

void NAVI2PG::NAVILayer::doCreateNameRuField(OGRFeature *featureFrom, OGRFeature *featureTo)
{

}

bool NAVI2PG::NAVILayer::equalSpatialReferences(const NAVILayer& layer)
{

    OGRSpatialReference *sr1 =  poLayer->GetSpatialRef();
    OGRSpatialReference *sr2 =  layer.poLayer->GetSpatialRef();

    if ( !sr1->IsSame(sr2))
    {
        return false;
    }

    return true;
}

void NAVI2PG::LightsNAVILayer::doCreateNameEnField(OGRFeature *featureFrom, OGRFeature *featureTo)
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
}

void NAVI2PG::LightsNAVILayer::doCreateNameRuField(OGRFeature *featureFrom, OGRFeature *featureTo)
{
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


    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );

    createBeaconLayer(poSrcDatasource, poDstDatasource);
    createAnchorParkingPlg(poSrcDatasource, poDstDatasource);
    createAnchorParkingPt(poSrcDatasource, poDstDatasource);

}
