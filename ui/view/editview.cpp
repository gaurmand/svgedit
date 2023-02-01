#include "editview.h"
#include "../svg/svgmodel.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView> 

EditView::EditView(QWidget *parent) : QWidget(parent)
{
   setLayout(new QVBoxLayout);
   
   svgTreeView_ = new QTreeView(this);
   svgTreeView_->setRootIsDecorated(false);
   layout()->addWidget(svgTreeView_);
}

void EditView::setSVGModel(SVGModel* model)
{
   svgTreeView_->setModel(model);
}
