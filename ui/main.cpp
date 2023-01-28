#include "view/mainwindow.h"

#include <QApplication>

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.setWindowTitle("svgedit");
   w.show();
   return a.exec();
}
