#include "svgitem.h"

#include <algorithm>
#include <stdexcept>

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
      auto it = std::find(parent_->children_.begin(), parent_->children_.end(), const_cast<SVGItem*>(this));
      if(it != parent_->children_.end())
      {
         return std::distance(parent_->children_.begin(), it);
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
