#ifndef RESAMPLER_H
#define RESAMPLER_H
#include <QString>
#include <QDate>
#include <QFile>
#include <QVector>
#include <QDate>
#include <QTextStream>
#include "datafile.h"
#include "point.h"

class resampler
{
public:
    resampler();
    resampler(QString filename);
    void setFile (QString filename);
    void setFrequency (int freq);
    void setStartDate(QDate startDate);
    void setEndDate(QDate endDate);
    DataFile resample();
    QVector<Point> secResample(QVector<Point> lines);


private:
    QDate _startDate;
    QDate _endDate;
    QFile _file;
    int _newFrequency;

};

#endif // RESAMPLER_H
