#ifndef GRAPH_H
#define GRAPH_H

#include "qcustomplot.h"
#include "datafile.h"

class Graph : public QCustomPlot
{
    Q_OBJECT
public:
    Graph(QWidget * parent = NULL);
    void setDataFile(DataFile * data);
    ~Graph();
};

#endif // GRAPH_H
