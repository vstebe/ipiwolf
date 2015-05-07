#ifndef FREQUENCYFILTER_H
#define FREQUENCYFILTER_H

#include <QSharedPointer>

#include "datafile.h"
#include "spectrum.h"

class FrequencyFilter
{
public:
    enum Axe {X, Y, Z, XYZ};

    FrequencyFilter();
    void setDatafile(DataFilePtr dataFile);
    void setThreshold(int threshold);
    void setAxes(Axe axes);
    SpectrumPtr getSpectrum();
    DataFilePtr process();
    ~FrequencyFilter();

protected:
    DataFilePtr _dataFile;
    Axe _axe;
    int _threshold;
};




#endif // FREQUENCYFILTER_H
