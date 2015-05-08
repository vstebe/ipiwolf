#ifndef FREQUENCYFILTER_H
#define FREQUENCYFILTER_H

#include <functional>
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
    MultiSpectrum getSpectrum(bool x, bool y, bool z, bool xyz);
    DataFilePtr process();
    ~FrequencyFilter();

protected:
    SpectrumPtr getSpectrum(std::function<double (DataFilePtr, int)> );
    SpectrumPtr getSpectrum(Axe axe);

    DataFilePtr _dataFile;
    Axe _axe;
    int _threshold;
};




#endif // FREQUENCYFILTER_H
