#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../svg/svgmodel.h"

#include <QMainWindow>

class EditView;

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   MainWindow(QWidget* parent = nullptr);

public slots:
   void openSVGFile();

private:
   EditView* editor_                = nullptr;
   std::unique_ptr<SVGModel> model_ = nullptr;
};

#endif // MAINWINDOW_H