#ifndef NAVI2PG_H
#define NAVI2PG_H

#include <vector>

#include "ogr_api.h"
#include "ogrsf_frmts.h"
#include "feature_creation_rules.h"

#include "logger.h"

#define TO_DEGREES 57.2957795130823208766
#define TO_RADIANS 0.017453292519943295769

namespace NAVI2PG {

    class AddNewFieldStrategy
    {
    public:
        AddNewFieldStrategy(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature) = 0;
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn() = 0;
    };

    class AddSignatures: public AddNewFieldStrategy
    {
    public:
        AddSignatures(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

    class AddLightsSignatures: public AddSignatures
    {
    public:
        AddLightsSignatures(){}
        void Execute(OGRFeature* dstFeatures, OGRFeature* srcFeature);
    };

    class AddSoundgValues: public AddNewFieldStrategy
    {
    public:
        AddSoundgValues(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

    class CreateLayerStrategy
    {
    protected:
        const CPLString LayerName_;
        const OGRwkbGeometryType GeomType_;
        OGRLayer* Layer_;

    public:
        CreateLayerStrategy(const CPLString& layerName, OGRwkbGeometryType geomType)
            : LayerName_(layerName),
              GeomType_(geomType)
        {
        }

        void Create(OGRDataSource *poDstDatasource);

    private:
        virtual void DoProcess() = 0;
        virtual OGRSpatialReference* GetSpatialRef() = 0;
        virtual bool LayerCreationPossibility() = 0;
    };

    struct LayerWithCopyRules
    {
        OGRLayer* SrcLayer_;
        std::vector<AddNewFieldStrategy*> AddNewFieldStrategies_;
        std::vector<CPLString> FieldsNamesForCopy_;
    };
    typedef std::vector<LayerWithCopyRules> LayersWithCopyRules;

    class CopyFeaturesStrategy : public CreateLayerStrategy
    {
        LayersWithCopyRules SrcLayers_;
        bool AddTypeFieldFlag_;
    public:
        CopyFeaturesStrategy(const CPLString& layerName, OGRwkbGeometryType geomType, LayersWithCopyRules srcLayersWithRules, bool addTypeField = true)
            : CreateLayerStrategy(layerName, geomType),
              AddTypeFieldFlag_(addTypeField)
        {
            for(size_t iSrcLayer = 0; iSrcLayer < srcLayersWithRules.size(); ++iSrcLayer)
            {
                OGRLayer* poLayer = srcLayersWithRules[iSrcLayer].SrcLayer_;
                if(poLayer != NULL)
                {
                    SrcLayers_.push_back(srcLayersWithRules[iSrcLayer]);
                }
            }
        }

    private:
        void DoProcess();
        void ModifyLayerDefnForCopyFields();
        void ModifyLayerDefnForAddNewFields();

        OGRSpatialReference* GetSpatialRef();
        bool LayerCreationPossibility();
    };

    class CreateLightsSectorsStrategy : public CreateLayerStrategy
    {
        OGRLayer* LightsLayer_;
    public:
        CreateLightsSectorsStrategy(const CPLString& layerName, OGRwkbGeometryType geomType, OGRLayer* lightsLayer)
            : CreateLayerStrategy(layerName, geomType),
              LightsLayer_(lightsLayer)
        {

        }

    private:
        void DoProcess();
        void ModifyLayerDefnForAddNewFields();

        OGRSpatialReference* GetSpatialRef();
        bool LayerCreationPossibility();
    };


    void Import(const char* fromS57DataSource, const char* toPGConnectionString);

}
#endif // NAVI2PG_H
