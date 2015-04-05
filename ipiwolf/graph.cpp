#include "graph.h"


DataFile * test() {
    QFile file("/home/vincent/accel/accel/wacu100_Loups_cc_ACC-15_05_2014-08_00_01--03_07_2014-14_35_15-50Hz.txt");
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            QTextStream in(&file);
            //QVector<double> x, y;
            DataFile * data = new DataFile();
            int t = 0;
            int d = 0;
            while (!in.atEnd())
            {
                QString line = in.readLine(); //read one line at a time
                if(t == 0) {

                    QStringList lstLine = line.split('\t');

                    data->push_back(Point(lstLine[0].toDouble(), 0, 0));

                }
                d++;
                  t = (++t==5) ? 0 : t;
                if(data->size() == 1000000)
                    break;
            }
            return data;
}

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



    setDataFile(test());
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


void Graph::setDataFile(DataFile *data) {
    _dataFile = data;
    update();
}

void Graph::update() {
    int zap = 1;
    QVector<double> x(_dataFile->size() / zap);
    clearGraphs();
    for(int i=0; i<x.size(); i++) {
        x[i] = i*zap;
    }
    if(_axeX) {

        QVector<double> y(_dataFile->size() / zap);
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i*zap).x;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::blue)); // line color blue for first graph
        graph->rescaleAxes();
    }
    if(_axeY) {

        QVector<double> y(_dataFile->size() / zap);
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i*zap).y;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::red)); // line color blue for first graph
        graph->rescaleAxes();
    }
    if(_axeZ) {

        QVector<double> y(_dataFile->size() / zap);
        for(int i=0; i<x.size(); i++) {
            y[i] = _dataFile->at(i*zap).z;
        }
        QCPGraph * graph = addGraph();
        graph->setData(x, y);
        graph->setPen(QPen(Qt::green)); // line color blue for first graph
        graph->rescaleAxes();
    }

    QCustomPlot::update();
}


void Graph::setAxes(bool axeX, bool axeY, bool axeZ) {
    _axeX = axeX;
    _axeY = axeY;
    _axeZ = axeZ;
}
