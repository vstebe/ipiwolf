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
    void setAxes(bool axeX, bool axeY, bool axeZ);
    void update();
    QCPGraph * addGraph(QCPAxis *keyAxis = NULL, QCPAxis *valueAxis = NULL);
    ~Graph();

protected:
    DataFile * _dataFile;
    bool _axeX;
    bool _axeY;
    bool _axeZ;
};

#endif // GRAPH_H
