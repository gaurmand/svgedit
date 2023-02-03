#include "svgmodel.h"

#include <QWidget>
#include <QDomDocument>
#include <QDebug>

namespace
{

void setAttributesFromElem(const QDomElement& elem, SVGItem* modelItem)
{
   const QDomNamedNodeMap attributes = elem.attributes();
   for (int i = 0; i < attributes.length(); ++i)
   {
      QDomAttr attr = attributes.item(i).toAttr();
      if (!attr.isNull())
      {
         modelItem->setAttribute(attr.name(), attr.value());
      }
   }
}

void constructTreeModel(const QDomElement& elem, SVGItem* modelItem)
{
   QDomElement child = elem.firstChildElement();
   while (!child.isNull())
   {
      SVGItem* childItem = modelItem->appendChild(SVGItem::elementTypeFromString(child.tagName()));
      setAttributesFromElem(child, childItem);
      constructTreeModel(child, childItem);
      child = child.nextSiblingElement();
   }
}

void printTree(SVGItem* item, int depth = 0)
{
   QString indent(2*depth, ' ');
   qDebug().nospace().noquote() << indent << SVGItem::stringFromElementType(item->type());
   for(int i = 0; i < item->numChildren(); ++i)
   {
      printTree(item->childAt(i), depth + 1);
   }
}

}

SVGModel::SVGModel(const QDomDocument& svg, QWidget* parent) : QAbstractItemModel(parent)
{
   SVGItem* svgRoot = root_->appendChild(SVGElementType::svg);
   constructTreeModel(svg.documentElement(), svgRoot);
   printTree(root_.get());
}

QModelIndex SVGModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!hasIndex(row, column, parent))
   {
      return QModelIndex();
   }

   const SVGItem* parentItem = itemFromIndex(parent);
   assert(parentItem != nullptr);

   const SVGItem* item = parentItem->childAt(row);
   assert(item != nullptr);

   return createIndex(row, column, item);
}

QModelIndex SVGModel::parent(const QModelIndex& index) const 
{
   const SVGItem* item = itemFromIndex(index);
   assert(item != nullptr);

   const SVGItem* parentItem = item->parent();
   if (parentItem == nullptr || parentItem == root_.get())
   {
      return QModelIndex();
   }

   return createIndex(parentItem->row(), 0, parentItem); 
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
   return index.isValid() ? static_cast<const SVGItem*>(index.constInternalPointer()) : root_.get();
}

