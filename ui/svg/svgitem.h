#ifndef SVG_ITEM_H
#define SVG_ITEM_H

#include <vector>

#include <QString>
#include <QHash>

class QDomElement;

enum class SVGElementType
{
   unknown,
   circle,
   ellipse,
   g,
   line,
   path,
   polyline,
   polygon,
   rect,
   svg,
   text,
};

class SVGItem
{
public:
   SVGItem() {}
   SVGItem(SVGElementType type) : type_(type) {}
   SVGItem(SVGElementType type, SVGItem* parent) : type_(type), parent_(parent) {}
   virtual ~SVGItem();

   SVGElementType type() const {return type_; }
   int numChildren() const;
   const SVGItem* childAt(int row) const;
   const SVGItem* parent() const { return parent_; }
   int row() const;

   SVGItem* childAt(int row);
   SVGItem* parent() { return parent_; }
   SVGItem* appendChild(SVGElementType type);

   QString attribute(const QString& name) const;
   bool hasAttribute(const QString& name) const;
   void setAttribute(const QString& name, const QString& value);
   void clearAttribtues();

   static SVGElementType elementTypeFromString(const QString& tagName);
   static QString stringFromElementType(const SVGElementType type);

private:
   SVGElementType type_ = SVGElementType::unknown;
   QHash<QString, QString> attributes_;
   std::vector<SVGItem*> children_;
   SVGItem* parent_ = nullptr;
};

#endif // SVG_ITEM_H