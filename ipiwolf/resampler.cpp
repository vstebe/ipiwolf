#include "resampler.h"
#include <QDebug>
/**
* \brief Constructor of the object resampler
*/
Resampler::Resampler()
{
    setStartDate(QDate::currentDate());
    setEndDate(QDate::currentDate());
}

/**
* \brief Constructor of the object resampler
* \param filename the name of the file
*/
Resampler::Resampler(QString filename)
{
    setFile(filename);
    setStartDate(QDate::currentDate());
    setEndDate(QDate::currentDate());
}


/**
* \brief Set the file you want to resample
* \param filename the name of the file
*/
void Resampler::setFile (QString filename)
{
    _file.setFileName(filename);
    if (!_file.exists())
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}

/**
* \brief Set the startDate
* \param startDate the date you want to set
*/
void Resampler::setStartDate(QDate startDate)
{
    this->_startDate = startDate;
}


/**
* \brief Set the endDate
* \param endDate the date you want to set
*/
void Resampler::setEndDate(QDate endDate)
{
    this->_endDate = endDate;
}

/**
* \brief Set the frequency of the sample
* \param freq the new frequency
*/
void Resampler::setFrequency (int freq)
{
    this->_newFrequency = freq;
}


/**
* \brief Resample the file with the _newFrequency
* \return a formatted Datafile of the sample, between the two dates given and at the new Frequency
*/
DataFilePtr Resampler::resample()
{
    if(!_file.open(QIODevice::ReadOnly))
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        return DataFilePtr();
    }

    DataFilePtr final(new DataFile());
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
                Point b (listCou[4].toFloat(),listCou[5].toFloat(),listCou[6].toFloat());     //second point
                timePa = timePb - timeBetweenPoints;
                final->push_back(calcCoord(a, timePa, b, timePb, timeNewPoint));     //compute the new point
            }
        }

        if (!listCou[0].trimmed().isEmpty())       //if the date changes
        {
            QDate parsedDate = QDate::fromString(listCou[0], "dd'/'MM'/'yyyy");
            if(parsedDate.isValid()) {
                currentDate = parsedDate;
                emit dateChanged(currentDate);           //send the date to resamplerdialog
                timeBetweenPoints = 1.f / listCou[2].toFloat();
            }
        }
    }

    _file.close();

    final->setSamplingRate(_newFrequency);
    return final;
}

Point Resampler::calcCoord(Point a, float timePa, Point b, float timePb, float timeNewPoint)
{
    float coeffDirX = coeffDirect(a.x, timePa, b.x, timePb);        //process the coeff
    float coeffDirY = coeffDirect(a.y, timePa, b.y, timePb);
    float coeffDirZ = coeffDirect(a.z, timePa, b.z, timePb);

    float OrdOriX = ordOri(coeffDirX, a.x, timePa);
    float OrdOriY = ordOri(coeffDirY, a.y, timePa);
    float OrdOriZ = ordOri(coeffDirZ, a.z, timePa);

    float CoordX = calcNewPoint(coeffDirX, OrdOriX, timeNewPoint);
    float CoordY = calcNewPoint(coeffDirY, OrdOriY, timeNewPoint);
    float CoordZ = calcNewPoint(coeffDirZ, OrdOriZ, timeNewPoint);

    return Point(CoordX, CoordY, CoordZ);
}

float Resampler::coeffDirect(float a, float timePa, float b, float timePb)
{
    return ((b-a)/(timePb-timePa));
}

float Resampler::ordOri(float coeffDir, float a, float timePa)
{
    return ((a)-(coeffDir*timePa));
}

float Resampler::calcNewPoint(float coeffDir, float OrdOri, float time)
{
    return ((time*coeffDir) + OrdOri);
}


