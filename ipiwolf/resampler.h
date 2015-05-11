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

class Resampler : public QObject
{
    Q_OBJECT

public:
    Resampler();
    Resampler(QString filename);
    void setFile (QString filename);
    void setFrequency (int freq);
    void setStartDate(QDate startDate);
    void setEndDate(QDate endDate);
    void resample();
    Point calcCoord(Point a, float timePa, Point b, float timePb, float timeNewPoint);
    float coeffDirect(float a, float timePa, float b, float timePb);
    float ordOri(float coeffDir, float a, float timPa);
    float calcNewPoint(float coeffDir, float OrdOri, float time);
    DataFilePtr getResult();

signals:
    void dateChanged(QDate date);
    void finished();

private:
    QDate _startDate;
    QDate _endDate;
    QFile _file;
    int _newFrequency;
    DataFilePtr _result;

};

#endif // RESAMPLER_H
