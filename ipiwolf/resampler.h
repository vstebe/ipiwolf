#ifndef RESAMPLER_H
#define RESAMPLER_H
#include "QString"
#include "QDate"
#include "QFile"
#include "QVector"
#include "datafile.h"
#include "point.h"

class resampler
{
public:
    resampler();
    resampler(QString filename);
    void setFile (QString filename);
    void setFrequency (int freq);
    DataFile resample();
    QVector<Point> secResample(QVector<Point> lines);


private:
    QDate _dateDebut;
    QDate _dateFin;
    QFile _file;
    int _newFrequency;

};

#endif // RESAMPLER_H
