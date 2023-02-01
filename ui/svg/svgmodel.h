#ifndef SVG_MODEL_H
#define SVG_MODEL_H

#include "svgitem.h"

#include <QAbstractItemModel>

class QDomDocument;
class SVGItem;

class SVGModel : public QAbstractItemModel
{
   Q_OBJECT
public:
   SVGModel(const QDomDocument& svg, QWidget* parent = nullptr);

   QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex& index) const override;
   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant data(const QModelIndex& index, int role) const override;
   Qt::ItemFlags flags(const QModelIndex& index) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
   const SVGItem* itemFromIndex(const QModelIndex& index) const;

private:
   SVGItem root_ = SVGItem(SVGElementType::Root);
};

#endif // SVG_MODEL_H