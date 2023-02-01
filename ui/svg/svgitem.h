#ifndef SVG_ITEM_H
#define SVG_ITEM_H

#include <vector>

enum class SVGElementType
{
   None,
   Root,
   Rect,
   Circle,
   Ellipse,
   Text,
   Line,
   PolyLine
};

class SVGItem
{
public:
   SVGItem() {}
   SVGItem(SVGElementType type) : type_(type) {}
   SVGItem(SVGElementType type, SVGItem* parent) : type_(type), parent_(parent) {}

   SVGElementType type() const {return type_; }
   int numChildren() const;
   const SVGItem* childAt(int row) const;
   const SVGItem* parent() const { return parent_; }
   int row() const;

   SVGItem* childAt(int row);
   SVGItem* parent() { return parent_; }
   SVGItem* appendChild(SVGElementType type);

private:
   SVGElementType type_ = SVGElementType::None;
   std::vector<SVGItem*> children_;
   SVGItem* parent_ = nullptr;
};

#endif // SVG_ITEM_H