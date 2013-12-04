#ifndef NAVI2PG_H
#define NAVI2PG_H

#include <vector>

#include "ogr_api.h"
#include "ogrsf_frmts.h"

namespace NAVI2PG {

    typedef struct
    {
        CPLString fieldName;
    }FieldForCopy;

    class NAVISRCLayer
    {
    protected:
        OGRLayer* poLayer;
        std::vector<FieldForCopy> FieldsToCopy_;

    public:
        NAVISRCLayer(OGRLayer* layerFrom);
        NAVISRCLayer(OGRLayer* layerFrom, std::vector<FieldForCopy> fieldsToCopy);

        OGRLayer* getOGRLayer();

        void ImportFeaturesTo(OGRLayer* dstLayer);
        void ImportFieldsDefns(OGRLayer* dstLayer);

        virtual CPLString GetNameRuField(OGRFeature *srcFeature);
        virtual CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    class NAVISRCLayerOBJNAMSign: public NAVISRCLayer
    {
    public:
        NAVISRCLayerOBJNAMSign(OGRLayer* layerFrom):NAVISRCLayer(layerFrom){}
        NAVISRCLayerOBJNAMSign(OGRLayer* layerFrom, std::vector<FieldForCopy> fieldsToCopy):NAVISRCLayer(layerFrom, fieldsToCopy){}

        CPLString GetNameRuField(OGRFeature *srcFeature);
        CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    class NAVISRCLayerLIGHTSSign: public NAVISRCLayer
    {
    public:
        NAVISRCLayerLIGHTSSign(OGRLayer* layerFrom):NAVISRCLayer(layerFrom){}
        NAVISRCLayerLIGHTSSign(OGRLayer* layerFrom, std::vector<FieldForCopy> fieldsToCopy):NAVISRCLayer(layerFrom, fieldsToCopy){}

        CPLString GetNameRuField(OGRFeature *srcFeature);
        CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    typedef struct
    {
        CPLString layerName;
        OGRwkbGeometryType geomType;
        bool hasSignature;
        std::vector<NAVISRCLayer*> srcLayers;
    }NaviLayerConfuguration;

    typedef std::vector<NaviLayerConfuguration> Navi2PGConfig;

    class NAVILayer
    {
    private:
        CPLString LayerName_;
        OGRwkbGeometryType LayerGeometryType_;
        std::vector<NAVISRCLayer*> SrcLayers_;
    public:
        NAVILayer(const CPLString& layerName, OGRwkbGeometryType geomType, std::vector<NAVISRCLayer*> srcLayers);

        void CopyTo(OGRDataSource* poDstDatasource);

    private:
        bool CheckSpatialReferences();

    };


    void Import(const char* fromS57DataSource, const char* toPGConnectionString);

}
#endif // NAVI2PG_H
