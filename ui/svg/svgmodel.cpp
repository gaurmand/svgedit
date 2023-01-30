#include "svgmodel.h"

#include <QWidget>

#include <algorithm>

int SVGItem::numChildren() const
{
   return children_.size();
}

SVGItem* SVGItem::childAt(int row)
{
   return children_.at(row);
}

const SVGItem* SVGItem::childAt(int row) const
{
   return children_.at(row);
}

int SVGItem::row() const
{
   if (parent_)
   {
      auto res = std::find(parent_->children_.cbegin(), parent_->children_.cend(), const_cast<SVGItem*>(this));
      if(res != parent_->children_.cend())
      {
         return std::distance(parent_->children_.cbegin(), res);
      }

      throw std::runtime_error("SVGItem is not a child of its parent");
   }

   return 0;
}

SVGItem* SVGItem::appendChild(SVGElementType type)
{
   children_.push_back(new SVGItem(type, this));
   return children_.back();
}


SVGModel::SVGModel(const QDomDocument& svg, QWidget* parent) : QAbstractItemModel(parent)
{

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
   if (role != Qt::DisplayRole)
   {
      return QVariant();
   }

   const SVGItem* item = itemFromIndex(index);
   assert(item != nullptr);

   switch (item->type())
   {
      case SVGElementType::Root:
         return tr("svg");
      case SVGElementType::Rect:
         return tr("rect");
      case SVGElementType::Circle:
         return tr("circle");
      case SVGElementType::Ellipse:
         return tr("ellipse");
      case SVGElementType::Text:
         return tr("text");
      case SVGElementType::Line:
         return tr("line");
      case SVGElementType::PolyLine:
         return tr("polyline");
      case SVGElementType::None:
      default:
         return QVariant();
   }
}

Qt::ItemFlags SVGModel::flags(const QModelIndex& index) const
{
   Q_UNUSED(index);
   return Qt::ItemIsSelectable;
}

const SVGItem* SVGModel::itemFromIndex(const QModelIndex& index) const
{
   return index.isValid() ? static_cast<const SVGItem*>(index.constInternalPointer()) : &root_;
}

