#include <map>

#include "logger.h"
#include "navi2pg.h"
#include "feature_creation_rules.h"

namespace
{
    using namespace NAVI2PG;

    std::vector<CreateLayerStrategy*> configurateTest(OGRDataSource *poSrcDatasource)
    {
        std::vector<CreateLayerStrategy*> configuration;

        LayersWithCopyRules layersWithCopyRules;
        LayerWithCopyRules layerWithCopyRules;

        CPLString layerName;
        OGRwkbGeometryType geomType;

        /*
         * lights_sectors_conf layer configuration
         */
        layerName = "lights_sectors_conf";
        geomType = wkbLineString;

        OGRLayer* lightsLayer = poSrcDatasource->GetLayerByName("LIGHTS");

        configuration.push_back(new NAVI2PG::CreateLightsSectorsStrategy("lights_sectors", geomType, lightsLayer));

        return configuration;
    }

    std::vector<CreateLayerStrategy*> configurate(OGRDataSource *poSrcDatasource)
    {
        std::vector<CreateLayerStrategy*> configuration;

        LayersWithCopyRules layersWithCopyRules;
        LayerWithCopyRules layerWithCopyRules;

        CPLString layerName;
        OGRwkbGeometryType geomType;


        /*
         * beacon layer configuration
         */
        layerName = "beacon";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNLAT");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYLAT");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYCAR");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNSPP");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSAW");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LIGHTS");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddLightsSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();
        layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * anchor_parking_plg layer configuration
         */
        layerName = "anchor_parking_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * anchor_parking_pt layer configuration
         */
        layerName = "anchor_parking_pt";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHARE");
        layersWithCopyRules.push_back(layerWithCopyRules);


        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * building_ln layer configuration
         */
        layerName = "building_ln";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DYKCON");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SLCONS");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * building_plg layer configuration
         */
        layerName = "building_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BUAARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DOCARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SLCONS");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * called_sea_parts layer configuration
         */
        layerName = "called_sea_parts";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SEAARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * coastline layer configuration
         */
        layerName = "coastline";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("COALNE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * depths_area_ln layer configuration
         */
        layerName = "depths_area_ln";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DEPARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DEPCNT");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("VALDCO");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * depths_area_plg layer configuration
         */
        layerName = "depths_area_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DRGARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DEPARE");
        layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL2");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * dump_plg layer configuration
         */
        layerName = "dump_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DMPGRD");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * land_region_ln layer configuration
         */
        layerName = "land_region_ln";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SLOTOP");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * land_region_plg layer configuration
         */
        layerName = "land_region_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDRGN");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * land_region_pt layer configuration
         */
        layerName = "land_region_pt";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDRGN");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * landmark layer configuration
         */
        layerName = "landmark";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDMRK");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * magnetic_declination layer configuration
         */
        layerName = "magnetic_declination";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("MAGVAR");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * mark layer configuration
         */
        layerName = "mark";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DAYMAR");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TOPMAR");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SOUNDG");
        layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSoundgValues());
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * obstacles_ln layer configuration
         */
        layerName = "obstacles_ln";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CBLSUB");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FSHFAC");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * obstacles_plg layer configuration
         */
        layerName = "obstacles_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OBSTRN");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * obstacles_pt layer configuration
         */
        layerName = "obstacles_pt";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OBSTRN");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SBDARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("UWTROC");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("WRECKS");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * pile_pt layer configuration
         */
        layerName = "pile_pt";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PILPNT");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * rivers layer configuration
         */
        layerName = "rivers";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RIVERS");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * route_ln layer configuration
         */
        layerName = "route_ln";
        geomType = wkbLineString;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("NAVLNE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RECTRC");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * route_plg layer configuration
         */
        layerName = "route_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CTNARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CTNARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * vegetation layer configuration
         */
        layerName = "vegetation";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("VEGATN");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * lights_sectors_conf layer configuration
         */
        layerName = "lights_sectors_conf";
        geomType = wkbLineString;

        OGRLayer* lightsLayer = poSrcDatasource->GetLayerByName("LIGHTS");

        configuration.push_back(new NAVI2PG::CreateLightsSectorsStrategy("lights_sectors", geomType, lightsLayer));

        return configuration;
    }

}

void NAVI2PG::AddSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    dstFeature->SetField( "name_en", srcFeature->GetFieldAsString( "OBJNAM" ) );
    dstFeature->SetField( "name_ru", srcFeature->GetFieldAsString( "NOBJNM" ) );
}

std::vector<OGRFieldDefn*> NAVI2PG::AddSignatures::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;

    OGRFieldDefn* oFieldNameEn = new OGRFieldDefn( "name_en", OFTString );
    oFieldNameEn->SetWidth(32);
    result.push_back(oFieldNameEn);

    OGRFieldDefn* oFieldNameRu = new OGRFieldDefn( "name_ru", OFTString );
    oFieldNameRu->SetWidth(32);
    result.push_back(oFieldNameRu);

    return result;
}

void NAVI2PG::AddLightsSignatures::Execute(OGRFeature *dstFeatures, OGRFeature *srcFeature)
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

    dstFeatures->SetField( "name_en", nameEn.c_str() );
    dstFeatures->SetField( "name_ru", nameEn.c_str() );
}

void NAVI2PG::AddSoundgValues::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    OGRPoint* point;
    double z;

    point = (OGRPoint*)srcFeature->GetGeometryRef();
    z = point->getZ();
    dstFeature->SetField( "depth_whole", CPLString().Printf("%d", (int)z) );


    point = (OGRPoint*)srcFeature->GetGeometryRef();
    z = point->getZ();

    dstFeature->SetField( "depth_fractional", CPLString().Printf("%d", (int)( 10* (z - (int)z) ) ) );
}

std::vector<OGRFieldDefn*> NAVI2PG::AddSoundgValues::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;

    OGRFieldDefn* oFieldNameEn = new OGRFieldDefn( "depth_whole", OFTString );
    oFieldNameEn->SetWidth(32);
    result.push_back(oFieldNameEn);

    OGRFieldDefn* oFieldNameRu = new OGRFieldDefn( "depth_fractional", OFTString );
    oFieldNameRu->SetWidth(32);
    result.push_back(oFieldNameRu);

    return result;
}

void NAVI2PG::CreateLayerStrategy::Create(OGRDataSource *poDstDatasource)
{
    if(LayerCreationPossibility() == false)
    {
        CPLString msg;
        msg.Printf("Error. Layer %s cannot be created.", LayerName_.c_str());
        LOG(msg.c_str());

        return;
    }

    char** papszLCO = NULL;
    papszLCO = CSLAddString(papszLCO, CPLString("OVERWRITE=yes").c_str() );

    Layer_ = poDstDatasource->CreateLayer( LayerName_.c_str(), GetSpatialRef(), GeomType_, papszLCO );

    DoProcess();
}

void NAVI2PG::CopyFeaturesStrategy::DoProcess()
{

    if(AddTypeFieldFlag_)
    {
        OGRFieldDefn* oFieldType = new OGRFieldDefn( "type", OFTString );
        oFieldType->SetWidth(32);

        if( Layer_->CreateField(oFieldType) != OGRERR_NONE )
        {
            //TODO Set exception
            LOG( "Creating field 'type' failed.\n" );
        }
    }

    ModifyLayerDefnForCopyFields();
    ModifyLayerDefnForAddNewFields();

    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        OGRLayer* srcLayer = SrcLayers_[iSrcLayer].SrcLayer_;
        srcLayer->ResetReading();

        std::vector<CPLString> fieldsNamesForCopy = SrcLayers_[iSrcLayer].FieldsNamesForCopy_;
        std::vector<AddNewFieldStrategy*> strategies = SrcLayers_[iSrcLayer].AddNewFieldStrategies_;

        OGRFeature *poFeatureFrom = NULL;
        while( (poFeatureFrom = srcLayer->GetNextFeature()) != NULL )
        {
            OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());
            OGRGeometry *poGeometry = poFeatureFrom->GetGeometryRef();

            if( poGeometry == NULL ||
                    wkbFlatten(poGeometry->getGeometryType()) != Layer_->GetLayerDefn()->GetGeomType() )
            {
                //TODO Debug Info
                continue;
            }

            poFeatureTo->SetGeometry(poGeometry);

            for(size_t iFieldName = 0; iFieldName< fieldsNamesForCopy.size(); ++iFieldName)
            {
                CPLString fieldName = fieldsNamesForCopy[iFieldName];
                int fieldIndex = srcLayer->GetLayerDefn()->GetFieldIndex(fieldName.c_str());
                OGRField* srcField = poFeatureFrom->GetRawFieldRef(fieldIndex);

                poFeatureTo->SetField(fieldName.c_str(), srcField);
            }

            for(size_t iStrategy = 0; iStrategy < strategies.size(); ++iStrategy)
            {
                AddNewFieldStrategy* strategy = strategies[iStrategy];
                strategy->Execute(poFeatureTo, poFeatureFrom);
            }

            if(AddTypeFieldFlag_)
            {
                poFeatureTo->SetField( "type", srcLayer->GetName() );
            }

            Layer_->CreateFeature(poFeatureTo);
        }

    }


}
void NAVI2PG::CopyFeaturesStrategy::ModifyLayerDefnForCopyFields()
{
    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        OGRLayer* srcLayer = SrcLayers_[iSrcLayer].SrcLayer_;
        std::vector<CPLString> fieldsNamesForCopy = SrcLayers_[iSrcLayer].FieldsNamesForCopy_;

        for(size_t iFieldName = 0; iFieldName< fieldsNamesForCopy.size(); ++iFieldName)
        {
            CPLString fieldName = fieldsNamesForCopy[iFieldName];

            OGRFeatureDefn* ogrFeatrDefn = srcLayer->GetLayerDefn();
            OGRFieldDefn* fieldDefn = ogrFeatrDefn->GetFieldDefn( ogrFeatrDefn->GetFieldIndex(fieldName.c_str()) );

            if( Layer_->GetLayerDefn()->GetFieldIndex(fieldDefn->GetNameRef()) != -1)
            {
                continue;
            }

            if( Layer_->CreateField(fieldDefn) != OGRERR_NONE )
            {
                //TODO Set exception
                LOG( "Creating field failed.\n" );
                continue;
            }
        }
    }
}
void NAVI2PG::CopyFeaturesStrategy::ModifyLayerDefnForAddNewFields()
{
    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        std::vector<AddNewFieldStrategy*> strategies = SrcLayers_[iSrcLayer].AddNewFieldStrategies_;

        for(size_t iStrategy = 0; iStrategy < strategies.size(); ++iStrategy)
        {
            AddNewFieldStrategy* strategy = strategies[iStrategy];

            std::vector<OGRFieldDefn*> fieldsDefns = strategy->GetOGRFieldDefn();

            for(size_t iFieldDefn = 0; iFieldDefn < fieldsDefns.size(); ++iFieldDefn)
            {
                OGRFieldDefn* fieldDefn = fieldsDefns[iFieldDefn];

                if( Layer_->GetLayerDefn()->GetFieldIndex(fieldDefn->GetNameRef()) != -1)
                {
                    continue;
                }

                if( Layer_->CreateField(fieldDefn) != OGRERR_NONE )
                {
                    //TODO Set exception
                    LOG( "Creating field failed.\n" );
                    return;
                }
            }
        }
    }
}
OGRSpatialReference* NAVI2PG::CopyFeaturesStrategy::GetSpatialRef()
{
    OGRLayer* poLayer = SrcLayers_[0].SrcLayer_;
    return poLayer->GetSpatialRef();
}
bool NAVI2PG::CopyFeaturesStrategy::LayerCreationPossibility()
{
    if(SrcLayers_.size() == 0)
        return false;
    return true;
}

void NAVI2PG::CreateLightsSectorsStrategy::DoProcess()
{
    ModifyLayerDefnForAddNewFields();

    LightsLayer_->ResetReading();

    OGRFeature* poFeatureFrom = NULL;
    while( (poFeatureFrom = LightsLayer_->GetNextFeature()) != NULL )
    {
        const double DegreesToPoint_ = 5;
        const unsigned int RadiusStrat_ = 1000;
        const unsigned int RadiusReductionCoef_ = 2;
        const size_t RadiusCount_ = 3;

        OGRPoint* poPoint = (OGRPoint*)poFeatureFrom->GetGeometryRef();
        double valnmr = poFeatureFrom->GetFieldAsDouble("VALNMR");
        double sectr1 = poFeatureFrom->GetFieldAsDouble("SECTR1");
        double sectr2 = poFeatureFrom->GetFieldAsDouble("SECTR2");


        if(sectr1==0 && sectr2==0)
        {
            continue;
        }

        OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());

        OGRSpatialReference* dstSpRef = poPoint->getSpatialReference();

        OGRSpatialReference poSRS;
        poSRS.importFromEPSG(3857);
        poPoint->transformTo(&poSRS);

        OGRPoint pt1;
        pt1.assignSpatialReference(&poSRS);
        OGRPoint pt2;
        pt2.assignSpatialReference(&poSRS);
        OGRPoint pt3;
        pt3.assignSpatialReference(&poSRS);


        pt1.setX( poPoint->getX() - std::sin(sectr1*TO_RADIANS) * valnmr * 1852 );
        pt1.setY( poPoint->getY() - std::cos(sectr1*TO_RADIANS) * valnmr * 1852 );
        pt1.transformTo(dstSpRef);

        pt2.setX( poPoint->getX() );
        pt2.setY( poPoint->getY() );
        pt2.transformTo(dstSpRef);

        pt3.setX( poPoint->getX() - std::sin(sectr2*TO_RADIANS) * valnmr * 1852 );
        pt3.setY( poPoint->getY() - std::cos(sectr2*TO_RADIANS) * valnmr * 1852 );
        pt3.transformTo(dstSpRef);

        OGRLineString* poLS = new OGRLineString();
        poLS->addPoint( &pt1 );
        poLS->addPoint( &pt2 );
        poLS->addPoint( &pt3 );

        poFeatureTo->SetGeometry( poLS );
        poFeatureTo->SetField( "type", "rays" );

        Layer_->CreateFeature(poFeatureTo);

        double delta = sectr2 - sectr1;
        double angleFrom;
        double angleTo;

        if(delta >= 0)
        {
            angleFrom = sectr1;
            angleTo = sectr2;
        }
        else
        {
            angleFrom = sectr1;
            angleTo = 360 + sectr2;
        }

        int coloure = poFeatureFrom->GetFieldAsDouble("COLOUR");

        double radius = RadiusStrat_;
        for(size_t iRadius = 0; iRadius < RadiusCount_; ++iRadius)
        {
            OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());
            poFeatureTo->SetField( "type", "sector" );
            poFeatureTo->SetField( "radius", radius );
            poFeatureTo->SetField( "colour", coloure );

            OGRLineString* sectorLine = new OGRLineString();

            double angle = angleFrom;
            while(angle < angleTo)
            {
                OGRPoint pt;
                pt.assignSpatialReference(&poSRS);
                pt.setX( poPoint->getX() - std::sin(angle * TO_RADIANS) * (radius ) );
                pt.setY( poPoint->getY() - std::cos(angle * TO_RADIANS) * (radius ) );
                pt.transformTo(dstSpRef);

                angle = angle + DegreesToPoint_;

                sectorLine->addPoint(&pt);
            }

            OGRPoint pt;
            pt.assignSpatialReference(&poSRS);
            pt.setX( poPoint->getX() - std::sin(angleTo * TO_RADIANS) * (radius ) );
            pt.setY( poPoint->getY() - std::cos(angleTo * TO_RADIANS) * (radius ) );
            pt.transformTo(dstSpRef);
            sectorLine->addPoint(&pt);

            poFeatureTo->SetGeometry( sectorLine );

            Layer_->CreateFeature(poFeatureTo);

            radius /= RadiusReductionCoef_;
        }
    }
}
void NAVI2PG::CreateLightsSectorsStrategy::ModifyLayerDefnForAddNewFields()
{
    OGRFieldDefn* oFieldRadius = new OGRFieldDefn( "radius", OFTInteger );
    oFieldRadius->SetWidth(10);
    Layer_->CreateField(oFieldRadius);

    OGRFieldDefn* oFieldType = new OGRFieldDefn( "type", OFTString );
    oFieldType->SetWidth(32);
    Layer_->CreateField(oFieldType);

    OGRFieldDefn* oFieldColoure = new OGRFieldDefn( "colour", OFTInteger );
    oFieldColoure->SetWidth(32);
    Layer_->CreateField(oFieldColoure);
}
OGRSpatialReference* NAVI2PG::CreateLightsSectorsStrategy::GetSpatialRef()
{
    return LightsLayer_->GetSpatialRef();
}
bool NAVI2PG::CreateLightsSectorsStrategy::LayerCreationPossibility()
{
    if(LightsLayer_ != NULL)
        return true;

    return false;
}

void NAVI2PG::Import(const char  *pszS57DataSource, const char  *pszPGConnectionString)
{

    CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_PRIMITIVES=ON,RETURN_LINKAGES=ON,LNAM_REFS=ON,SPLIT_MULTIPOINT=ON,ADD_SOUNDG_DEPTH=ON,RECODE_BY_DSSI=ON");

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

    std::vector<CreateLayerStrategy*>layersCreators = configurate(poSrcDatasource);
    //std::vector<CreateLayerStrategy*>layersCreators = configurateTest(poSrcDatasource);

    for(size_t i = 0; i < layersCreators.size(); ++i)
    {
        CreateLayerStrategy* layersCreator = layersCreators[i];
        layersCreator->Create(poDstDatasource);
    }



    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}
