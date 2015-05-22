#ifndef RESAMPLER_H
#define RESAMPLER_H
#include <QString>
#include <QDate>
#include <QFile>
#include <QVector>
#include <QDateTime>
#include <QTextStream>
#include "datafile.h"
#include "point.h"

/**
 * @brief Class used for resampling a signal.
 * It opens a raw file.
 */
class Resampler : public QObject
{
    Q_OBJECT

public:
    Resampler();
    Resampler(QString filename);
    void setFile (QString filename);
    void setFrequency (int freq);
    void setStartDate(QDateTime startDate);
    void setEndDate(QDateTime endDate);
    void resample();
    Point calcCoord(Point a, float timePa, Point b, float timePb, float timeNewPoint);
    float coeffDirect(float a, float timePa, float b, float timePb);
    float ordOri(float coeffDir, float a, float timPa);
    float calcNewPoint(float coeffDir, float OrdOri, float time);
    DataFilePtr getResult();
    void stop();

    static void getExtremDates(const QString& filename, QDateTime * startDate, QDateTime * lastDate);

signals:
    void dateChanged(QDateTime date);
    void finished();

private:
    QDateTime _startDate;
    QDateTime _endDate;
    QFile _file;
    int _newFrequency;
    DataFilePtr _result;
    bool _stop;

};

#endif // RESAMPLER_H
