#ifndef NAVI2PG_H
#define NAVI2PG_H

#include <map>
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
    private:
        CPLString GetFirstPartOfSig(OGRFeature* srcFeature, bool withSIGGRP);
    };

    /*
     *  ORIENT угол повораота в пространстве
     */
    class AddORIENTSignatures: public AddSignatures
    {
    public:
        AddORIENTSignatures(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

    /*
     * NATSUR - Материал поверхности
     */
    class AddNATSURSignatures: public AddSignatures
    {
        std::map<int, CPLString> SurfaceMaterial_;
    public:
        AddNATSURSignatures()
        {
            SurfaceMaterial_[1] = "ил";
            SurfaceMaterial_[2] = "глина";
            SurfaceMaterial_[3] = "силт";
            SurfaceMaterial_[4] = "песок";
            SurfaceMaterial_[5] = "камень";
            SurfaceMaterial_[6] = "гравий";
            SurfaceMaterial_[7] = "галька";
            SurfaceMaterial_[8] = "булыжник";
            SurfaceMaterial_[9] = "скала";
            SurfaceMaterial_[11] = "лава";
            SurfaceMaterial_[14] = "коралл";
            SurfaceMaterial_[17] = "ракушки";
            SurfaceMaterial_[18] = "валун";
            SurfaceMaterial_[32000] = "нет значения";

        }

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

    /*
     * VALSOU - значение глубины
     */
    class AddVALSOUSignatures: public AddSignatures
    {
    public:
        AddVALSOUSignatures(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

    class AddVALSOUasExtFields: public AddNewFieldStrategy
    {
    public:
        AddVALSOUasExtFields(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };


    /*
     *  Soundg - метка глубины
     */
    class AddSoundgValues: public AddNewFieldStrategy
    {
    public:
        AddSoundgValues(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

    /*
     * VALMAG - значение магнитного склонения
     */
    class AddVALMAGSignatures: public AddSignatures
    {
    public:
        AddVALMAGSignatures(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
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


    class CreateTSSLPTStrategy : public CreateLayerStrategy
    {
        OGRLayer* TSSLPTLayer_;
    public:
        CreateTSSLPTStrategy(const CPLString& layerName, OGRLayer* srcLayer)
            : CreateLayerStrategy(layerName, wkbPoint),
              TSSLPTLayer_(srcLayer)
        {

        }

    private:
        void DoProcess();
        void ModifyLayerDefnForAddNewFields();

        OGRSpatialReference* GetSpatialRef();
        bool LayerCreationPossibility();
    };

    class CreateS57SignaturesStrategy : public CreateLayerStrategy
    {
        OGRLayer* IsolatedNodeLayer_;
        OGRLayer* TextsLayer_;
    public:
        CreateS57SignaturesStrategy(const CPLString& layerName, OGRLayer* isolatedNodeLayer, OGRLayer* textsLayer)
            : CreateLayerStrategy(layerName, wkbPoint),
              IsolatedNodeLayer_(isolatedNodeLayer),
              TextsLayer_(textsLayer)
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

