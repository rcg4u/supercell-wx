#pragma once

#include <scwx/qt/types/text_event_key.hpp>
#include <scwx/common/geographic.hpp>

#include <memory>

#include <QAbstractTableModel>

namespace scwx
{
namespace qt
{
namespace model
{

class PlacefileModelImpl;

class PlacefileModel : public QAbstractTableModel
{
public:
   enum class Column : int
   {
      Enabled     = 0,
      Thresholds  = 1,
      Url         = 2,
      Description = 3
   };

   explicit PlacefileModel(QObject* parent = nullptr);
   ~PlacefileModel();

   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;

   Qt::ItemFlags flags(const QModelIndex& index) const override;

   QVariant data(const QModelIndex& index,
                 int                role = Qt::DisplayRole) const override;
   QVariant headerData(int             section,
                       Qt::Orientation orientation,
                       int             role = Qt::DisplayRole) const override;

public slots:
   void HandlePlacefileUpdate(const std::string& name);

private:
   friend class PlacefileModelImpl;
   std::unique_ptr<PlacefileModelImpl> p;
};

} // namespace model
} // namespace qt
} // namespace scwx
