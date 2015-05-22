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

void SpectrumGraph::setSpectrum(MultiSpectrum mhisto) {
    clearGraphs();

    if(!mhisto.x.isNull()) {
        SpectrumPtr histo = mhisto.x;

        addGraph();

        graph()->setPen(QPen(Qt::red)); // line color blue for first graph
        graph()->setAntialiasedFill(false);
        graph()->setLineStyle(QCPGraph::lsStepCenter);
        graph()->setName("X");

        QVector<double> ticks(histo->getEasyTab().size());
        QVector<double> data(histo->getEasyTab().size());
        for(int i=0; i<histo->getEasyTab().size(); i++) {
            ticks[i] = histo->getEasyTab()[i].frequency;
            data[i] = histo->getEasyTab()[i].amplitude;
        }
        graph()->setData(ticks, data);
    }

    if(!mhisto.y.isNull()) {
        SpectrumPtr histo = mhisto.y;
        addGraph();

        graph()->setPen(QPen(Qt::green)); // line color blue for first graph
        graph()->setAntialiasedFill(false);
        graph()->setLineStyle(QCPGraph::lsStepCenter);
        graph()->setName("Y");

        QVector<double> ticks(histo->getEasyTab().size());
        QVector<double> data(histo->getEasyTab().size());
        for(int i=0; i<histo->getEasyTab().size(); i++) {
            ticks[i] = histo->getEasyTab()[i].frequency;
            data[i] = histo->getEasyTab()[i].amplitude;
        }
        graph()->setData(ticks, data);
    }

    if(!mhisto.z.isNull()) {
        SpectrumPtr histo = mhisto.z;
        addGraph();

        graph()->setPen(QPen(Qt::blue)); // line color blue for first graph
        graph()->setAntialiasedFill(false);
        graph()->setLineStyle(QCPGraph::lsStepCenter);
        graph()->setName("Z");

        QVector<double> ticks(histo->getEasyTab().size());
        QVector<double> data(histo->getEasyTab().size());
        for(int i=0; i<histo->getEasyTab().size(); i++) {
            ticks[i] = histo->getEasyTab()[i].frequency;
            data[i] = histo->getEasyTab()[i].amplitude;
        }
        graph()->setData(ticks, data);
    }

    if(!mhisto.xyz.isNull()) {
        SpectrumPtr histo = mhisto.xyz;
        addGraph();

        graph()->setPen(QPen(QColor(251, 186,24))); // line color blue for first graph
        graph()->setAntialiasedFill(false);
        graph()->setLineStyle(QCPGraph::lsStepCenter);
        graph()->setName("XYZ");

        QVector<double> ticks(histo->getEasyTab().size());
        QVector<double> data(histo->getEasyTab().size());
        for(int i=0; i<histo->getEasyTab().size(); i++) {
            ticks[i] = histo->getEasyTab()[i].frequency;
            data[i] = histo->getEasyTab()[i].amplitude;
        }
        graph()->setData(ticks, data);
    }
}

SpectrumGraph::~SpectrumGraph()
{

}

