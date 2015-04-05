#ifndef FREQUENCYFILTER_H
#define FREQUENCYFILTER_H

#include "datafile.h"

class FrequencyFilter
{
public:
    enum Axe {X, Y, Z, XYZ};

    FrequencyFilter();
    void setDatafile(DataFile * dataFile);
    void setThreshold(int threshold);
    void setAxes(Axe axes);
    DataFile * process();
    ~FrequencyFilter();

protected:
    DataFile * _dataFile;
    Axe _axe;
    int _threshold;
};

#endif // FREQUENCYFILTER_H
