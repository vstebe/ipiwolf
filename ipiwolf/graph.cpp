#include "graph.h"


Graph::Graph(QWidget * parent) : QCustomPlot(parent)
{
    _axeX = true;
    _axeY = true;
    _axeZ = true;

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    xAxis2->setVisible(true);
    xAxis2->setTickLabels(false);
    yAxis2->setVisible(true);
    yAxis2->setTickLabels(false);


    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    setNoAntialiasingOnDrag(true);

    setNotAntialiasedElements(QCP::aeAll);

    // setup legend:
    legend->setVisible(true);
    axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    legend->setFont(legendFont);
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

Graph::~Graph()
{

}

QCPGraph * Graph::addGraph(QCPAxis *keyAxis, QCPAxis *valueAxis) {
    QCPGraph * graph = QCustomPlot::addGraph(keyAxis, valueAxis);
    graph->setPen(QPen(Qt::blue)); // line color blue for first graph
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setAdaptiveSampling(true);
    graph->setAntialiasedFill(false);
    return graph;
}


void Graph::setDataFile(DataFilePtr data) {
    _dataFile = data;
    update();
}

void Graph::update() {
    QVector<double> x(_dataFile->size());
    clearGraphs();
    for(int i=0; i<x.size(); i++) {
        x[i] = ((float) i) / _dataFile->getSamplingRate();
    }
    if(_axeX) {

        QVector<double> y(_dataFile->size());
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i).x;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::red)); // line color blue for first graph
        graph->setName("X");
    }
    if(_axeY) {

        QVector<double> y(_dataFile->size());
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i).y;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::green)); // line color blue for first graph
        graph->setName("Y");
    }
    if(_axeZ) {

        QVector<double> y(_dataFile->size());
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i).z;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::blue)); // line color blue for first graph
        graph->setName("Z");
    }

    if(_axeXYZ) {

        QVector<double> y(_dataFile->size());
        for(int i=0; i<x.size(); i++) {
            y[i] = (*_dataFile)[i].getXYZ();
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(QColor(251, 186,24))); // line color blue for first graph
        graph->setName("XYZ");
    }

    QCustomPlot::update();
}


void Graph::setAxes(bool axeX, bool axeY, bool axeZ, bool axeXYZ) {
    _axeX = axeX;
    _axeY = axeY;
    _axeZ = axeZ;
    _axeXYZ = axeXYZ;
    update();
}
