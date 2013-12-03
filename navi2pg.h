#ifndef NAVI2PG_H
#define NAVI2PG_H

#include <vector>

#include "ogr_api.h"
#include "ogrsf_frmts.h"

namespace NAVI2PG {


    class NAVISRCLayer
    {
    protected:
        OGRLayer* poLayer;
    public:
        NAVISRCLayer(OGRLayer* layerFrom);

        OGRLayer* getOGRLayer();

        virtual CPLString GetNameRuField(OGRFeature *srcFeature);
        virtual CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    class NAVISRCLayerOBJNAMSign: public NAVISRCLayer
    {
    public:
        NAVISRCLayerOBJNAMSign(OGRLayer* layerFrom):NAVISRCLayer(layerFrom){}

        CPLString GetNameRuField(OGRFeature *srcFeature);
        CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    class NAVISRCLayerLIGHTSSign: public NAVISRCLayer
    {
    public:
        NAVISRCLayerLIGHTSSign(OGRLayer* layerFrom):NAVISRCLayer(layerFrom){}

        CPLString GetNameRuField(OGRFeature *srcFeature);
        CPLString GetNameEnField(OGRFeature *srcFeature);
    };

    typedef struct
    {
        CPLString fieldName;
        OGRFieldType fieldType;
    }FieldForCopy;

    typedef struct
    {
        CPLString layerName;
        OGRwkbGeometryType geomType;
        bool hasSignature;
        std::vector<NAVISRCLayer*> srcLayers;
        std::vector<FieldForCopy> fieldsForCopy;
    }NaviLayerConfuguration;

    typedef std::vector<NaviLayerConfuguration> Navi2PGConfig;

    class NAVILayer
    {
    private:
        CPLString LayerName_;
        OGRwkbGeometryType LayerGeometryType_;
        std::vector<NAVISRCLayer*> SrcLayers_;
        std::vector<FieldForCopy> FieldsToCopy_;
    public:
        NAVILayer(const CPLString& layerName, OGRwkbGeometryType geomType, std::vector<NAVISRCLayer*> srcLayers, std::vector<FieldForCopy> fieldsToCopy);

        void CopyTo(OGRDataSource* poDstDatasource);

    private:
        bool CheckSpatialReferences();
        void AddFieldsForCopy(OGRLayer *poLayer);
        void CopyFields(OGRFeature* srcFeature, OGRFeature* dstFeature);

        virtual void InitFields(OGRLayer* poLayer) = 0;
        virtual void SetFields(NAVISRCLayer* layerFrom, OGRFeature* srcFeature, OGRFeature* dstFeature) = 0;

    };

    class NAVILayerSimple: public NAVILayer
    {
    public:
        NAVILayerSimple(const CPLString& layerName, OGRwkbGeometryType geomType, std::vector<NAVISRCLayer*> srcLayers, std::vector<FieldForCopy> fieldsToCopy);

    private:
        void InitFields(OGRLayer* poLayer);
        void SetFields(NAVISRCLayer* layerFrom, OGRFeature* srcFeature, OGRFeature* dstFeature);

        virtual void SetTypeField(NAVISRCLayer* layerFrom, OGRFeature* featureTo);
        virtual void SetNameRuField(NAVISRCLayer* layerFrom, OGRFeature* featureFrom, OGRFeature* featureTo);
        virtual void SetNameEnField(NAVISRCLayer* layerFrom, OGRFeature* featureFrom, OGRFeature* featureTo);
    };


    void Import(const char* fromS57DataSource, const char* toPGConnectionString);

}
#endif // NAVI2PG_H
