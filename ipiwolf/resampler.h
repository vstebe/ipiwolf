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
    /**
    * \brief Constructor of the object resampler
    */
    Resampler();

    /**
    * \brief Constructor of the object resampler
    * \param filename the name of the file
    */
    Resampler(QString filename);

    /**
    * \brief Sets the file you want to resample
    * \param filename the name of the file
    */
    void setFile (QString filename);

    /**
    * \brief Sets the frequency of the sample
    * \param freq the new frequency
    */
    void setFrequency (int freq);

    /**
    * \brief Sets the startDate
    * \param startDate the date you want to set
    */
    void setStartDate(QDateTime startDate);

    /**
    * \brief Sets the endDate
    * \param endDate the date you want to set
    */
    void setEndDate(QDateTime endDate);

    /**
    * \brief Resamples the file with the _newFrequency
    * \return a formatted Datafile of the sample, between the two dates given and at the new Frequency
    */
    void resample();

    /**
     * @brief Computes the coordinates of a new point beetween the coordinates of two points and their time.
     * @param a the first point
     * @param timePa the time of the point a
     * @param b the second point
     * @param timePb the time of the point b
     * @param timeNewPoint the time of the new point
     * @return the coordinates of the new point.
     */
    Point calcCoord(Point a, float timePa, Point b, float timePb, float timeNewPoint);

    /**
     * @brief Computes the guiding coefficient of the straight line crossing 2 points.
     * @param a the point a
     * @param timePa the time of the point a
     * @param b the point b
     * @param timePb the time of the point b
     * @return the guiding coefficient
     */
    float coeffDirect(float a, float timePa, float b, float timePb);

    /**
     * @brief Computes the ordinates at the origin of a straight line
     * @param coeffDir the guiding coefficient of the straight line
     * @param a a point of the straight line
     * @param timPa the time of the point a
     * @return the ordinates at the origin
     */
    float ordOri(float coeffDir, float a, float timPa);

    /**
     * @brief Computes the coordinates of a new point on a straight line
     * @param coeffDir the guiding coefficient of the straight line
     * @param OrdOri the ordinates at teh origin of a straight line
     * @param time the time of the new point
     * @return the coordinates of the new point
     */
    float calcNewPoint(float coeffDir, float OrdOri, float time);

    /**
     * @brief Returns the pointer of the Datafile
     * @return the pointer of the Datafile
     */
    DataFilePtr getResult();

    /**
     * @brief stop Stops the thread of the resamplerDialog when the user push the cancel button.
     */
    void stop();

    /**
     * @brief Gets the first and last datetime of a file.
     * @param filename the name of the file
     * @param startDate the pointer on the first date
     * @param lastDate the pointer on the second date
     */
    static void getExtremDates(const QString& filename, QDateTime * startDate, QDateTime * lastDate);

signals:

    /**
     * @brief Signal which is emit when the date changes
     * @param date the new date
     */
    void dateChanged(QDateTime date);

    /**
     * @brief Signal which is emit at the end of the resampling
     */
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
