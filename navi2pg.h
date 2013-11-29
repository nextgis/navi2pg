#ifndef NAVI2PG_H
#define NAVI2PG_H

#include "ogr_api.h"
#include "ogrsf_frmts.h"

namespace NAVI2PG {

    class NAVILayer
    {
    protected:
        OGRLayer* poLayer;
    public:
        NAVILayer(OGRLayer* layerFrom);
        ~NAVILayer(){};

        bool equalSpatialReferences(const NAVILayer& layer);

        void copyFeaturesTo(OGRLayer* layerTo);
    private:

        virtual void doCreateFields(OGRFeature *featureFrom, OGRFeature *featureTo);
        virtual void doCreateTypeField(OGRFeature *featureFrom, OGRFeature *featureTo);
        virtual void doCreateNameRuField(OGRFeature *featureFrom, OGRFeature *featureTo);
        virtual void doCreateNameEnField(OGRFeature *featureFrom, OGRFeature *featureTo);
    };

    class LightsNAVILayer: public NAVILayer
    {
    public:
        LightsNAVILayer(OGRLayer* layerFrom):NAVILayer(layerFrom){};
    private:
        void doCreateNameRuField(OGRFeature *featureFrom, OGRFeature *featureTo);
        void doCreateNameEnField(OGRFeature *featureFrom, OGRFeature *featureTo);
    };

    void Import(const char  *fromS57DataSource, const char  *toPGConnectionString);

}
#endif // NAVI2PG_H
