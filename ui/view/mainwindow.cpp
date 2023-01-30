#include "mainwindow.h"
#include "editview.h"
#include "../svg/svgparser.h"

#include <QVBoxLayout>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   setCentralWidget(new EditView);

   auto* open = new QAction(tr("Open SVG file"), this);
   open->setShortcut(QKeySequence::Open);
   connect(open, &QAction::triggered, this, &MainWindow::openSVGFile);
   addAction(open);
}

void MainWindow::openSVGFile()
{
   QString filename =  QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("Images (*.svg)"));

   if (filename.isEmpty())
      return;

   QFile file(filename);
   if (!file.open(QFile::ReadOnly | QFile::Text)) 
   {
      QMessageBox::warning(this, tr("QXmlStream Bookmarks"), tr("Cannot open file %1:\n%2.")
      .arg(QDir::toNativeSeparators(filename), file.errorString()));
      return;
   }

   std::unique_ptr<SVGModel> svgModel = SVG::parse(&file);
}

