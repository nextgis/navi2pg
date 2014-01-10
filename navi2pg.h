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

/**
* namespace NAVI2PG
* @brief Импортирование данных из файла формата s57 в БД PostgreSQL
*/
namespace NAVI2PG {

/**
* @brief Абстрактный класс представляющий интерфейс стратегии добавления новых полей в таблицы.
*/
    class AddNewFieldStrategy
    {
    public:
        AddNewFieldStrategy(){}
/**
* @brief Абстрактный метод. Исполнение стратегии.
* @param dstFeature Запись в которую производится добавление новоых полей
* @param srcFeature Запись-источник данных на основании которых формируется значение новых полей
*/
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature) = 0;
/**
* @brief Абстрактный метод. Возвращает описание новых полей.
* @return Вектор описаний полей, добавляемых данной стратегией.
*/
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn() = 0;
    };

/**
* @brief Абстрактный класс представляющий интерфейс стратегии редактирования поля "type".
*/
    class ModifyTypeField: public AddNewFieldStrategy
    {
    public:
        ModifyTypeField(){}
/**
* @brief Абстрактный метод. Исполнение стратегии.
* @param dstFeature Запись поле которого подвергается редактированию
* @param srcFeature Запись-источник данных на основании которых редактируются значения полей
*/
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature) = 0;
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс представляющий стратегию редактирования поля type на основании данных поля BOYSHP.
* BOYSHP - форма буя
*/
    class BOYSHPSpecify: public ModifyTypeField
    {
    public:
        BOYSHPSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс представляющий стратегию редактирования поля type на основании данных поля BCNSHP.
* BCNSHP - форма знака
*/
    class BCNSHPSpecify: public ModifyTypeField
    {
    public:
        BCNSHPSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс представляющий стратегию редактирования поля type на основании полей SECTR1 и SECTR1.
*/
        class SECTRSpecify: public ModifyTypeField
        {
        public:
            SECTRSpecify(){}
            virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        };

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru,
* на основе данных из полей OBJNAM и NOBJNM
*/
    class AddSignatures: public AddNewFieldStrategy
    {
    public:
        AddSignatures(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru,
* для объектов "Огни", на основе данных из полей CATLIT, SIGPER, HEIGHT, VALNMR, SIGGRP, LITCHR, COLOUR
*/
    class AddLightsSignatures: public AddSignatures
    {
    public:
        AddLightsSignatures(){}
        void Execute(OGRFeature* dstFeatures, OGRFeature* srcFeature);
    private:
/**
* @brief Вспомогательная функция, возвращает первую часть подписи
*/
        CPLString GetFirstPartOfSig(OGRFeature* srcFeature, bool withSIGGRP);
    };

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию об углах поворота в пространстве, на основе значения поля ORIENT - Ориентация.
* Формат подписи: "1.02 deg" и "3.21 град"
*
*/
    class AddORIENTSignatures: public AddSignatures
    {
    public:
        AddORIENTSignatures(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Класс-стратегия для добавления поля orient, содержащего угол поворота по часовой стрелке от направления на север.
* На основе значения поля ORIENT - Ориентация
*/
    class AddORIENTasExtFields: public AddNewFieldStrategy
    {
    public:
        AddORIENTasExtFields(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию о материалах поверхности, на основе значения поля NATSUR - Материал поверхности.
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

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию о значение глубины, на основе значения поля VALSOU - Значение глубины.
*/
    class AddVALSOUSignatures: public AddSignatures
    {
    public:
        AddVALSOUSignatures(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Класс-стратегия для добавления полей depth_whole и depth_fractional, содержащих целую и дробную часть значения глубины  соответственно.
* Целая и дробная части значения глубины определяются по значению поля VALSOU - Значение глубины.
*/
    class AddVALSOUasExtFields: public AddNewFieldStrategy
    {
    public:
        AddVALSOUasExtFields(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс-стратегия для добавления полей depth_whole и depth_fractional, содержащих целую и дробную часть значения глубины  соответственно.
* Целая и дробная части значения глубины определяются по значению координаты Z.
*/
    class AddSoundgValues: public AddNewFieldStrategy
    {
    public:
        AddSoundgValues(){}

        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию о значение магнитного склонения, на основе значения поля VALMAG - значение магнитного склонения.
*/
    class AddVALMAGSignatures: public AddSignatures
    {
    public:
        AddVALMAGSignatures(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Абстрактный класс представляющий интерфейс стратегии добавления нового слоя в БД.
*/
    class CreateLayerStrategy
    {
    protected:
        const CPLString LayerName_;
        const OGRwkbGeometryType GeomType_;
        OGRLayer* Layer_;

    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param geomType Тип геометрии
*/
        CreateLayerStrategy(const CPLString& layerName, OGRwkbGeometryType geomType)
            : LayerName_(layerName),
              GeomType_(geomType)
        {
        }
/**
* @brief Создание нового слоя в БД.
* @param poDstDatasource Источник данных где будет создан новый слой
*/
        void Create(OGRDataSource *poDstDatasource);

    private:
/**
* @brief Абстрактный метод копирования/добавления/редактирования объектов в слое на основе данных из слоев-источников.
*/
        virtual void DoProcess() = 0;
/**
* @brief Абстрактный метод получения пространственного индекса на основе слоев-источников.
*/
        virtual OGRSpatialReference* GetSpatialRef() = 0;
/**
* @brief Абстрактный метод определения возможности создания нового слоя из слоев-источников.
* @return Флаг возможности создания слоя
*/
        virtual bool LayerCreationPossibility() = 0;
    };

    struct LayerWithCopyRules
    {
        OGRLayer* SrcLayer_;
        std::vector<AddNewFieldStrategy*> AddNewFieldStrategies_;
        std::vector<CPLString> FieldsNamesForCopy_;
    };
    typedef std::vector<LayerWithCopyRules> LayersWithCopyRules;

/**
* @brief Класс-стратегия добавления нового слоя в БД, основаный на принципе копирования геометрий всех объектов из слоев-источников.
*/
    class CopyFeaturesStrategy : public CreateLayerStrategy
    {
        LayersWithCopyRules SrcLayers_;
        bool AddTypeFieldFlag_;
    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param geomType Тип геометрии
* @param srcLayersWithRules Слои-источники с набором стратегий копирования/добавления/редактирования объектов для нового слоя
* @param addTypeField Флаг необходимости создания поля "type"
*/
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

/**
* @brief Класс-стратегия добавления слоя, содержащего информацию о секторах огней.
*/
    class CreateLightsSectorsStrategy : public CreateLayerStrategy
    {
        OGRLayer* LightsLayer_;
    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param lightsLayer Слой содержащий информацию об огнях
*/
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


/**
* @brief Класс-стратегия добавления слоя, содержащего центр полигонов слоя TSSLPT.
* Слой TSSLPT содержит части полосы сист.раздел.движ.
*/
    class CreateTSSLPTStrategy : public CreateLayerStrategy
    {
        OGRLayer* TSSLPTLayer_;
    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param srcLayer Слой TSSLPT
*/
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

/**
* @brief Класс-стратегия добавления слоя, содержащего подписи s57.
* Данные формируются на основании слоев "IsolatedNode" и "$TEXTS"
*/
    class CreateS57SignaturesStrategy : public CreateLayerStrategy
    {
        OGRLayer* IsolatedNodeLayer_;
        OGRLayer* TextsLayer_;
    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param isolatedNodeLayer Слой "$IsolatedNode"
* @param textsLayer Слой "$TEXTS"
*/
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

/**
 * @brief Импортирование данных из файла формата s57 в БД PostgreSQL
 *
 * @param fromS57DataSource - полный путь до файла-источника данных s57
 * @param toPGConnectionString - строка подключения к БД PostgreSQL (http://www.gdal.org/ogr/drv_pg.html)
 */
    void Import(const char* fromS57DataSource, const char* toPGConnectionString);

}
#endif // NAVI2PG_H

