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
 #ifndef NAVI2PG_H
#define NAVI2PG_H

#include <map>
#include <vector>

#include "ogr_api.h"
#include "ogrsf_frmts.h"

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
* @param dstFeature Запись, в которую производится добавление новых полей
* @param srcFeature Запись-источник данных, на основании которых формируется значение новых полей
*/
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature) = 0;
/**
* @brief Абстрактный метод. Возвращает описание новых полей.
* @return Вектор описаний полей, добавляемых данной стратегией.
*/
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn() = 0;
    };

/**
* @brief Абстрактный класс, представляющий интерфейс стратегии редактирования поля "type".
*/
    class ModifyTypeField: public AddNewFieldStrategy
    {
    public:
        ModifyTypeField(){}
/**
* @brief Абстрактный метод. Исполнение стратегии.
* @param dstFeature Запись, поле которой подвергается редактированию
* @param srcFeature Запись-источник, данных на основании которых редактируются значения полей
*/
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature) = 0;
        virtual std::vector<OGRFieldDefn*> GetOGRFieldDefn();
    };

/**
* @brief Класс, представляющий стратегию редактирования поля type объектов BOYCAR, BOYLAT, BOYSPP, BOYISD, BOYSAW на основании данных поля BOYSHP.
* BOYSHP - форма буя
*/
    class BOYSpecify: public ModifyTypeField
    {
    public:
        BOYSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Класс, представляющий стратегию редактирования поля type на основании данных поля BCNSHP.
* BCNSHP - форма знака
*/
    class BCNLATSpecify: public ModifyTypeField
    {
    public:
        BCNLATSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Класс, представляющий стратегию редактирования поля type на основании данных полей BCNSHP и CATSPM.
* BCNSHP - форма знака
* CATSPM - Категория знака специального назначения
*/
    class BCNSPPSpecify: public ModifyTypeField
    {
    public:
        BCNSPPSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Класс, представляющий стратегию редактирования поля type на основании полей SECTR1 и SECTR2.
*/
    class SECTRSpecify: public ModifyTypeField
    {
    public:
        SECTRSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля COLOUR.
*/
    class COLOURSpecify: public ModifyTypeField
    {
    public:
        COLOURSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля наличия значения в поле ORIENT.
*/
    class ORIENTPresenceSpecify: public ModifyTypeField
    {
    public:
        ORIENTPresenceSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля TOPSHP - форма топовой фигуры.
*/
    class TOPSHPSpecify: public ModifyTypeField
    {
    public:
        TOPSHPSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля CONVIS - визуально приметный.
*/
    class CONVISSpecify: public ModifyTypeField
    {
    public:
        CONVISSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля CATLMK - ктегория берегового ориентира.
*/
    class CATLMKSpecify: public ModifyTypeField
    {
    public:
        CATLMKSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля CATNAV - ктегория навигационного створа.
*/
    class CATNAVSpecify: public ModifyTypeField
    {
    public:
        CATNAVSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля TRAFIC - поток движения.
*/
    class TRAFICSpecify: public ModifyTypeField
    {
    public:
        TRAFICSpecify(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };
/**
* @brief Класс, представляющий стратегию редактирования поля type на основании поля CATSLC - категория берогового сооружения.
*/
    class CATSLCSpecify: public ModifyTypeField
    {
    public:
        CATSLCSpecify(){}
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
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию о значение вертикального просвета, на основе значения поля VERCLR - Вертикальный просвет.
*/
    class AddVERCLRSignatures: public AddSignatures
    {
    public:
        AddVERCLRSignatures(){}
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
* @brief Класс-стратегия для добавления полей, содержащих подписи на английском и русском языках name_en и name_ru.
* Подписи содержат информацию о значение изобаты, на основе значения поля VALDCO - значение изобаты.
*/
    class AddVALDCOSignatures: public AddSignatures
    {
    public:
        AddVALDCOSignatures(){}
        virtual void Execute(OGRFeature* dstFeature, OGRFeature* srcFeature);
    };

/**
* @brief Абстрактный класс, представляющий интерфейс стратегии добавления нового слоя в БД.
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
* @param poDstDatasource Источник данных, где будет создан новый слой
*/
        void Create(OGRDataSource *poDstDatasource, OGRSpatialReference* spatRef);

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
* @brief Класс-стратегия добавления нового слоя в БД, основанный на принципе копирования геометрий всех объектов из слоев-источников.
* @code
    const char *pszDstDriverName = "PostgreSQL";
    poDstDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
                pszDstDriverName );

    OGRDataSource *poDstDatasource = NULL;
    poDstDatasource = poDstDriver->Open(PG:"dbname='dbname' user='postgres' password='tochange'");

    layerName = "anchor_parking_plg";
    geomType = wkbPolygon;

    layerWithCopyRules.SrcLayer_ = poSrcDatasource->GetLayerByName("ACHARE");
    layersWithCopyRules.push_back(layerWithCopyRules);

    NAVI2PG::CreateLayerStrategy* cfs = new NAVI2PG::CopyFeaturesStrategy(layerName, geomType, layersWithCopyRules, false);
    cfs->Create(poDstDatasource)
* @endcode
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
              AddTypeFieldFlag_(addTypeField),
              SrcLayers_(srcLayersWithRules)
        {
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
* @brief Класс-стратегия добавления слоя, содержащего объекты "Выделение линейных" из классификатора ГИС Панорама.
* Данные формируются на основании слоев "Edge" и "$LINES"
*/
    class CreateSystemLinesStrategy : public CreateLayerStrategy
    {
        OGRLayer* EdgeLayer_;
        OGRLayer* LinesLayer_;
        OGRLayer* ConnectedNodeLayer_;
    public:
/**
* @brief Конструктор.
* @param layerName Имя нового слоя
* @param edgeLayer Слой "Edge"
* @param linesLayer Слой "$LINES"
* @param connectedNodeLayer Слой "ConnectedNode"
*/
        CreateSystemLinesStrategy(const CPLString& layerName, OGRLayer* edgeLayer, OGRLayer* linesLayer, OGRLayer* connectedNodeLayer)
            : CreateLayerStrategy(layerName, wkbLineString),
              EdgeLayer_(edgeLayer),
              LinesLayer_(linesLayer),
              ConnectedNodeLayer_(connectedNodeLayer)
        {

        }

    private:
        std::vector<int> getSubLinesRCIDs(const CPLString& lineDescription);
        void getSubLine(const int subLineRCID, OGRLineString* resultSubLine);
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

/**
 * @brief Копирование файла-шаблона конфигурации MapServer с установкой новых значений некоторых переменных
 *
 * @param mapConfigTemplateFilename - полный путь до файла-шаблона конфигурации MapServer
 * @param mapConfigFilename - полный путь до нового файла конфигурации MapServer
 * @param newExtent - экстент, который должен быть установлен в файле конфигурации MapServer
 */
    void CopyConfigFile(
            const char  *mapConfigTemplateFilename,
            const char  *mapConfigFilename,
            OGREnvelope newExtent,
            const char  *pszPGConnectionString);
}
#endif // NAVI2PG_H
