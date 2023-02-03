#include "svgitem.h"

#include <algorithm>
#include <stdexcept>

SVGItem::~SVGItem()
{
   for (int i = 0; i < children_.size(); ++i)
   {
      delete children_.at(i);
   }
}

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

QString SVGItem::attribute(const QString& name) const
{
   auto it = attributes_.find(name);
   if (it != attributes_.end())
   {
      return *it;
   }
   else
   {
      throw std::out_of_range(QString("SVGItem does not contain attribute %1").arg(name).toStdString());
   }
}

bool SVGItem::hasAttribute(const QString& name) const
{
   return attributes_.contains(name);
}

void SVGItem::setAttribute(const QString& name, const QString& value)
{
   attributes_.insert(name, value);
}

void SVGItem::clearAttribtues()
{
   attributes_.clear();
}

SVGElementType SVGItem::elementTypeFromString(const QString& tagName)
{
   if (tagName == "circle")
      return SVGElementType::circle;
   else if (tagName == "ellipse")
      return SVGElementType::ellipse;
   else if (tagName == "g")
      return SVGElementType::g;
   else if (tagName == "line")
      return SVGElementType::line;
   else if (tagName == "path")
      return SVGElementType::path;
   else if (tagName == "polyline")
      return SVGElementType::polyline;
   else if (tagName == "polygon")
      return SVGElementType::polygon;
   else if (tagName == "rect")
      return SVGElementType::rect;
   else if (tagName == "svg")
      return SVGElementType::svg;
   else if (tagName == "text")
      return SVGElementType::text;
   else
      return SVGElementType::unknown;
}

QString SVGItem::stringFromElementType(const SVGElementType type)
{
   switch (type)
   {
      case SVGElementType::circle:
         return "circle";
      case SVGElementType::ellipse:
         return "ellipse";
      case SVGElementType::g:
         return "g";
      case SVGElementType::line:
         return "line";
      case SVGElementType::path:
         return "path";
      case SVGElementType::polyline:
         return "polyline";
      case SVGElementType::polygon:
         return "polygon";
      case SVGElementType::rect:
         return "rect";
      case SVGElementType::svg:
         return "svg";
      case SVGElementType::text:
         return "text";
      case SVGElementType::unknown:
      default:
         return "unknown";
   }
}
