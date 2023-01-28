#include "mainwindow.h"
#include "editview.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   setCentralWidget(new EditView);
}
