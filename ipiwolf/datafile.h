#ifndef DATAFILE_H
#define DATAFILE_H

#include <QVector>
#include <QSharedPointer>

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

typedef QSharedPointer<DataFile> DataFilePtr;

#endif // DATAFILE_H
