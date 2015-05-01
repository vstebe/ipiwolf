#ifndef HISTOGRAMGRAPH_H
#define HISTOGRAMGRAPH_H

#include "histogram.h"
#include "qcustomplot.h"

class HistogramGraph : public QCustomPlot
{
public:
    HistogramGraph(QWidget * parent = NULL);
    void setHistogram(HistogramPtr histo);
    ~HistogramGraph();
};

#endif // HISTOGRAMGRAPH_H
