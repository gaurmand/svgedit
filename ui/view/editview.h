#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>

class QTreeView;
class SVGModel;

class EditView : public QWidget
{
   Q_OBJECT
public:
   EditView(QWidget *parent = nullptr);

public slots:
   void setSVGModel(SVGModel* model);

private:
   QAction* open_          = nullptr;
   QTreeView* svgTreeView_ = nullptr;
};

#endif // EDITVIEW_H