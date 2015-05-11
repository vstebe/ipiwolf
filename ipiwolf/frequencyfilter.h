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
    enum Direction {LOW, HIGH};

    FrequencyFilter();
    void setDatafile(DataFilePtr dataFile);
    void setThreshold(double threshold);
    void setAxes(Axe axes);
    void setDirection(Direction d);
    MultiSpectrum getSpectrum(bool x, bool y, bool z, bool xyz);
    void process();
    ~FrequencyFilter();

protected:
    SpectrumPtr getSpectrum(std::function<double (DataFilePtr, int)> );
    SpectrumPtr getSpectrum(Axe axe);

    DataFilePtr _dataFile;
    Axe _axe;
    Direction _direction;
    double _threshold;
};




#endif // FREQUENCYFILTER_H
