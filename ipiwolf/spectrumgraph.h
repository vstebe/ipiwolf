#ifndef HISTOGRAMGRAPH_H
#define HISTOGRAMGRAPH_H

#include "spectrum.h"
#include "qcustomplot.h"

/**
 * @brief Graph used for displaying a spectrum
 */
class SpectrumGraph : public QCustomPlot
{
public:
    /**
     * @brief Constructs the graph
     * @param parent QWidget parent
     */
    SpectrumGraph(QWidget * parent = NULL);

    /**
     * @brief Sets the spectrum which must be displayed.
     * The graph will display the axes which are not null
     * @param mhisto
     */
    void setSpectrum(MultiSpectrum mhisto);

    ~SpectrumGraph();
};

#endif // HISTOGRAMGRAPH_H
