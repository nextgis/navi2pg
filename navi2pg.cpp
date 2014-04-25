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
#include <string>
#include <algorithm>

#include "cpl_vsi.h"
#include "cpl_string.h"

#include "logger.h"
#include "navi2pg.h"
#include "command_line_parser.h"


namespace
{
    std::string readFromDBConnectString(const std::string& connectionString, const std::string& paramName)
    {
        int pos = connectionString.find(paramName);

        if(pos == std::string::npos)
            return std::string();

        int paramValueStart = connectionString.find("=",pos)+1;

        int i = 0;
        while(connectionString[paramValueStart+i] == ' ')
        {
            LOG(connectionString[paramValueStart+i]);
            i++;
            paramValueStart++;
        }

        int paramValueEnd = connectionString.find(" ",paramValueStart);

        std::string paramValue(connectionString, paramValueStart, paramValueEnd - paramValueStart);
        paramValue.erase(std::remove(paramValue.begin(), paramValue.end(), '\''), paramValue.end());

        return paramValue;
    }

    using namespace NAVI2PG;

    std::vector<CreateLayerStrategy*> configurateTest(OGRDataSource *poSrcDatasource)
    {
        std::vector<CreateLayerStrategy*> configuration;

        LayersWithCopyRules layersWithCopyRules;
        LayerWithCopyRules layerWithCopyRules;

        CPLString layerName;
        OGRwkbGeometryType geomType;


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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNLATSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BCNSPP");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BCNSPPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYLAT");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYCAR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSPP");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYSAW");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BOYISD");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::BOYSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FOGSIG");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RTPBCN");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LITVES");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LIGHTS");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddLightsSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddORIENTasExtFields());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::SECTRSpecify());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::ORIENTPresenceSpecify());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::COLOURSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
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

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("GATCON");
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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::CATSLCSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("GATCON");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя building_plg
         */
        layerName = "building_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BUAARE");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();


            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DOCARE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SLCONS");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BRIDGE");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RUNWAY");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("BUISGL");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("OFSPLF");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddVALDCOSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


        /*
         * конфигурация слоя depths_area_plg
         */
        layerName = "depths_area_plg";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DRGARE");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL1");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL2");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("DEPARE");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL1");
            layerWithCopyRules.FieldsNamesForCopy_.push_back("DRVAL2");
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.FieldsNamesForCopy_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDELV");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDRGN");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


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
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TOPMAR");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::TOPSHPSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SOUNDG");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSoundgValues());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LNDMRK");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddSignatures());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::CONVISSpecify());
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::CATLMKSpecify());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

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

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PIPSOL");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("CBLOHD");
            layerWithCopyRules.AddNewFieldStrategies_.push_back(new NAVI2PG::AddVERCLRSignatures());
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

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

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("FSHGRD");
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

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SNDWAV");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("MARCUL");
            layersWithCopyRules.push_back(layerWithCopyRules);

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("WATTUR");
            layersWithCopyRules.push_back(layerWithCopyRules);

        configuration.push_back(new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules));
        layersWithCopyRules.clear();


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
         * конфигурация слоя lakes
         */
        layerName = "lakes";
        geomType = wkbPolygon;

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("LAKARE");
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

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SISTAT");
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
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::CATNAVSpecify() );
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RECTRC");
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::TRAFICSpecify() );
            layersWithCopyRules.push_back(layerWithCopyRules);
            layerWithCopyRules.AddNewFieldStrategies_.clear();

            layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("RCRTCL");
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::AddORIENTSignatures() );
            layerWithCopyRules.AddNewFieldStrategies_.push_back( new NAVI2PG::TRAFICSpecify() );
            layersWithCopyRules.push_back(layerWithCopyRules);
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

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TSSRON");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("TSSCRS");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("SUBTLN");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("PILBOP");
        layersWithCopyRules.push_back(layerWithCopyRules);

        layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ISTZNE");
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

        /*
         * конфигурация слоя system_lines
         */
        layerName = "system_lines";

        OGRLayer* edgeLayer = poSrcDatasource->GetLayerByName("Edge");
        OGRLayer* linesLayer = poSrcDatasource->GetLayerByName("$LINES");
        OGRLayer* connectedNodeLayer = poSrcDatasource->GetLayerByName("ConnectedNode");

        configuration.push_back(new NAVI2PG::CreateSystemLinesStrategy(layerName, edgeLayer, linesLayer, connectedNodeLayer));

        return configuration;
    }

}

std::vector<OGRFieldDefn*> NAVI2PG::ModifyTypeField::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;
    return result;
}

void NAVI2PG::BOYSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int boyshp = srcFeature->GetFieldAsInteger( "BOYSHP" );

    CPLString typeValue;

    switch (boyshp)
    {
        case 1:
            typeValue = "konicheskii";
            break;
        case 2:
            typeValue = "cilindricheskii";
            break;
        case 3:
            typeValue = "sphericheskii";
            break;
        case 4:
            typeValue = "stolb";
            break;
        case 5:
            typeValue = "veha";
            break;
        case 7:
            typeValue = "superbui";
            break;
        default:
            typeValue = "unknown";
            break;
    }

    CPLString oldValue = dstFeature->GetFieldAsString("type");
    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), typeValue.c_str() ) );
}

void NAVI2PG::BCNLATSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int bcnshp = srcFeature->GetFieldAsInteger( "BCNSHP" );

    CPLString typeValue;

    switch (bcnshp)
    {
        case 1:
            typeValue = "veha";
            break;
        case 2:
            typeValue = "derevo2";
            break;
        case 3:
            typeValue = "mayak";
            break;
        case 5:
            typeValue = "konstr";
            break;;
        case 7:
            typeValue = "konstr";
            break;
        default:
            typeValue = "unknown";
            break;
    }

    CPLString oldValue = dstFeature->GetFieldAsString("type");
    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), typeValue.c_str()) );
}

void NAVI2PG::BCNSPPSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int bcnshp = srcFeature->GetFieldAsInteger( "BCNSHP" );
    int catspm = srcFeature->GetFieldAsInteger( "CATSPM" );

    CPLString typeValue;

    if (bcnshp == 3 && catspm == 18)
    {
        typeValue = "vnimanie";
    }
    else if (bcnshp == 1)
    {
        typeValue = "veha";
    }
    else if (bcnshp == 5)
    {
        typeValue = "konstr";
    }
    else if (bcnshp == 3)
    {
        typeValue = "mayak";
    }
    else if (bcnshp == 4)
    {
        typeValue = "vishka";
    }
    else
    {
        typeValue = "unknown";
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

void NAVI2PG::COLOURSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

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
        case(6):
        {
            colourStr.Printf("%s", "Y");
            break;
        }
        default:
        {
            colourStr.Printf("%s", "Unknown");
        }
    }

    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), colourStr.c_str()) );
}

void NAVI2PG::ORIENTPresenceSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    CPLString orientStr = srcFeature->GetFieldAsString("ORIENT");
    if (orientStr != "")
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_orient", oldValue.c_str() ) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_not_orient", oldValue.c_str() ) );
    }
}

void NAVI2PG::TOPSHPSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    int topshp = srcFeature->GetFieldAsInteger("TOPSHP");
    CPLString topshpStr;
    if (topshp == 3)
    {
        topshpStr.assign("shar");
    }
    else if (topshp == 4)
    {
        topshpStr.assign("2_shara");
    }
    else if (topshp == 10)
    {
        topshpStr.assign("2_kon_versh_vmeste");
    }
    else if (topshp == 13)
    {
        topshpStr.assign("2_kon_versh_vverh");
    }
    else if (topshp == 11)
    {
        topshpStr.assign("2_kon_versh_vroz");
    }
    else if (topshp == 14)
    {
        topshpStr.assign("2_kon_versh_vniz");
    }
    else if (topshp == 5)
    {
        topshpStr.assign("cilindr");
    }
    else if (topshp == 5)
    {
        topshpStr.assign("cilindr");
    }
    else if (topshp == 1)
    {
        topshpStr.assign("kon_versh_vverh");
    }
    else
    {
        topshpStr.assign("unknown");
    }

    dstFeature->SetField( "type", CPLString().Printf("%s_%s", oldValue.c_str(), topshpStr.c_str() ) );
}
void NAVI2PG::CONVISSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    int convis = srcFeature->GetFieldAsInteger("CONVIS");
    if (convis == 1)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_visible", oldValue.c_str() ) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_unknown", oldValue.c_str() ) );
    }
}
void NAVI2PG::CATLMKSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    CPLString catlmk_str(srcFeature->GetFieldAsString("CATLMK"));
    char **siggrpTokens = CSLTokenizeString2( catlmk_str.c_str(), ",", FALSE );
    int nTokens = CSLCount(siggrpTokens);
    int catlmk = -1;
    if (nTokens > 0)
    {
        std::stringstream(siggrpTokens[nTokens - 1]) >> catlmk;
    }

    if (catlmk == 17)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_tower", oldValue.c_str() ) );
    }
    else if (catlmk == 3)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_pipe", oldValue.c_str() ) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_unknown", oldValue.c_str() ) );
    }
}
void NAVI2PG::CATNAVSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    int catnav = srcFeature->GetFieldAsInteger("CATNAV");
    if (catnav == 1)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_limiting", oldValue.c_str() ) );
    }
    else if (catnav == 3)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_recomend_path", oldValue.c_str() ) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_unknown", oldValue.c_str() ) );
    }
}
void NAVI2PG::TRAFICSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    int trafic = srcFeature->GetFieldAsInteger("TRAFIC");
    if (trafic == 4)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_bothway", oldValue.c_str() ) );
    }
    else if (trafic == 0)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_noteset", oldValue.c_str() ) );
    }
    else
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_unknown", oldValue.c_str() ) );
    }
}
void NAVI2PG::CATSLCSpecify::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    CPLString oldValue = dstFeature->GetFieldAsString("type");

    int catslc = srcFeature->GetFieldAsInteger("CATSLC");
    if (catslc == 4)
    {
        dstFeature->SetField( "type", CPLString().Printf("%s_pirs(pristan)", oldValue.c_str() ) );
    }
    else
    {
    }
}

void NAVI2PG::AddSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    dstFeature->SetField( "name_en", srcFeature->GetFieldAsString( "OBJNAM" ) );

    CPLString natName = srcFeature->GetFieldAsString( "NOBJNM" );
    if(natName.length() > 0)
        dstFeature->SetField( "name_ru", natName.c_str() );
    else
        dstFeature->SetField( "name_ru", srcFeature->GetFieldAsString( "OBJNAM" ) );
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
            litchrStr.Printf("Iso%s", siggrpStr.c_str());
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
        case(6):
        {
            colourStr.Printf("%s", "Y");
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
        dstFeature->SetField( "orient_ccw", 360 - orient);
        dstFeature->SetField( "orient_cw", orient);
    }
}

std::vector<OGRFieldDefn*> NAVI2PG::AddORIENTasExtFields::GetOGRFieldDefn()
{
    std::vector<OGRFieldDefn*> result;

    OGRFieldDefn* oFieldOrientCW = new OGRFieldDefn( "orient_cw", OFTReal );
    oFieldOrientCW->SetWidth(32);
    result.push_back(oFieldOrientCW);

    OGRFieldDefn* oFieldOrientCCW = new OGRFieldDefn( "orient_ccw", OFTReal );
    oFieldOrientCCW->SetWidth(32);
    result.push_back(oFieldOrientCCW);

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

void NAVI2PG::AddVERCLRSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
   double verclr = srcFeature->GetFieldAsDouble( "VERCLR" );

   dstFeature->SetField( "name_en", CPLString().Printf("dr %.1f", verclr) );
   dstFeature->SetField( "name_ru", CPLString().Printf("dr %.1f", verclr) );

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

    dstFeature->SetField( "depth_fractional", CPLString().Printf("%d", abs( (int)( 10* (z - (int)z + 0.05) ) ) ) );
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

void NAVI2PG::AddVALDCOSignatures::Execute(OGRFeature *dstFeature, OGRFeature *srcFeature)
{
    int valdco = srcFeature->GetFieldAsInteger( "VALDCO" );

    dstFeature->SetField( "name_en", CPLString().Printf("%d", valdco) );
    dstFeature->SetField( "name_ru", CPLString().Printf("%d", valdco) );
}

void NAVI2PG::CreateLayerStrategy::Create(OGRDataSource *poDstDatasource, OGRSpatialReference* spatRef)
{
    char** papszLCO = NULL;
    papszLCO = CSLAddString(papszLCO, CPLString("OVERWRITE=yes").c_str() );

    const char* scheme = CPLGetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), NULL);
    if( scheme == NULL)
    {
        LOG( CPLString().Printf("Error: Layer %s can not be created: The schema isn't defined" ) );
        return;
    }

    /*
     * Создание слоя в источнике данных OGR
     */
    CPLString fullLayerName(scheme);
    fullLayerName.append(".");
    Layer_ = poDstDatasource->CreateLayer( fullLayerName.append(LayerName_.c_str()).c_str(), spatRef, GeomType_, papszLCO );

    LLOG(LOGGER::LOG_LEVEL_DEBUG,
         CPLString().Printf("Layer %s success created", LayerName_.c_str()).c_str());

    if (Layer_ == NULL)
    {
        LLOG(LOGGER::LOG_LEVEL_ERROR,
             CPLString().Printf("Error: Layer %s can not be created: %s", LayerName_.c_str(), CPLGetLastErrorMsg()));
        return;
    }
    /*
     * Добавление объектов в новый слой, определяется в классах-потомках.
     * Это может быть обычное копирование обыъектов с добавлением вспомогательных полей,
     * а может быть создание новых объектов на основе объектов из слоев источников.
     */
    DoProcess();
}

void NAVI2PG::CopyFeaturesStrategy::DoProcess()
{
    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CopyFeaturesStrategy::DoProcess - Start"));

    if(AddTypeFieldFlag_)
    {
        OGRFieldDefn* oFieldType = new OGRFieldDefn( "type", OFTString );
        oFieldType->SetWidth(64);

        if( Layer_->CreateField(oFieldType) != OGRERR_NONE )
        {
            //TODO Set exception
            LLOG(LOGGER::LOG_LEVEL_WARNING, "Creating field 'type' failed.");
        }
    }

    ModifyLayerDefnForCopyFields();
    ModifyLayerDefnForAddNewFields();

    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        OGRLayer* srcLayer = SrcLayers_[iSrcLayer].SrcLayer_;

        if(srcLayer == NULL)
            continue;

        LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("Source layer %d: %s", iSrcLayer, srcLayer->GetName()).c_str());

        srcLayer->ResetReading();

        LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("source layer reset reading success"));

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

            if(!poGeometry->IsValid())
            {
                LLOG(LOGGER::LOG_LEVEL_WARNING,
                     CPLString().Printf("Error. The geometry is not valid (Layer: %s, RCID: %d)",
                                        srcLayer->GetName(), poFeatureFrom->GetFieldAsInteger("RCID")));
                continue;
            }

            if (Layer_->GetLayerDefn()->GetGeomType() == wkbPolygon)
            {
                OGRPolygon* poly = (OGRPolygon*)poGeometry;

                OGRLinearRing* exteriorRing = poly->getExteriorRing();

                if(exteriorRing == NULL)
                {
                    LLOG(LOGGER::LOG_LEVEL_WARNING,
                         CPLString().Printf("Error. Polygon is empty (Layer: %s, RCID: %d)",
                                        srcLayer->GetName(), poFeatureFrom->GetFieldAsInteger("RCID")));
                    continue;
                }

                bool isExteriorRingClockwise = poly->getExteriorRing()->isClockwise();

                for(int interiorRingIndex = 0; interiorRingIndex < poly->getNumInteriorRings(); ++interiorRingIndex)
                {
                    OGRLinearRing* ring = poly->getInteriorRing(interiorRingIndex);
                    if(isExteriorRingClockwise == ring->isClockwise())
                        ring->reversePoints();
                }
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

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CopyFeaturesStrategy::DoProcess - Finish"));
}
void NAVI2PG::CopyFeaturesStrategy::ModifyLayerDefnForCopyFields()
{
    LLOG(LOGGER::LOG_LEVEL_DEBUG, CPLString().Printf("ModifyLayerDefnForCopyFields").c_str());

    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        OGRLayer* srcLayer = SrcLayers_[iSrcLayer].SrcLayer_;

        if(srcLayer == NULL)
            continue;

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

            LLOG(LOGGER::LOG_LEVEL_DEBUG_2, CPLString().Printf("Try to create field (copy field) %s", fieldDefn->GetNameRef()).c_str());

            if( Layer_->CreateField(fieldDefn) != OGRERR_NONE )
            {
                LLOG(LOGGER::LOG_LEVEL_WARNING, CPLString().Printf("creating field failed (copy field)").c_str());
                continue;
            }

            LLOG(LOGGER::LOG_LEVEL_DEBUG_2, CPLString().Printf("creating field success (copy field)").c_str());
        }
    }
}
void NAVI2PG::CopyFeaturesStrategy::ModifyLayerDefnForAddNewFields()
{
    LLOG(LOGGER::LOG_LEVEL_DEBUG, CPLString().Printf("ModifyLayerDefnForAddNewFields").c_str());

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

                LLOG(LOGGER::LOG_LEVEL_DEBUG_2, CPLString().Printf("Try to create field (new field) %s", fieldDefn->GetNameRef()).c_str());

                if( Layer_->CreateField(fieldDefn) != OGRERR_NONE )
                {
                    LLOG(LOGGER::LOG_LEVEL_WARNING, CPLString().Printf("creating field failed (new field)").c_str());
                    return;
                }

                LLOG(LOGGER::LOG_LEVEL_DEBUG_2, CPLString().Printf("creating field success (new field)").c_str());
            }
        }
    }
}
OGRSpatialReference* NAVI2PG::CopyFeaturesStrategy::GetSpatialRef()
{
    OGRSpatialReference* sr = NULL;
    for(size_t iSrcLayer = 0; iSrcLayer < SrcLayers_.size(); ++iSrcLayer)
    {
        OGRLayer* poLayer = SrcLayers_[iSrcLayer].SrcLayer_;
        if(poLayer != NULL)
        {
            sr = poLayer->GetSpatialRef();
        }
    }
    return sr;
}
bool NAVI2PG::CopyFeaturesStrategy::LayerCreationPossibility()
{
    if(SrcLayers_.size() == 0)
        return false;
    return true;
}

void NAVI2PG::CreateLightsSectorsStrategy::DoProcess()
{
    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateLightsSectorsStrategy::DoProcess - Start"));

    ModifyLayerDefnForAddNewFields();

    if(LightsLayer_ == NULL)
        return;

    //LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("Source layer %d: %s", LightsLayer_->GetName()).c_str());

    LightsLayer_->ResetReading();

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("source layer reset reading success"));

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


        pt1.setX( poPoint->getX() - sin(sectr1*TO_RADIANS) * valnmr * 1852 );
        pt1.setY( poPoint->getY() - cos(sectr1*TO_RADIANS) * valnmr * 1852 );
        pt1.transformTo(dstSpRef);

        pt2.setX( poPoint->getX() );
        pt2.setY( poPoint->getY() );
        pt2.transformTo(dstSpRef);

        pt3.setX( poPoint->getX() - sin(sectr2*TO_RADIANS) * valnmr * 1852 );
        pt3.setY( poPoint->getY() - cos(sectr2*TO_RADIANS) * valnmr * 1852 );
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
                pt.setX( poPoint->getX() - sin(angle * TO_RADIANS) * (radius ) );
                pt.setY( poPoint->getY() - cos(angle * TO_RADIANS) * (radius ) );
                pt.transformTo(dstSpRef);

                angle = angle + DegreesToPoint_;

                sectorLine->addPoint(&pt);
            }

            OGRPoint pt;
            pt.assignSpatialReference(&poSRS);
            pt.setX( poPoint->getX() - sin(angleTo * TO_RADIANS) * (radius ) );
            pt.setY( poPoint->getY() - cos(angleTo * TO_RADIANS) * (radius ) );
            pt.transformTo(dstSpRef);
            sectorLine->addPoint(&pt);

            poFeatureTo->SetGeometry( sectorLine );

            Layer_->CreateFeature(poFeatureTo);

            radius *= RadiusReductionCoef_;
        }
    }

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateLightsSectorsStrategy::DoProcess - Finish"));
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
    if(LightsLayer_== NULL)
        return NULL;

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
    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateTSSLPTStrategy::DoProcess - Start"));

    ModifyLayerDefnForAddNewFields();

    if (TSSLPTLayer_ == NULL)
        return;

    //LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("Source layer %d: %s", TSSLPTLayer_->GetName()).c_str());

    TSSLPTLayer_->ResetReading();

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("source layer reset reading success"));

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

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateTSSLPTStrategy::DoProcess - Finish"));
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
    if(TSSLPTLayer_ == NULL)
        return NULL;
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
    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateS57SignaturesStrategy::DoProcess - Start"));

    ModifyLayerDefnForAddNewFields();

    if(TextsLayer_==NULL)
        return;

    //LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("Source layer %d: %s", TextsLayer_->GetName()).c_str());

    TextsLayer_->ResetReading();

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("source layer reset reading success"));

    const char* need_convert = CPLGetConfigOption("NEED_CONVERT_SIGN_TO_CP1251",NULL);

    OGRFeature *poFeatureFromTexts;
    while( (poFeatureFromTexts = TextsLayer_->GetNextFeature()) != NULL )
    {
        CPLString lable = poFeatureFromTexts->GetFieldAsString("$TXSTR");

        if( need_convert && EQUAL(need_convert,"TRUE"))
        {
            CPLString lable_ISO8859 = CPLRecode(lable.c_str(), CPL_ENC_UTF8, CPL_ENC_ISO8859_1 );
            lable = CPLRecode(lable_ISO8859.c_str(), "CP1251", CPL_ENC_UTF8);
        }

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

                poFeatureTo->SetField("lable", lable.c_str() );
                Layer_->CreateFeature(poFeatureTo);

                OGRFeature::DestroyFeature( poFeatureTo );
            }

            OGRFeature::DestroyFeature(poFeatureFromIsolatedNode);
        }

        OGRFeature::DestroyFeature(poFeatureFromTexts);
    }

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateS57SignaturesStrategy::DoProcess - Finish"));
}
void NAVI2PG::CreateS57SignaturesStrategy::ModifyLayerDefnForAddNewFields()
{
    OGRFieldDefn oFieldAngleCW( "lable", OFTString );
    oFieldAngleCW.SetWidth(255);
    Layer_->CreateField(&oFieldAngleCW);
}
OGRSpatialReference* NAVI2PG::CreateS57SignaturesStrategy::GetSpatialRef()
{
    if(IsolatedNodeLayer_==NULL)
        return NULL;

    return IsolatedNodeLayer_->GetSpatialRef();
}
bool NAVI2PG::CreateS57SignaturesStrategy::LayerCreationPossibility()
{
    if(IsolatedNodeLayer_ != NULL && TextsLayer_ != NULL)
        return true;

    return false;
}

std::vector<int> NAVI2PG::CreateSystemLinesStrategy::getSubLinesRCIDs(const CPLString& lineDescription)
{
    size_t begin = lineDescription.find("(");
    size_t end = lineDescription.find(":");
    int subLineCounts = atoi(lineDescription.substr(begin+1, end - 1).c_str());

    std::stringstream ss(lineDescription.substr(lineDescription.find(":")+1, lineDescription.find(")")));

    std::vector<int> result;
    for(int i = 0; i < subLineCounts; ++i)
    {
        int subLineRCID;
        char delim;
        ss >> subLineRCID;
        ss >> delim;

        result.push_back(subLineRCID);
    }

    return result;
}

void NAVI2PG::CreateSystemLinesStrategy::getSubLine(const int subLineRCID, OGRLineString* resultSubLine)
{
    EdgeLayer_->ResetReading();
    OGRFeature *poFeatureFromEdge;
    while( (poFeatureFromEdge = EdgeLayer_->GetNextFeature()) != NULL )
    {
        int rcid =poFeatureFromEdge->GetFieldAsInteger("RCID");

        if (subLineRCID == rcid)
        {

            OGRLineString* geomFromEdge = (OGRLineString*)poFeatureFromEdge->GetGeometryRef();

            int nameRCID_0 = poFeatureFromEdge->GetFieldAsInteger("NAME_RCID_0");
            int nameRCID_1 = poFeatureFromEdge->GetFieldAsInteger("NAME_RCID_1");

            ConnectedNodeLayer_->ResetReading();
            OGRFeature *poFeatureFromConnectedNode;
            OGRPoint* firstPoint;
            OGRPoint* secondPoint;
            while( (poFeatureFromConnectedNode = ConnectedNodeLayer_->GetNextFeature()) != NULL )
            {
                int rcid =poFeatureFromConnectedNode->GetFieldAsInteger("RCID");
                if (nameRCID_0 == rcid)
                {
                    firstPoint = (OGRPoint*)poFeatureFromConnectedNode->GetGeometryRef();
                }

                if (nameRCID_1 == rcid)
                {
                    secondPoint = (OGRPoint*)poFeatureFromConnectedNode->GetGeometryRef();
                }
            }

            resultSubLine->addPoint(firstPoint);
            resultSubLine->addSubLineString(geomFromEdge);
            resultSubLine->addPoint(secondPoint);
        }

        OGRFeature::DestroyFeature(poFeatureFromEdge);
    }
}

void NAVI2PG::CreateSystemLinesStrategy::DoProcess()
{
    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateSystemLinesStrategy::DoProcess - Start"));

    ModifyLayerDefnForAddNewFields();

    if(LinesLayer_ == NULL || EdgeLayer_ == NULL || ConnectedNodeLayer_ == NULL)
        return;

    LinesLayer_->ResetReading();

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("source LinesLayer_ reset reading success"));

    OGRFeature *poFeatureFromLines;

    while( (poFeatureFromLines = LinesLayer_->GetNextFeature()) != NULL )
    {
        CPLString lineDescription = poFeatureFromLines->GetFieldAsString("NAME_RCID");

        std::vector<int> subLinesRCIDs = getSubLinesRCIDs(lineDescription);

        OGRFeature* poFeatureTo = OGRFeature::CreateFeature(Layer_->GetLayerDefn());

        OGRLineString geomFromEdge;

        for(size_t i = 0; i < subLinesRCIDs.size(); ++i)
        {
            OGRLineString subLine;
            getSubLine(subLinesRCIDs[i], &subLine);
            geomFromEdge.addSubLineString(&subLine);
        }

        poFeatureTo->SetGeometry(&geomFromEdge);

        Layer_->CreateFeature(poFeatureTo);

        OGRFeature::DestroyFeature( poFeatureTo );

        OGRFeature::DestroyFeature(poFeatureFromLines);
    }

    LLOG(LOGGER::LOG_LEVEL_DEBUG_1, CPLString().Printf("CreateSystemLinesStrategy::DoProcess - Finish"));
}
void NAVI2PG::CreateSystemLinesStrategy::ModifyLayerDefnForAddNewFields()
{
}
OGRSpatialReference* NAVI2PG::CreateSystemLinesStrategy::GetSpatialRef()
{
    if(EdgeLayer_==NULL)
        return NULL;

    return EdgeLayer_->GetSpatialRef();
}
bool NAVI2PG::CreateSystemLinesStrategy::LayerCreationPossibility()
{
    if(EdgeLayer_ != NULL && LinesLayer_ != NULL && ConnectedNodeLayer_ != NULL)
        return true;

    return false;
}

void NAVI2PG::Import(const char  *pszS57DataSource, const char  *pszPGConnectionString)
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

    CPLSetConfigOption("CPL_DEBUG","ON" );
    CPLSetConfigOption("CPL_TIMESTAMP", "ON");
    CPLSetConfigOption("CPL_LOG_ERRORS", "ON");
    CPLSetConfigOption("CPL_LOG", "c:\gdal.log");
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

    if( CPLGetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), NULL) == NULL)
    {
        CPLSetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), CPLGetBasename(pszS57DataSource));
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
     * Автоматическое создание схемы
     */
    const char *crateSchemaFlag= CPLGetConfigOption(CommandLineKeys::CREATE_SCHEME_FLAG.c_str(), "FALSE");

    if ( EQUAL(crateSchemaFlag,"TRUE"))
    {
        CPLErrorReset();

        poDstDatasource->ExecuteSQL( CPLString().Printf("CREATE SCHEMA\"%s\";",
            CPLGetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), "")), NULL, NULL );

        if( CPLGetLastErrorNo() != CE_None )
        {
            LLOG(LOGGER::LOG_LEVEL_ERROR, CPLString().Printf("DB schems creation: %s", CPLGetLastErrorMsg()) );
        }
        CPLErrorReset();
    }

    /*
     *  Конфигурация
     */
    //std::vector<CreateLayerStrategy*>layersCreators;
    std::vector<CreateLayerStrategy*>layersCreators = configurate(poSrcDatasource);
    //std::vector<CreateLayerStrategy*>layersCreators = configurateTest(poSrcDatasource);

    /*
     *  Определяем общую СК
     */
    size_t layerIndex = 0;
    while(poSrcDatasource->GetLayer(layerIndex)->GetSpatialRef() == NULL)
    {
        layerIndex++;
    }
    OGRSpatialReference* spatRef = poSrcDatasource->GetLayer(layerIndex)->GetSpatialRef();

    /*
     *  Импорт данных в БД
     */
    for(size_t i = 0; i < layersCreators.size(); ++i)
    {
        CreateLayerStrategy* layersCreator = layersCreators[i];
        layersCreator->Create(poDstDatasource, spatRef);
    }

    /*
     *  Cоздание файла конфигурации для mapserver
     */
    OGRSpatialReference poSRSfrom;
    poSRSfrom.importFromEPSG(4326);

    OGRSpatialReference poSRSto;
    poSRSto.importFromEPSG(3857);

    OGRLayer* layer = poSrcDatasource->GetLayer(0);
    OGREnvelope envelope;
    OGRErr err = layer->GetExtent(&envelope);

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

#ifdef WIN32
        const char* mapserver_config_file =
                   CPLGetConfigOption(
                       CommandLineKeys::MAPSERVER_CONFIG_TEMPLATE_FILENAME.c_str(),
                       NULL);
        if(mapserver_config_file != NULL)
        {
            CopyConfigFile(mapserver_config_file, CPLResetExtension(pszS57DataSource, "map"), newExtent, pszPGConnectionString);
        }

       const char* mapnik_config_file =
               CPLGetConfigOption(
                   CommandLineKeys::MAPNIK_CONFIG_TEMPLATE_FILENAME.c_str(),
                   NULL);
       if(mapnik_config_file != NULL)
       {
            CopyConfigFile(mapnik_config_file, CPLResetExtension(pszS57DataSource, "mapnik.xml"), newExtent, pszPGConnectionString);
       }

       const char* mapnik_pyscript_file =
               CPLGetConfigOption(
                   CommandLineKeys::MAPNIK_PYSCRIPT_TEMPLATE_FILENAME.c_str(),
                   NULL);
       if(mapnik_pyscript_file != NULL)
       {
            CopyConfigFile(mapnik_pyscript_file, CPLResetExtension(pszS57DataSource, "mapnik.py"), newExtent, pszPGConnectionString);
       }
#else
        const char* mapserver_config_file =
                   CPLGetConfigOption(
                       CommandLineKeys::MAPSERVER_CONFIG_TEMPLATE_FILENAME.c_str(),
                       "/usr/local/share/navi2pg/mapserver.map.template");
       CopyConfigFile(mapserver_config_file, CPLResetExtension(pszS57DataSource, "map"), newExtent, pszPGConnectionString);

       const char* mapnik_config_file =
               CPLGetConfigOption(
                   CommandLineKeys::MAPNIK_CONFIG_TEMPLATE_FILENAME.c_str(),
                   "/usr/local/share/navi2pg/mapnik.xml.template");
       CopyConfigFile(mapnik_config_file, CPLResetExtension(pszS57DataSource, "mapnik.xml"), newExtent, pszPGConnectionString);

       const char* mapnik_pyscript_file =
               CPLGetConfigOption(
                   CommandLineKeys::MAPNIK_PYSCRIPT_TEMPLATE_FILENAME.c_str(),
                   "/usr/local/share/navi2pg/mapnik.py.template");
       CopyConfigFile(mapnik_pyscript_file, CPLResetExtension(pszS57DataSource, "mapnik.py"), newExtent, pszPGConnectionString);
#endif

    OGRDataSource::DestroyDataSource( poSrcDatasource );
    OGRDataSource::DestroyDataSource( poDstDatasource );
}

void NAVI2PG::CopyConfigFile(
        const char  *mapConfigTemplateFilename,
        const char  *mapConfigFilename,
        OGREnvelope newExtent,
        const char  *pszPGConnectionString)
{
    std::string S57_FILENAME = "{S57_file_name}";
    std::string S57_EXTENT_X_MIN = "{S57_extent_X_Min}";
    std::string S57_EXTENT_Y_MIN = "{S57_extent_Y_Min}";
    std::string S57_EXTENT_X_MAX = "{S57_extent_X_Max}";
    std::string S57_EXTENT_Y_MAX = "{S57_extent_Y_Max}";
    std::string PG_DBNAME = "{PG_DBNAME}";
    std::string PG_USER = "{PG_USER}";
    std::string PG_PASSWORD = "{PG_PASSWORD}";
    std::string PG_HOST = "{PG_HOST}";
    std::string PG_PORT = "{PG_PORT}";
    std::string PG_SCHEME = "{PG_SCHEME}";

    /*
     *  Парсим параметры подключения к БД
     */
    CPLString connectionString(pszPGConnectionString);

    std::string dbname = readFromDBConnectString(connectionString, "dbname");
    std::string user = readFromDBConnectString(connectionString, "user");
    std::string password = readFromDBConnectString(connectionString, "password");
    std::string host = readFromDBConnectString(connectionString, "host");
    std::string port = readFromDBConnectString(connectionString, "port");

    if (host=="")
        host.assign("localhost");

    if (port=="")
        port.assign("5432");

    const char* scheme = CPLGetConfigOption(CommandLineKeys::SCHEME_NAME.c_str(), "public");

    /*
     *  Копируем шаблон конфигурации с заменой переменных
     */

    std::ifstream input;
    input.open(mapConfigTemplateFilename, std::ios::in);
    if (!input.good())
    {
        LOG( CPLString().Printf("Error: Template file %s not found ", mapConfigTemplateFilename) );
        return;
    }

    std::ofstream output;
    output.open(mapConfigFilename, std::ios::out);

    std::string line;

    while (!input.eof())
    {
        std::getline(input,line);
        int pos = 0;


        if( (pos = line.find(S57_FILENAME) ) != std::string::npos)
            line.replace(pos, S57_FILENAME.size(), CPLGetBasename(mapConfigFilename) );

        if( (pos = line.find(S57_EXTENT_X_MIN) ) != std::string::npos)
            line.replace(pos, S57_EXTENT_X_MIN.size(), CPLString().Printf("%e", newExtent.MinX).c_str() );

        if( (pos = line.find (S57_EXTENT_Y_MIN) ) != std::string::npos)
            line.replace(pos, S57_EXTENT_Y_MIN.size(), CPLString().Printf("%e", newExtent.MinY).c_str() );

        if( (pos = line.find (S57_EXTENT_X_MAX) ) != std::string::npos)
            line.replace(pos, S57_EXTENT_X_MAX.size(), CPLString().Printf("%e", newExtent.MaxX).c_str() );

        if( (pos = line.find (S57_EXTENT_Y_MAX) ) != std::string::npos)
            line.replace(pos, S57_EXTENT_Y_MAX.size(), CPLString().Printf("%e", newExtent.MaxY).c_str() );

        if( (pos = line.find (PG_DBNAME) ) != std::string::npos)
            line.replace(pos, PG_DBNAME.size(), dbname.c_str() );

        if( (pos = line.find (PG_USER) ) != std::string::npos)
            line.replace(pos, PG_USER.size(), user.c_str() );

        if( (pos = line.find (PG_PASSWORD) ) != std::string::npos)
            line.replace(pos, PG_PASSWORD.size(), password.c_str() );

        if( (pos = line.find (PG_HOST) ) != std::string::npos)
            line.replace(pos, PG_HOST.size(),  host.c_str() );

        if( (pos = line.find (PG_PORT) ) != std::string::npos)
            line.replace(pos, PG_PORT.size(), port.c_str() );

        if( (pos = line.find (PG_SCHEME) ) != std::string::npos)
            line.replace(pos, PG_SCHEME.size(), scheme);

        output << line << "\n";
    }
}
