#ifndef SVGPARSER_H
#define SVGPARSER_H

#include "svgmodel.h"

#include <QObject>

#include <memory>

class QIODevice;

namespace SVG
{
   std::unique_ptr<SVGModel> parse(QIODevice* svgDevice);
}

#endif // SVGPARSER_H