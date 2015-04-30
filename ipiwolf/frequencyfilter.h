#ifndef FREQUENCYFILTER_H
#define FREQUENCYFILTER_H

#include "datafile.h"
struct HistogramPoint {
    double frequency;
    double amplitude;
};

typedef QVector<HistogramPoint> Histogram;
typedef QSharedPointer<Histogram> HistogramPtr;

class FrequencyFilter
{
public:
    enum Axe {X, Y, Z, XYZ};

    FrequencyFilter();
    void setDatafile(DataFilePtr dataFile);
    void setThreshold(int threshold);
    void setAxes(Axe axes);
    HistogramPtr getHistogram();
    DataFilePtr process();
    ~FrequencyFilter();

protected:
    DataFilePtr _dataFile;
    Axe _axe;
    int _threshold;
};




#endif // FREQUENCYFILTER_H
