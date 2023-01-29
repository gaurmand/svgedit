#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <QObject>
#include <QDomDocument>

class QIODevice;

namespace SVG
{
   void parse(QIODevice* device);
}

#endif // SVGPARSER_H