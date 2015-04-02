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
    addGraph();
    graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue

    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    xAxis2->setVisible(true);
    xAxis2->setTickLabels(false);
    yAxis2->setVisible(true);
    yAxis2->setTickLabels(false);
    graph(0)->setLineStyle(QCPGraph::lsLine);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    setNoAntialiasingOnDrag(true);

    setNotAntialiasedElements(QCP::aeAll);

    graph(0)->setAdaptiveSampling(true);

    graph(0)->setAntialiasedFill(false);

    setDataFile(test());
}

Graph::~Graph()
{

}


void Graph::setDataFile(DataFile *data) {

    int zap = 1;

    QVector<double> x(data->size() / zap);
    QVector<double> y(data->size() / zap);

    for(int i=0; i<x.size(); i++) {
        x[i] = i*zap;
        y[i] = data->at(i*zap).x;
    }

    graph(0)->setData(x, y);
    //customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
}

