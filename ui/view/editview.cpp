#include "editview.h"

#include <QLabel>
#include <QVBoxLayout>

EditView::EditView(QWidget *parent) : QWidget(parent)
{
   setLayout(new QVBoxLayout);
   layout()->addWidget(new QLabel("hello"));
}
