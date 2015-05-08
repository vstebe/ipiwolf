#ifndef HISTOGRAMGRAPH_H
#define HISTOGRAMGRAPH_H

#include "spectrum.h"
#include "qcustomplot.h"

class SpectrumGraph : public QCustomPlot
{
public:
    SpectrumGraph(QWidget * parent = NULL);
    void setSpectrum(MultiSpectrum mhisto);

    ~SpectrumGraph();
};

#endif // HISTOGRAMGRAPH_H
