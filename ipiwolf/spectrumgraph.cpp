#include "spectrumgraph.h"

SpectrumGraph::SpectrumGraph(QWidget *parent) : QCustomPlot(parent)
{
    xAxis->setTickLabelRotation(60);
    xAxis->setSubTickCount(0);
    xAxis->setTickLength(0, 4);
    xAxis->grid()->setVisible(true);
    xAxis->setRange(0, 8);
    xAxis->setLabel("");

    // prepare y axis:
    yAxis->setRange(0, 12.1);
    yAxis->setPadding(5); // a bit more space to the left border
    yAxis->setLabel("Amplitude");
    yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    yAxis->grid()->setSubGridPen(gridPen);

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

void SpectrumGraph::setSpectrum(SpectrumPtr histo) {
    clearGraphs();

    addGraph();

    graph()->setPen(QPen(Qt::blue)); // line color blue for first graph
    graph()->setAntialiasedFill(false);
    graph()->setLineStyle(QCPGraph::lsStepCenter);

    QVector<double> ticks(histo->getEasyTab().size());
    QVector<double> data(histo->getEasyTab().size());
    for(int i=0; i<histo->getEasyTab().size(); i++) {
        ticks[i] = histo->getEasyTab()[i].frequency;
        data[i] = histo->getEasyTab()[i].amplitude;
    }
    graph()->setData(ticks, data);
}

SpectrumGraph::~SpectrumGraph()
{

}

