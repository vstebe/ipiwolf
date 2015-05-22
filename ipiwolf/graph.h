#ifndef GRAPH_H
#define GRAPH_H

#include "qcustomplot.h"
#include "datafile.h"

/**
 * @brief Class used for displaying the graph of a signal
 */
class Graph : public QCustomPlot
{
    Q_OBJECT
public:
    /**
     * @brief Constructs an empty graph
     * @param parent QWidget parent
     */
    Graph(QWidget * parent = NULL);

    /**
     * @brief Sets the signal to display
     * @param data SharedPointer of the datafile to load
     */
    void setDataFile(DataFilePtr data);

    /**
     * @brief Sets the axis of the signal which must be displayed
     * @param axeX X axis of the signal
     * @param axeY Y axis of the signal
     * @param axeZ Z axis of the signal
     * @param axeXYZ magnitude of the signal
     */
    void setAxes(bool axeX, bool axeY, bool axeZ, bool axeXYZ);

    /**
     * @brief Updates the graph with the current data file and axis info.
     */
    void update();

    ~Graph();

protected:
    QCPGraph * addGraph(QCPAxis *keyAxis = NULL, QCPAxis *valueAxis = NULL);

    DataFilePtr _dataFile;
    bool _axeX;
    bool _axeY;
    bool _axeZ;
    bool _axeXYZ;
};

#endif // GRAPH_H
