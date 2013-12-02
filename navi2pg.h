#ifndef NAVI2PG_H
#define NAVI2PG_H

#include <vector>

#include "ogr_api.h"
#include "ogrsf_frmts.h"

namespace NAVI2PG {

    class NAVILayer
    {
    private:
        CPLString LayerName_;
        OGRwkbGeometryType LayerGeometryType_;
        std::vector<OGRLayer*> SrcLayers_;
    public:
        NAVILayer(const CPLString& layerName, OGRwkbGeometryType geomType, OGRDataSource* poSrcDatasource, std::vector<CPLString> srcLayerNames);

        void CopyTo(OGRDataSource* poDstDatasource);

    private:
        bool checkSpatialReferences();

        virtual void InitFields(OGRLayer* poLayer) = 0;
        virtual void SetFields(OGRLayer* layerFrom, OGRFeature* featureTo) = 0;

    };

    class NAVILayerSimple: public NAVILayer
    {
    public:
        NAVILayerSimple(const CPLString& layerName, OGRwkbGeometryType geomType, OGRDataSource* poSrcDatasource, std::vector<CPLString> srcLayerNames);

    private:
        void InitFields(OGRLayer* poLayer);
        void SetFields(OGRLayer* layerFrom, OGRFeature* featureTo);

        virtual void SetTypeField(OGRLayer* layerFrom, OGRFeature* featureTo);
        virtual void SetNameRuField(OGRLayer* layerFrom, OGRFeature* featureTo);
        virtual void SetNameEnField(OGRLayer* layerFrom, OGRFeature* featureTo);
    };

    void Import(const char* fromS57DataSource, const char* toPGConnectionString);

}
#endif // NAVI2PG_H
