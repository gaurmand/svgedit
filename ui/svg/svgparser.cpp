#include "svgparser.h"
#include "svgmodel.h"

#include <QDomDocument>
#include <QDebug> 

namespace
{

void printDOM(const QDomNode& root)
{
   qDebug() << root.nodeName();

   QDomNode child = root.firstChild();
   while (!child.isNull())
   {
      printDOM(child);
      child = child.nextSibling();
   }
}

}


namespace SVG
{

std::unique_ptr<SVGModel> parse(QIODevice* svgDevice)
{
   QDomDocument doc;
   doc.setContent(svgDevice, false);

   //printDOM(doc.documentElement());

   return std::make_unique<SVGModel>(doc);
}

}
