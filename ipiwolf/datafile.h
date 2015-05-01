#ifndef DATAFILE_H
#define DATAFILE_H

#include <QVector>
#include <QSharedPointer>

#include "point.h"

class DataFile;
typedef QSharedPointer<DataFile> DataFilePtr;

class DataFile : public QVector<Point>
{
public:
    DataFile();
    DataFile(int size);
    void saveInFile(QString filename);
    void setSamplingRate(int samplingRate);
    int getSamplingRate() const;

    static DataFilePtr openFile(const QString& filename);

protected:
    int _samplingRate;
};

std::ostream& operator << (std::ostream& O, const DataFile& d);


#endif // DATAFILE_H
