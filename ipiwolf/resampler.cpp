#include "resampler.h"

/**
* \brief Constructor of the object resampler
*/
resampler::resampler()
{
    setStartDate(QDate::currentDate());
    setEndDate(QDate::currentDate());
}

/**
* \brief Constructor of the object resampler
* \param filename the name of the file
*/
resampler::resampler(QString filename)
{
    setFile(filename);
    setStartDate(QDate::currentDate());
    setEndDate(QDate::currentDate());
}


/**
* \brief Set the file you want to resample
* \param filename the name of the file
*/
void resampler::setFile (QString filename)
{
    QFile _file(filename);
    if (!_file.exists())
        printf("Le fichier n'existe pas !");
}

/**
* \brief Set the startDate
* \param startDate the date you want to set
*/
void resampler::setStartDate(QDate startDate)
{
    this->_startDate = startDate;
}


/**
* \brief Set the endDate
* \param endDate the date you want to set
*/
void resampler::setEndDate(QDate endDate)
{
    this->_endDate = endDate;
}

/**
* \brief Set the frequency of the sample
* \param freq the new frequency
*/
void resampler::setFrequency (int freq)
{
    this->_newFrequency = freq;
}


/**
* \brief Resample the file with the _newFrequency
* \return a formatted Datafile of the sample, between the two dates given and at the new Frequency
*/
DataFile resampler::resample()
{
    if(!_file.open(QIODevice::ReadOnly))
    {
        printf("Impossible d'ouvrir le fichier !");
        return DataFile();
    }

    DataFile final;
    QTextStream in(&_file);
    QDate currentDate;
    QString line = in.readLine();
    QStringList listCou = line.split("\t");
    QStringList listPrec;
    float timePb = 0.0, timeNewPoint = 0.0, timePa, timeBetweenPoints;

    while (!in.atEnd())
    {

        listPrec = listCou;
        line = in.readLine();
        listCou = line.split("\t");

        if ((!currentDate.isNull()) && ( currentDate >= _startDate && currentDate<= _endDate))  //the current date between the two dates
        {
            timePb += timeBetweenPoints;      //the time of the second point


            while ((timeNewPoint + (1.f/(float)_newFrequency)) < timePb)
            {
                timeNewPoint += (1.f/(float)_newFrequency);
                Point a (listPrec[4].toFloat(),listPrec[5].toFloat(),listPrec[6].toFloat());     //first point
                Point b (listPrec[4].toFloat(),listPrec[5].toFloat(),listPrec[6].toFloat());     //second point
                timePa = timePb - timeBetweenPoints;

                final.push_back(calcCoord(a, timePa, b, timePb, timeNewPoint));     //compute the new point
            }
        }

        if (listCou[0] != "")       //if the date changes
        {
            currentDate = QDate::fromString(listCou[0], "dd'/'MM'/'yyyy");
            timeBetweenPoints = 1.f / listCou[2].toFloat();
        }
    }

    return final;
}

Point resampler::calcCoord(Point a, float timePa, Point b, float timePb, float timeNewPoint)
{
    return Point();
}








