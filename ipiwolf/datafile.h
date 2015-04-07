#ifndef DATAFILE_H
#define DATAFILE_H
#include <QVector>
#include "point.h"

class DataFile : public QVector<Point>
{
public:
    DataFile();
    DataFile(int size);
    void saveInFile(QString filename);
    void setSamplingRate(int samplingRate);
    int getSamplingRate() const;

protected:
    int _samplingRate;
};

#endif // DATAFILE_H
