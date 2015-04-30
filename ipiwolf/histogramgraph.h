#ifndef HISTOGRAMGRAPH_H
#define HISTOGRAMGRAPH_H

#include "datafile.h"
#include "qcustomplot.h"

class HistogramGraph : public QCustomPlot
{
public:
    HistogramGraph(QWidget * parent = NULL);
    void setDataFile(DataFilePtr dataFile);
    ~HistogramGraph();
};

#endif // HISTOGRAMGRAPH_H
