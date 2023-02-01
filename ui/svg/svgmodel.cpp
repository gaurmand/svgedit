#include "svgmodel.h"

#include <QWidget>
#include <QDomDocument>

namespace
{

void constructModel(const QDomNode& DOMRoot, SVGItem* modelRoot)
{
   QDomNode child = DOMRoot.firstChild();
   while (!child.isNull())
   {
      QDomElement childElem = child.toElement();
      if (!childElem.isNull())
      {
         SVGItem* childItem = modelRoot->appendChild(SVGItem::elementTypeFromString(childElem.tagName()));
         constructModel(child, childItem);
      }
      child = child.nextSibling();
   }
}

}

SVGModel::SVGModel(const QDomDocument& svg, QWidget* parent) : QAbstractItemModel(parent)
{
   constructModel(svg.documentElement(), &root_);
}

QModelIndex SVGModel::index(int row, int column, const QModelIndex& parent) const
{
   Q_UNUSED(column);

   if (!hasIndex(row, column, parent))
   {
      return QModelIndex();
   }

   const SVGItem* parentItem = itemFromIndex(parent);
   assert(parentItem != nullptr);

   const SVGItem* item = parentItem->childAt(row);
   assert(item != nullptr);

   return createIndex(row, 0, item);
}

QModelIndex SVGModel::parent(const QModelIndex& index) const 
{
   if (!index.isValid())
   {
      return QModelIndex();
   }

   const SVGItem* item = itemFromIndex(index);
   assert(item != nullptr);

   const SVGItem* parentItem = item->parent();
   assert(parentItem != nullptr);

   if (parentItem == &root_)
   {
      return QModelIndex();
   }

   return createIndex(parentItem->row(), 0, item); 
}

int SVGModel::rowCount(const QModelIndex& parent) const
{
   const SVGItem* parentItem = itemFromIndex(parent);
   assert(parentItem != nullptr);

   return parentItem->numChildren();
}

int SVGModel::columnCount(const QModelIndex& parent) const
{
   Q_UNUSED(parent);
   return 1;
}

QVariant SVGModel::data(const QModelIndex& index, int role) const 
{
   if (!index.isValid())
   {
      return QVariant();
   }

   if (role != Qt::DisplayRole)
   {
      return QVariant();
   }

   const SVGItem* item = itemFromIndex(index);
   assert(item != nullptr);

   return SVGItem::stringFromElementType(item->type());
}

Qt::ItemFlags SVGModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

   return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SVGModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
   {
      return tr("SVG Element");
   }

   return QVariant();
}

const SVGItem* SVGModel::itemFromIndex(const QModelIndex& index) const
{
   return index.isValid() ? static_cast<const SVGItem*>(index.constInternalPointer()) : &root_;
}

