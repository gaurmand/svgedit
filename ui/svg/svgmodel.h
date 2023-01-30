#ifndef SVG_MODEL_H
#define SVG_MODEL_H

#include <QAbstractItemModel>

#include <vector>

class QDomDocument;

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
   SVGItem* childAt(int row);
   const SVGItem* childAt(int row) const;
   SVGItem* parent() { return parent_; }
   const SVGItem* parent() const { return parent_; }
   int row() const;

   SVGItem* appendChild(SVGElementType type);

private:
   SVGElementType type_ = SVGElementType::None;
   std::vector<SVGItem*> children_;
   SVGItem* parent_ = nullptr;
};

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

private:
   const SVGItem* itemFromIndex(const QModelIndex& index) const;

private:
   SVGItem root_ = SVGItem(SVGElementType::Root);
};

#endif // SVG_MODEL_H