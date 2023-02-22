#pragma once

#include <scwx/common/products.hpp>
#include <scwx/qt/config/radar_site.hpp>
#include <scwx/qt/types/radar_product_record.hpp>

#include <chrono>
#include <memory>

#include <QMapLibreGL/QMapLibreGL>

#include <QOpenGLWidget>
#include <QPropertyAnimation>
#include <QtGlobal>

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

namespace scwx
{
namespace qt
{
namespace map
{

class MapWidgetImpl;

class MapWidget : public QOpenGLWidget
{
   Q_OBJECT

public:
   explicit MapWidget(const QMapLibreGL::Settings&);
   ~MapWidget();

   common::Level3ProductCategoryMap   GetAvailableLevel3Categories();
   float                              GetElevation() const;
   std::vector<float>                 GetElevationCuts() const;
   std::vector<std::string>           GetLevel3Products();
   common::RadarProductGroup          GetRadarProductGroup() const;
   std::string                        GetRadarProductName() const;
   std::shared_ptr<config::RadarSite> GetRadarSite() const;
   uint16_t                           GetVcp() const;

   void SelectElevation(float elevation);
   void SelectRadarProduct(common::RadarProductGroup group,
                           const std::string&        product,
                           int16_t                   productCode);
   void SelectRadarProduct(std::shared_ptr<types::RadarProductRecord> record);

   /**
    * @brief Selects a radar site.
    *
    * @param [in] radarSite ID of the requested radar site
    * @param [in] updateCoordinates Whether to update the map coordinates to the
    * requested radar site location. Default is true.
    */
   void SelectRadarSite(const std::string& id, bool updateCoordinates = true);

   /**
    * @brief Selects a radar site.
    *
    * @param [in] radarSite Shared pointer to the requested radar site
    * @param [in] updateCoordinates Whether to update the map coordinates to the
    * requested radar site location. Default is true.
    */
   void SelectRadarSite(std::shared_ptr<config::RadarSite> radarSite,
                        bool updateCoordinates = true);

   void SetActive(bool isActive);
   void SetAutoRefresh(bool enabled);

   /**
    * @brief Sets the current map location.
    *
    * @param [in] latitude Latitude in degrees
    * @param [in] longitude Longitude in degrees
    * @param [in] updateRadarSite Whether to update the selected radar site to
    * the closest WSR-88D site. Default is false.
    */
   void SetMapLocation(double latitude,
                       double longitude,
                       bool   updateRadarSite = false);
   void SetMapParameters(double latitude,
                         double longitude,
                         double zoom,
                         double bearing,
                         double pitch);

private:
   void  changeStyle();
   qreal pixelRatio();

   // QWidget implementation.
   void keyPressEvent(QKeyEvent* ev) override final;
   void mousePressEvent(QMouseEvent* ev) override final;
   void mouseMoveEvent(QMouseEvent* ev) override final;
   void wheelEvent(QWheelEvent* ev) override final;

   // QOpenGLWidget implementation.
   void initializeGL() override final;
   void paintGL() override final;

   void AddLayers();

   std::unique_ptr<MapWidgetImpl> p;

   friend class MapWidgetImpl;

private slots:
   void mapChanged(QMapLibreGL::Map::MapChange);

signals:
   void Level3ProductsChanged();
   void MapParametersChanged(double latitude,
                             double longitude,
                             double zoom,
                             double bearing,
                             double pitch);
   void RadarSweepUpdated();
};

} // namespace map
} // namespace qt
} // namespace scwx
