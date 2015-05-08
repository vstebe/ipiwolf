#ifndef GRAPH_H
#define GRAPH_H

#include "qcustomplot.h"
#include "datafile.h"

class Graph : public QCustomPlot
{
    Q_OBJECT
public:
    Graph(QWidget * parent = NULL);
    void setDataFile(DataFilePtr data);
    void setAxes(bool axeX, bool axeY, bool axeZ, bool axeXYZ);
    void update();
    QCPGraph * addGraph(QCPAxis *keyAxis = NULL, QCPAxis *valueAxis = NULL);
    ~Graph();

protected:
    DataFilePtr _dataFile;
    bool _axeX;
    bool _axeY;
    bool _axeZ;
    bool _axeXYZ;
};

#endif // GRAPH_H
