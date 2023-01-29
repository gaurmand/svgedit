#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../svg/svgparser.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   MainWindow(QWidget* parent = nullptr);

public slots:
   void openSVGFile();
};

#endif // MAINWINDOW_H