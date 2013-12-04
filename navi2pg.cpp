#include <map>

#include "logger.h"
#include "navi2pg.h"

namespace
{
    using namespace NAVI2PG;

    Navi2PGConfig configurate(OGRDataSource* srcDataSource)
    {
        Navi2PGConfig configuration;

        NaviLayerConfuguration layerConf;

        FieldForCopy fieldForCopy;
        std::vector<FieldForCopy> fieldsForCopy;

        layerConf.hasSignature = false;

        layerConf.layerName = "beacon";
        layerConf.geomType = wkbPoint;

        fieldForCopy.fieldName = "COLOUR";
        fieldsForCopy.push_back(fieldForCopy);
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("BCNLAT"), fieldsForCopy) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("BOYLAT"), fieldsForCopy) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("BOYCAR"), fieldsForCopy) );
        layerConf.srcLayers.push_back( new NAVISRCLayerOBJNAMSign(srcDataSource->GetLayerByName("BCNSPP"), fieldsForCopy) );

        layerConf.srcLayers.push_back( new NAVISRCLayerOBJNAMSign(srcDataSource->GetLayerByName("BOYSAW")) );
        layerConf.srcLayers.push_back( new NAVISRCLayerLIGHTSSign(srcDataSource->GetLayerByName("LIGHTS")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        fieldsForCopy.clear();

        layerConf.layerName = "anchor_parking_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("ACHARE")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "anchor_parking_pt";
        layerConf.geomType = wkbPoint;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("ACHARE")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "building_ln";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DYKCON")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SLCONS")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "building_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("BUAARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DOCARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SLCONS")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "called_sea_parts";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SEAARE")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "coastline";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("COALNE")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "depths_area_ln";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DEPARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DEPCNT")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "depths_area_plg";
        layerConf.geomType = wkbPolygon;

        fieldForCopy.fieldName = "DRVAL2";
        fieldsForCopy.push_back(fieldForCopy);
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DEPARE"), fieldsForCopy) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DRGARE")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();
        fieldsForCopy.clear();

        layerConf.layerName = "dump_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DMPGRD")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "land_region_ln";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SLOTOP")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "land_region_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("LNDARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayerOBJNAMSign(srcDataSource->GetLayerByName("LNDRGN")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "land_region_pt";
        layerConf.geomType = wkbPoint;
        layerConf.hasSignature = true;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("LNDARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayerOBJNAMSign(srcDataSource->GetLayerByName("LNDRGN")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "landmark";
        layerConf.geomType = wkbPoint;
        layerConf.hasSignature = false;
        layerConf.srcLayers.push_back( new NAVISRCLayerOBJNAMSign(srcDataSource->GetLayerByName("LNDMRK")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "magnetic_declination";
        layerConf.geomType = wkbPoint;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("MAGVAR")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "mark";
        layerConf.geomType = wkbPoint;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("DAYMAR")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SOUNDG")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("TOPMAR")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "obstacles_ln";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("CBLSUB")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("FSHFAC")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "obstacles_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("OBSTRN")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "obstacles_pt";
        layerConf.geomType = wkbPoint;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("OBSTRN")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("SBDARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("UWTROC")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("WRECKS")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "pile_pt";
        layerConf.geomType = wkbPoint;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("PILPNT")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "rivers";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("RIVERS")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "route_ln";
        layerConf.geomType = wkbLineString;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("NAVLNE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("RECTRC")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "route_plg";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("CTNARE")) );
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("FAIRWY")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        layerConf.layerName = "vegetation";
        layerConf.geomType = wkbPolygon;
        layerConf.srcLayers.push_back( new NAVISRCLayer(srcDataSource->GetLayerByName("VEGATN")) );
        configuration.push_back(layerConf);

        layerConf.srcLayers.clear();

        return configuration;
    }
}

NAVI2PG::NAVILayer::NAVILayer(
            const CPLString& layerName,
            OGRwkbGeometryType geomType,
            std::vector<NAVISRCLayer*> srcLayers)
    : LayerName_(layerName),
      LayerGeometryType_(geomType),
      SrcLayers_(srcLayers)
{

}

void NAVI2PG::NAVILayer::CopyTo(OGRDataSource *poDstDatasource)
{
    if(SrcLayers_.size() == 0)
    {
        CPLString errMsg;
        errMsg.Printf("Warrning. %s layer not create. Source not found", LayerName_.c_str());
        LOG(errMsg);
        return;
    }

    if( !CheckSpatialReferences() )
    {
        //TODO set exception
        CPLString errMsg;
        errMsg.Printf("Error. %s layer creation error. Spatial references are not equal", LayerName_.c_str());
        LOG(errMsg);

        return;
    }

    OGRLayer *poLayer =
        poDstDatasource->CreateLayer( LayerName_.c_str(), SrcLayers_[0]->getOGRLayer()->GetSpatialRef(), LayerGeometryType_, NULL );

    for(size_t iLayer = 0; iLayer < SrcLayers_.size(); ++iLayer)
    {
        SrcLayers_[iLayer]->ImportFieldsDefns(poLayer);
    }

    for(size_t iLayer = 0; iLayer < SrcLayers_.size(); ++iLayer)
    {
        SrcLayers_[iLayer]->ImportFeaturesTo(poLayer);
    }

}
bool NAVI2PG::NAVILayer::CheckSpatialReferences()
{
    for(size_t iLayer = 1; iLayer < SrcLayers_.size(); ++iLayer)
    {
        OGRSpatialReference *sr1 =  SrcLayers_[iLayer-1]->getOGRLayer()->GetSpatialRef();
        OGRSpatialReference *sr2 =  SrcLayers_[iLayer]->getOGRLayer()->GetSpatialRef();

        if ( !sr1->IsSame(sr2))
            return false;
    }

    return true;
}

NAVI2PG::NAVISRCLayer::NAVISRCLayer(OGRLayer* srcOGRLayer, std::vector<FieldForCopy> fieldsToCopy)
    : poLayer(srcOGRLayer),
      FieldsToCopy_(fieldsToCopy)
{

}

NAVI2PG::NAVISRCLayer::NAVISRCLayer(OGRLayer* srcOGRLayer)
    : poLayer(srcOGRLayer)
{
}

OGRLayer* NAVI2PG::NAVISRCLayer::getOGRLayer()
{
    return poLayer;
}

void NAVI2PG::NAVISRCLayer::ImportFeaturesTo(OGRLayer* dstLayer)
{
    OGRFeature *poFeatureFrom;
    OGRFeature *poFeatureTo;

    while( (poFeatureFrom = poLayer->GetNextFeature()) != NULL )
    {
        poFeatureTo = OGRFeature::CreateFeature(dstLayer->GetLayerDefn());

        OGRGeometry *poGeometry = poFeatureFrom->GetGeometryRef();

        if( poGeometry == NULL
            || wkbFlatten(poGeometry->getGeometryType()) != dstLayer->GetLayerDefn()->GetGeomType() )
        {
            //TODO Debug Info
            continue;
        }

        poFeatureTo->SetGeometry(poGeometry);

        for(size_t iField = 0; iField< FieldsToCopy_.size(); ++iField)
        {
            int fieldIndex = poLayer->GetLayerDefn()->GetFieldIndex(FieldsToCopy_[iField].fieldName);
            OGRField* srcField = poFeatureFrom->GetRawFieldRef(fieldIndex);
            poFeatureTo->SetField(FieldsToCopy_[iField].fieldName, srcField);
        }

        poFeatureTo->SetField( "type",  poLayer->GetName());
        poFeatureTo->SetField( "name_en",  GetNameEnField(poFeatureFrom));
        poFeatureTo->SetField( "name_ru",  GetNameRuField(poFeatureFrom));

        dstLayer->CreateFeature(poFeatureTo);
    }
    
    OGRFeature::DestroyFeature( poFeatureFrom );
    OGRFeature::DestroyFeature( poFeatureTo );
}

void NAVI2PG::NAVISRCLayer::ImportFieldsDefns(OGRLayer* dstLayer)
{
    OGRFeatureDefn* dstOGRFeatrDefn = dstLayer->GetLayerDefn();

    for(size_t iField = 0; iField< FieldsToCopy_.size(); ++iField)
    {
        CPLString fieldName = FieldsToCopy_[iField].fieldName;

        if( dstOGRFeatrDefn->GetFieldIndex(fieldName.c_str()) != -1)
        {
            continue;
        }

        OGRFeatureDefn* ogrFeatrDefn = poLayer->GetLayerDefn();
        OGRFieldDefn* fieldDefn = ogrFeatrDefn->GetFieldDefn( ogrFeatrDefn->GetFieldIndex(fieldName.c_str()) );

        if( dstLayer->CreateField( fieldDefn ) != OGRERR_NONE )
        {
            //TODO Set exception
            LOG( "Creating field failed.\n" );
            return;
        }
    }

    if (dstOGRFeatrDefn->GetFieldIndex("type") == -1)
    {
        OGRFieldDefn oFieldType( "type", OFTString );
        oFieldType.SetWidth(32);
        if( dstLayer->CreateField( &oFieldType ) != OGRERR_NONE)
        {
            //TODO Set exception
            LOG( "Creating field \"type\" failed.\n" );
            return;
        }
    }

    if (dstOGRFeatrDefn->GetFieldIndex("name_en") == -1)
    {
        OGRFieldDefn oFieldNameEn( "name_en", OFTString );
        oFieldNameEn.SetWidth(32);
        if( dstLayer->CreateField( &oFieldNameEn ) != OGRERR_NONE)
        {
            //TODO Set exception
            LOG( "Creating field \"name_en\" failed.\n" );
            return;
        }
    }

    if (dstOGRFeatrDefn->GetFieldIndex("name_ru") == -1)
    {
        OGRFieldDefn oFieldNameRu( "name_ru", OFTString );
        oFieldNameRu.SetWidth(32);
        if( dstLayer->CreateField( &oFieldNameRu ) != OGRERR_NONE)
        {
            //TODO Set exception
            LOG( "Creating field \"name_ru\" failed.\n" );
            return;
        }
    }
}

CPLString NAVI2PG::NAVISRCLayer::GetNameEnField(OGRFeature *srcFeature)
{
    return CPLString();
}
CPLString NAVI2PG::NAVISRCLayer::GetNameRuField(OGRFeature *srcFeature)
{
    return CPLString();
}

CPLString NAVI2PG::NAVISRCLayerOBJNAMSign::GetNameEnField(OGRFeature *srcFeature)
{
    return CPLString(srcFeature->GetFieldAsString( "OBJNAM" ));
}
CPLString NAVI2PG::NAVISRCLayerOBJNAMSign::GetNameRuField(OGRFeature *srcFeature)
{
    return CPLString(srcFeature->GetFieldAsString( "OBJNAM" ));
}

CPLString NAVI2PG::NAVISRCLayerLIGHTSSign::GetNameEnField(OGRFeature *srcFeature)
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


    int litchrInt = srcFeature->GetFieldAsInteger( "LITCHR" );
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
        default:
        {
            litchrStr="";
            break;
        }
    }

    CPLString siggrpStr(srcFeature->GetFieldAsString( "SIGGRP" ) );

    int colourInt = srcFeature->GetFieldAsInteger( "COLOUR" );
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
        default:
        {
            colourStr = "";
        }
    }

    CPLString sigperStr(srcFeature->GetFieldAsString( "SIGPER" ) );
    if(sigperStr != "")
        sigperStr.Printf("%ss",sigperStr.c_str());

    CPLString heightStr(srcFeature->GetFieldAsString( "HEIGHT" ) );
    if(heightStr != "")
        heightStr.Printf("%sm",heightStr.c_str());

    CPLString valnmrStr(srcFeature->GetFieldAsString( "VALNMR" ) );
    if(valnmrStr != "")
        valnmrStr.Printf("%sM",valnmrStr.c_str());

    CPLString nameEn;
    nameEn.Printf("%s%s%s %s%s%s",litchrStr.c_str(), siggrpStr.c_str(), colourStr.c_str(), sigperStr.c_str(), heightStr.c_str(), valnmrStr.c_str());

    return nameEn;
}
CPLString NAVI2PG::NAVISRCLayerLIGHTSSign::GetNameRuField(OGRFeature *srcFeature)
{
    return GetNameEnField(srcFeature);
}

void NAVI2PG::Import(const char  *pszS57DataSource, const char  *pszPGConnectionString)
{

    CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_PRIMITIVES=ON,RETURN_LINKAGES=OFF,LNAM_REFS=ON,SPLIT_MULTIPOINT=ON,ADD_SOUNDG_DEPTH=ON,RECODE_BY_DSSI=ON");

    OGRRegisterAll();

    const char *pszSrcDriverName = "S57";
    const char *pszDstDriverName = "PostgreSQL";

    OGRSFDriver *poSrcDriver = NULL;
    OGRSFDriver *poDstDriver = NULL;

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
    OGRLayer *poLayer = poSrcDatasource->GetLayerByName("LNDRGN");
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
        std::cout <<   poFeature->GetFieldAsString( iField ) << "(" << poFDefn->GetFieldDefn(iField)->GetNameRef() << "), ";
    }
    std::cout << std::endl;
    */


    Navi2PGConfig config = configurate(poSrcDatasource);

    for(size_t iConfNode = 0; iConfNode < config.size(); ++iConfNode)
    {
        NAVI2PG::NAVILayer* naviLayer;

        naviLayer =
            new NAVI2PG::NAVILayer(
                config[iConfNode].layerName,
                config[iConfNode].geomType,
                config[iConfNode].srcLayers);

        naviLayer->CopyTo(poDstDatasource);
    }


    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}
