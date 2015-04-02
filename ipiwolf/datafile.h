#ifndef DATAFILE_H
#define DATAFILE_H
#include <QVector>
#include "point.h"

class DataFile : public QVector<Point>
{
public:
    DataFile();
    DataFile(int size);
};

#endif // DATAFILE_H
