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
 
#include <map>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

#include "cpl_vsi.h"
#include "cpl_string.h"

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
         * конфигурация слоя beacon
         */
        layerName = "beacon";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNLAT");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNSHPSpecify());
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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNSPP");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSPP");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();


            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSAW");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYISD");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FOGSIG");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RTPBCN");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LIGHTS");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddLightsSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::SECTRSpecify());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddORIENTasExtFields());
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();

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
         * конфигурация слоя beacon
         */
        layerName = "beacon";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNLAT");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNSHPSpecify());
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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNSPP");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSPP");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();


            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSAW");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYISD");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FOGSIG");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RTPBCN");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LIGHTS");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddLightsSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::SECTRSpecify());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddORIENTasExtFields());
            layerWithCopyRules.FieldsNamesForCopy_.push_back("COLOUR");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя anchor_parking_plg
         */
        layerName = "anchor_parking_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя anchor_parking_pt
         */
        layerName = "anchor_parking_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHBRT");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("MORFAC");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя building_pt
         */
        layerName = "building_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BUISGL");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя building_ln
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
         * конфигурация слоя building_plg
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
         * конфигурация слоя called_sea_parts
         */
        layerName = "called_sea_parts";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SEAARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя coastline
         */
        layerName = "coastline";
        geomType = wkbLineString;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("COALNE");
            layerWithCopyRules.FieldsNamesForCopy_.push_back( "CATCOA");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя depths_area_ln
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
         * конфигурация слоя depths_area_plg
         */
        layerName = "depths_area_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DRGARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DEPARE");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL1");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL2");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя dump_plg
         */
        /*
        layerName = "dump_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DMPGRD");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();
        */

        /*
         * конфигурация слоя dump_pt
         */
        /*
        layerName = "dump_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DMPGRD");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();
        */

        /*
         * конфигурация слоя land_region_ln
         */
        layerName = "land_region_ln";
        geomType = wkbLineString;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SLOTOP");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя land_region_plg
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
         * конфигурация слоя land_region_pt
         */
        layerName = "land_region_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDELV");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDRGN");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя landmark
         */
        /*
        layerName = "landmark";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDMRK");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("CATLMK");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.AddNewFieldStrategies_.clear();
            layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();
        */

        /*
         * конфигурация слоя magnetic_declination
         */
        layerName = "magnetic_declination";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("MAGVAR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new AddVALMAGSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя mark
         */
        layerName = "mark";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DAYMAR");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TOPMAR");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("TOPSHP");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SOUNDG");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSoundgValues());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDMRK");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("CATLMK");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.AddNewFieldStrategies_.clear();
            layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя obstacles_ln
         */
        layerName = "obstacles_ln";
        geomType = wkbLineString;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CBLSUB");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FSHFAC");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OBSTRN");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddVALSOUasExtFields());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();


        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя obstacles_plg
         */
        layerName = "obstacles_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OBSTRN");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DMPGRD");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя obstacles_pt
         */
        layerName = "obstacles_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OBSTRN");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SBDARE");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddNATSURSignatures() );
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("UWTROC");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddVALSOUSignatures() );
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("WRECKS");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DMPGRD");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PILPNT");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя pile_pt
         */
        /*
        layerName = "pile_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PILPNT");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();
        */

        /*
         * конфигурация слоя rivers
         */
        layerName = "rivers";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RIVERS");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя route_pt
         */
        layerName = "route_pt";
        geomType = wkbPoint;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CTNARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PILBOP");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PRCARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RDOCAL");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();

        /*
         * конфигурация слоя tsslpt_pt
         */
        layerName = "tsslpt_pt";
        OGRLayer* TSSLPTLayer = poSrcDatasource->GetLayerByName("TSSLPT");

        configuration.push_back(new NAVI2PG::CreateTSSLPTStrategy(layerName, TSSLPTLayer));

        /*
         *  конфигурация слоя route_ln
         */
        layerName = "route_ln";
        geomType = wkbLineString;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("NAVLNE");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("CATNAV");
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RECTRC");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("TRAFIC");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("CATTRK");
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RCRTCL");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("TRAFIC");
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.FieldsNamesForCopy_.clear();
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("STSLNE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TSELNE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TSSBND");
            layersWithCopyRules.push_back(layerWithCopyRules);


        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя route_plg
         */
        layerName = "route_plg";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CTNARE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TSEZNE");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FAIRWY");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя vegetation
         */
        layerName = "vegetation";
        geomType = wkbPolygon;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("VEGATN");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя vegetation_pt
         */
        layerName = "vegetation_pt";
        geomType = wkbPoint;

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("WEDKLP");
        layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя labels
         */
        layerName = "labels";

        OGRLayer* isolatedNodeLayer = poSrcDatasource->GetLayerByName("IsolatedNode");
        OGRLayer* textsLayer = poSrcDatasource->GetLayerByName("$TEXTS");

        configuration.push_back(new NAVI2PG::CreateS57SignaturesStrategy(layerName, isolatedNodeLayer, textsLayer));

        /*
         * конфигурация слоя lights_sectors_conf
         */
        layerName = "lights_sectors";
        geomType = wkbLineString;

        OGRLayer* lightsLayer = poSrcDatasource->GetLayerByName("LIGHTS");

        configuration.push_back(new NAVI2PG::CreateLightsSectorsStrategy(layerName, geomType, lightsLayer));

        return configuration;
    }

}

std::vector<OGRFieldDefn*> NAVI2PG::ModifyTypeField::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;
    return result;
}

void NAVI2PG::BOYSHPSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int boyshp = srcFeature->GetFieldAsInteger( "BOYSHP" );

    CPLString typeValue;

    switch (boyshp)
    {
        case 1:
            typeValue = "konicheskii";
            break;
        case 4:
            typeValue = "stolb";
            break;
        case 5:
            typeValue = "veha";
            break;
        default:
            typeValue = "unknown";
            break;
    }

    CPLString oldValue = dstFeature->GetFieldAsString("type");
    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), typeValue.c_str() ) );
}

void NAVI2PG::BCNSHPSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int bcnshp = srcFeature->GetFieldAsInteger( "BCNSHP" );

    CPLString typeValue;

    switch (bcnshp)
    {
        case 3:
            typeValue = "mayak";
            break;
        case 5:
            typeValue = "konstr";
            break;
        case 4:
            typeValue = "vishka";
            break;
        default:
            typeValue = "unknown";
            break;
    }

    CPLString oldValue = dstFeature->GetFieldAsString("type");
    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), typeValue.c_str()) );
}

void NAVI2PG::SECTRSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString s1 = srcFeature->GetFieldAsString( "SECTR1" );
    CPLString s2 = srcFeature->GetFieldAsString( "SECTR2" );

    CPLString oldValue = dstFeature->GetFieldAsString("type");

    if (s1 != "" || s2 != "")
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_with_sector", oldValue.c_str()) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_without_sector", oldValue.c_str()) );
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

CPLString NAVI2PG::AddLightsSignatures::GetFirstPartOfSig(OGRFeature *srcFeature, bool withSIGGRP = true)
{
    CPLString siggrpStr;
    if(withSIGGRP == true)
        siggrpStr = srcFeature->GetFieldAsString( "SIGGRP" );
    else
        siggrpStr = "";

    int litchrInt = srcFeature->GetFieldAsInteger( "LITCHR" );
    CPLString litchrStr;
    switch(litchrInt)
    {
        case(2):
        {
            litchrStr.Printf("FI%s", siggrpStr.c_str());
            break;
        }
        case(3):
        {
            litchrStr.Printf("LFI%s", siggrpStr.c_str());
            break;
        }
        case(4):
        {
            litchrStr.Printf("Q%s", siggrpStr.c_str());
            break;
        }
        case(5):
        {
            litchrStr.Printf("VQ%s", siggrpStr.c_str());
            break;
        }
        case(7):
        {
            litchrStr.Printf("lco%s", siggrpStr.c_str());
            break;
        }
        case(8):
        {
            litchrStr.Printf("Oc%s", siggrpStr.c_str());
            break;
        }
        case(25):
        {
            char **siggrpTokens = CSLTokenizeString2( siggrpStr.c_str(), ")(", FALSE );
            int nTokens = CSLCount(siggrpTokens);
            if (nTokens < 2)
                LOG("Warning. litchrStr = Q+LFI, siggrp = (x)")
            litchrStr.Printf("Q(%s)+LFI(%s)", siggrpTokens[0], siggrpTokens[1]);

            CSLDestroy( siggrpTokens );
            break;
        }
        case(26):
        {
            char **siggrpTokens = CSLTokenizeString2( siggrpStr.c_str(), ")(", FALSE );
            int nTokens = CSLCount(siggrpTokens);
            if (nTokens < 2)
                LOG("Warning. litchrStr = VQ+LFI, siggrp = (x)")
            litchrStr.Printf("VQ(%s)+LFI(%s)", siggrpTokens[0], siggrpTokens[1]);
            CSLDestroy( siggrpTokens );
            break;
        }
        default:
        {
            litchrStr="";
            break;
        }
    }

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
        case(4):
        {
            colourStr.Printf("%s", "G");
            break;
        }
        default:
        {
            colourStr = "";
        }
    }

    litchrStr.Printf("%s%s", litchrStr.c_str(), colourStr.c_str());

    return litchrStr;
}

void NAVI2PG::AddLightsSignatures::Execute(OGRFeature *dstFeatures, OGRFeature *srcFeature)
{
    /*
     * Если у огня есть сектор подпись не нужна - поведение Панорамы
     */
    CPLString s1 = srcFeature->GetFieldAsString( "SECTR1" );
    CPLString s2 = srcFeature->GetFieldAsString( "SECTR2" );

    if (s1 != "" || s2 != "")
    {
        return;
    }

    /*
     *  CATLIT - категория тумана (список через запятую)
     *  в ГИС "Панорама" учитывается только последний из списка категорий
     */
    int catlit;
    char **catlitTokens = CSLTokenizeString2( srcFeature->GetFieldAsString( "CATLIT" ), ",", FALSE );
    int nTokens = CSLCount(catlitTokens);
    if (nTokens != 0)
        catlit = atoi(catlitTokens[nTokens-1]);
    else
        catlit = -1;


    CPLString signFirstPart;
    switch(catlit)
    {
        case(-1):
        {
            signFirstPart = GetFirstPartOfSig(srcFeature);
            break;
        }
        case(1):
        {
            signFirstPart = GetFirstPartOfSig(srcFeature);
            signFirstPart.Printf("Dir%s", signFirstPart.c_str());
            break;
        }
        case(6):
        {
            signFirstPart = GetFirstPartOfSig(srcFeature);
            signFirstPart.Printf("Aero%s",signFirstPart.c_str());
            break;
        }
        case(8):
        {
            return;
        }
        case(9):
        {
            return;
        }
        default:
        {
            signFirstPart = GetFirstPartOfSig(srcFeature, false);
            signFirstPart.Printf("%s",signFirstPart.c_str());
            break;
        }
    }

    CPLString sigperStr;
    int sigper = srcFeature->GetFieldAsInteger( "SIGPER" );
    sigperStr.Printf("%ds",sigper);

    CPLString heightStr(srcFeature->GetFieldAsString( "HEIGHT" ) );
    if(heightStr != "")
        heightStr.Printf("%sm",heightStr.c_str());

    CPLString valnmrStr(srcFeature->GetFieldAsString( "VALNMR" ) );
    if(valnmrStr != "")
        valnmrStr.Printf("%sM",valnmrStr.c_str());

    CPLString nameEn;
    nameEn.Printf("%s %s%s%s",signFirstPart.c_str(), sigperStr.c_str(), heightStr.c_str(), valnmrStr.c_str());

    dstFeatures->SetField( "name_en", nameEn.c_str() );
    dstFeatures->SetField( "name_ru", nameEn.c_str() );
}

void NAVI2PG::AddORIENTSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
   double orient = srcFeature->GetFieldAsInteger( "ORIENT" );

   dstFeature->SetField( "name_en", CPLString().Printf("%.2f deg", orient) );
   dstFeature->SetField( "name_ru", CPLString().Printf("%.2f град", orient) );

}

void NAVI2PG::AddORIENTasExtFields::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    if (CPLString(srcFeature->GetFieldAsString("ORIENT" )) != "")
    {
        double orient = srcFeature->GetFieldAsDouble("ORIENT" );
        dstFeature->SetField( "orient", 360 - orient);
    }
}

std::vector<OGRFieldDefn*> NAVI2PG::AddORIENTasExtFields::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;

    OGRFieldDefn* oFieldOrient = new OGRFieldDefn( "orient", OFTReal );
    oFieldOrient->SetWidth(32);
    result.push_back(oFieldOrient);
    return result;
}

void NAVI2PG::AddNATSURSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    /*
     *  NATSUR - материал поверхности (список через запятую)
     *  в ГИС "Панорама" учитывается только последний из списка материалов
     */
   char **natsurTokens = CSLTokenizeString2( srcFeature->GetFieldAsString( "NATSUR" ), ",", FALSE );
   int nTokens = CSLCount(natsurTokens);

   int natsur;
   if (nTokens != 0)
   {
       natsur = atoi(natsurTokens[nTokens-1]);
       dstFeature->SetField( "name_en", SurfaceMaterial_[natsur].c_str() );
       dstFeature->SetField( "name_ru", SurfaceMaterial_[natsur].c_str() );
   }

   CSLDestroy( natsurTokens );
}

void NAVI2PG::AddVALSOUSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
   double valsou = srcFeature->GetFieldAsDouble( "VALSOU" );

   dstFeature->SetField( "name_en", CPLString().Printf("%.1f", valsou) );
   dstFeature->SetField( "name_ru", CPLString().Printf("%.1f", valsou) );

}

void NAVI2PG::AddVALSOUasExtFields::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    double valsou = srcFeature->GetFieldAsDouble( "VALSOU" );
    dstFeature->SetField( "depth_whole", CPLString().Printf("%d", (int)valsou) );

    int depth_fractional = (int)( 10* (valsou - (int)valsou) );
    if (depth_fractional != 0)
        dstFeature->SetField( "depth_fractional", CPLString().Printf("%d",  depth_fractional) );

}

std::vector<OGRFieldDefn*> NAVI2PG::AddVALSOUasExtFields::GetOGRFieldDefn()
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

void NAVI2PG::AddSoundgValues::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    OGRPoint* point;
    double z;

    point = (OGRPoint*)srcFeature->GetGeometryRef();
    z = point->getZ();
    dstFeature->SetField( "depth_whole", CPLString().Printf("%d", (int)z) );


    point = (OGRPoint*)srcFeature->GetGeometryRef();
    z = point->getZ();

    dstFeature->SetField( "depth_fractional", CPLString().Printf("%d", (int)( 10* (z - (int)z + 0.05) ) ) );
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

void NAVI2PG::AddVALMAGSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    double valmag = srcFeature->GetFieldAsDouble( "VALMAG" );

    dstFeature->SetField( "name_en", CPLString().Printf("%.2f", valmag) );
    dstFeature->SetField( "name_ru", CPLString().Printf("%.2f", valmag) );
}

void NAVI2PG::CreateLayerStrategy::Create(OGRDataSource *poDstDatasource)
{
    char** papszLCO = NULL;
    papszLCO = CSLAddString(papszLCO, CPLString("OVERWRITE=yes").c_str() );

    if(LayerCreationPossibility() == false)
    {
        CPLString msg;
        msg.Printf("Warrning. Creation layer %s.", LayerName_.c_str());
        LOG(msg.c_str());

        Layer_ = poDstDatasource->CreateLayer(LayerName_.c_str(), NULL, GeomType_, papszLCO );

        return;
    }

    /*
     * Создание слоя в источнике данных OGR
     */
    Layer_ = poDstDatasource->CreateLayer( LayerName_.c_str(), GetSpatialRef(), GeomType_, papszLCO );

    /*
     * Добавление объектов в новый слой, определяется в классах-потомках.
     * Это может быть обычное копирование обыъектов с добавлением вспомогательных полей,
     * а может быть создание новых объектов на основе объектов из слоев источников.
     */
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

            if(AddTypeFieldFlag_)
            {
                poFeatureTo->SetField( "type", srcLayer->GetName() );
            }

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
        const unsigned int RadiusReductionCoef_ = 3;
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

            radius *= RadiusReductionCoef_;
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


void NAVI2PG::CreateTSSLPTStrategy::DoProcess()
{
    ModifyLayerDefnForAddNewFields();

    TSSLPTLayer_->ResetReading();

    OGRFeature* poFeatureFrom = NULL;
    while( (poFeatureFrom = TSSLPTLayer_->GetNextFeature()) != NULL )
    {

        OGRPolygon* poPolygon = (OGRPolygon*)poFeatureFrom->GetGeometryRef();
        OGRPoint* centriodPoint = new OGRPoint();

        poPolygon->Centroid(centriodPoint);

        OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());
        poFeatureTo->SetGeometry(centriodPoint);


        double orient = poFeatureFrom->GetFieldAsDouble("ORIENT");

        poFeatureTo->SetField( "angle_cw", orient );
        poFeatureTo->SetField( "angle_ccw", 360 - orient );

        Layer_->CreateFeature(poFeatureTo);
    }

}
void NAVI2PG::CreateTSSLPTStrategy::ModifyLayerDefnForAddNewFields()
{
    OGRFieldDefn* oFieldAngleCW = new OGRFieldDefn( "angle_cw", OFTReal );
    oFieldAngleCW->SetWidth(10);
    Layer_->CreateField(oFieldAngleCW);

    OGRFieldDefn* oFieldAngleCCW = new OGRFieldDefn( "angle_ccw", OFTReal );
    oFieldAngleCCW->SetWidth(10);
    Layer_->CreateField(oFieldAngleCCW);
}
OGRSpatialReference* NAVI2PG::CreateTSSLPTStrategy::GetSpatialRef()
{
    return TSSLPTLayer_->GetSpatialRef();
}
bool NAVI2PG::CreateTSSLPTStrategy::LayerCreationPossibility()
{
    if(TSSLPTLayer_ != NULL)
        return true;

    return false;
}

void NAVI2PG::CreateS57SignaturesStrategy::DoProcess()
{
    ModifyLayerDefnForAddNewFields();

    TextsLayer_->ResetReading();

    OGRFeatureDefn* defnTexts = TextsLayer_->GetLayerDefn();

    OGRFeature *poFeatureFromTexts;
    while( (poFeatureFromTexts = TextsLayer_->GetNextFeature()) != NULL )
    {
        CPLString lable = CPLRecode(poFeatureFromTexts->GetFieldAsString("$TXSTR"), "CP1251", CPL_ENC_UTF8);


        CPLString nameRCID = poFeatureFromTexts->GetFieldAsString("NAME_RCID");
        size_t begin = nameRCID.find(":");
        size_t end = nameRCID.find(")");
        nameRCID = nameRCID.substr(begin+1, (end - begin - 1));
        int externalRCID = atoi(nameRCID.c_str());

        IsolatedNodeLayer_->ResetReading();

        OGRFeature *poFeatureFromIsolatedNode;
        while( (poFeatureFromIsolatedNode = IsolatedNodeLayer_->GetNextFeature()) != NULL )
        {
            int rcid =poFeatureFromIsolatedNode->GetFieldAsInteger("RCID");

            if (externalRCID == rcid)
            {
                OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());
                poFeatureTo->SetGeometry(poFeatureFromIsolatedNode->GetGeometryRef());
                poFeatureTo->SetField("lable",  lable.c_str());
                Layer_->CreateFeature(poFeatureTo);

                OGRFeature::DestroyFeature( poFeatureTo );
            }

            OGRFeature::DestroyFeature(poFeatureFromIsolatedNode);
        }

        OGRFeature::DestroyFeature(poFeatureFromTexts);
    }
}
void NAVI2PG::CreateS57SignaturesStrategy::ModifyLayerDefnForAddNewFields()
{
    OGRFieldDefn oFieldAngleCW( "lable", OFTString );
    oFieldAngleCW.SetWidth(32);
    Layer_->CreateField(&oFieldAngleCW);
}
OGRSpatialReference* NAVI2PG::CreateS57SignaturesStrategy::GetSpatialRef()
{
    return IsolatedNodeLayer_->GetSpatialRef();
}
bool NAVI2PG::CreateS57SignaturesStrategy::LayerCreationPossibility()
{
    if(IsolatedNodeLayer_ != NULL && TextsLayer_ != NULL)
        return true;

    return false;
}


void NAVI2PG::Import(const char  *pszS57DataSource, const char  *pszPGConnectionString, const char  *mapConfigTemplateFilename)
{
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

    /*
     *  Установка переменных среды для корректного чтения файлов s57 драйвером s57 OGR
     */
    CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_PRIMITIVES=ON,RETURN_LINKAGES=ON,LNAM_REFS=ON,ADD_SOUNDG_DEPTH=ON,SPLIT_MULTIPOINT=ON,RECODE_BY_DSSI=ON");

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
     *  Конфигурация
     */
    std::vector<CreateLayerStrategy*>layersCreators = configurate(poSrcDatasource);
    //std::vector<CreateLayerStrategy*>layersCreators = configurateTest(poSrcDatasource);

    /*
     *  Импорт данных в БД
     */

    for(size_t i = 0; i < layersCreators.size(); ++i)
    {
        CreateLayerStrategy* layersCreator = layersCreators[i];
        layersCreator->Create(poDstDatasource);
    }

    /*
     *  Cоздание файла конфигурации для mapserver
     */
    OGRLayer* layer = poSrcDatasource->GetLayer(0);
    OGREnvelope envelope;
    OGRErr err = layer->GetExtent(&envelope);

    OGRSpatialReference poSRSfrom;
    poSRSfrom.importFromEPSG(4326);

    OGRSpatialReference poSRSto;
    poSRSto.importFromEPSG(3857);

    OGRPoint minExtentPoint(envelope.MinX, envelope.MinY);
    minExtentPoint.assignSpatialReference(&poSRSfrom);
    minExtentPoint.transformTo(&poSRSto);

    OGRPoint maxExtentPoint(envelope.MaxX, envelope.MaxY);
    maxExtentPoint.assignSpatialReference(&poSRSfrom);
    maxExtentPoint.transformTo(&poSRSto);

    OGREnvelope newExtent;
    newExtent.MinX = minExtentPoint.getX();
    newExtent.MinY = minExtentPoint.getY();
    newExtent.MaxX = maxExtentPoint.getX();
    newExtent.MaxY = maxExtentPoint.getY();

    CopyMapConfigFile(mapConfigTemplateFilename, CPLResetExtension(pszS57DataSource, "map"), newExtent);

    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}

void NAVI2PG::CopyMapConfigFile(
        const char  *mapConfigTemplateFilename,
        const char  *mapConfigFilename,
        OGREnvelope newExtent)
{
    std::string S57_FILENAME = "[S57_file_name]";
    std::string S57_EXTENT = "[S57_extent]";

    std::ifstream input;
    input.open(mapConfigTemplateFilename, std::ios::in);

    std::ofstream output;
    output.open(mapConfigFilename, std::ios::out);

    std::string line;

    while (!input.eof())
    {
        std::getline(input,line);

        if(line.find (S57_FILENAME) != std::string::npos)
        {
            std::string newLine;
            newLine.assign(line, 0, line.find(S57_FILENAME));
            newLine.append(CPLGetBasename(mapConfigFilename));
            newLine.append(line.substr(line.find(S57_FILENAME)+ S57_FILENAME.size(), line.size() - line.find(S57_FILENAME) + S57_FILENAME.size() ) );

            output << newLine << "\n";
        }
        else if(line.find (S57_EXTENT) != std::string::npos)
        {
            std::string newLine;
            newLine.assign(line, 0, line.find(S57_EXTENT));
            newLine.append(CPLString().Printf("%e %e %e %e", newExtent.MinX, newExtent.MinY, newExtent.MaxX, newExtent.MaxY).c_str()) ;
            newLine.append(line.substr(line.find(S57_EXTENT) + S57_EXTENT.size(), line.size() - line.find(S57_EXTENT)+ S57_EXTENT.size()) );

            output << newLine << "\n";
        }
        else
        {
            output << line << "\n";
        }
    }
}
