#ifndef EDITVIEW_H
#define EDITVIEW_H

#include <QWidget>

class EditView : public QWidget
{
   Q_OBJECT
public:
   EditView(QWidget *parent = nullptr);

private:
   QAction* open_ = nullptr;
};

#endif // EDITVIEW_H