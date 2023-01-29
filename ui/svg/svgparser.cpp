#include "svgparser.h"

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

void parse(QIODevice* device)
{
   QDomDocument doc;
   doc.setContent(device, false);

   printDOM(doc.documentElement());
}

}

