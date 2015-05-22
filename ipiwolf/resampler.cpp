#include "resampler.h"
#include <QFileInfo>
#include <QDebug>

Resampler::Resampler()
{
    setStartDate(QDateTime::currentDateTime());
    setEndDate(QDateTime::currentDateTime());
}

Resampler::Resampler(QString filename)
{
    setFile(filename);
    setStartDate(QDateTime::currentDateTime());
    setEndDate(QDateTime::currentDateTime());
}

void Resampler::setFile (QString filename)
{
    _file.setFileName(filename);
    if (!_file.exists())
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
}

void Resampler::setStartDate(QDateTime startDate)
{
    this->_startDate = startDate;
}

void Resampler::setEndDate(QDateTime endDate)
{
    this->_endDate = endDate;
}

void Resampler::setFrequency (int freq)
{
    this->_newFrequency = freq;
}

void Resampler::stop()
{
    qDebug() << "stopped";
    _stop = true;
}

void Resampler::resample()
{
    if(!_file.open(QIODevice::ReadOnly))
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
    }

    DataFilePtr final(new DataFile());
    QTextStream in(&_file);
    QDateTime currentDate;
    QString line = in.readLine();
    QStringList listCou = line.split("\t");
    QStringList listPrec;
    float timePb = 0.0, timeNewPoint = 0.0, timePa, timeBetweenPoints;
    _stop = false;

    while (!in.atEnd() && (!currentDate.isValid() || currentDate <= _endDate) && !_stop)
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
            QDateTime parsedDate = QDateTime::fromString(listCou[0] + ":" + listCou[1], "dd'/'MM'/'yyyy:hh:mm:ss");
            if(parsedDate.isValid()) {
                currentDate = parsedDate;
                emit dateChanged(currentDate);           //send the date to resamplerdialog
                timeBetweenPoints = 1.f / listCou[2].toFloat();
            }
        }
    }

    _file.close();

    final->setSamplingRate(_newFrequency);

    _result = final;
    emit finished();
}

DataFilePtr Resampler::getResult() {
    return _result;
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

void Resampler::getExtremDates(const QString& filename, QDateTime * startDate, QDateTime * lastDate) {
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        QFileInfo fi(file);

        QTextStream in(&file);
        bool found = false;
        while(!found && !in.atEnd()) {
            QString line = in.readLine();
            QStringList listCou = line.split("\t");

            if(listCou.size() > 1) {
                if (!listCou[0].trimmed().isEmpty())       //if the date changes
                {
                    (*startDate) = QDateTime::fromString(listCou[0] + ":" + listCou[1], "dd'/'MM'/'yyyy:hh:mm:ss");
                    if(startDate->isValid())
                        found = true;
                }
            }
        }
        if(fi.size() <= 5000)
            in.seek(0);
        else
            in.seek(fi.size()-5000);
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList listCou = line.split("\t");

            if(listCou.size() > 1) {
                if (!listCou[0].trimmed().isEmpty())       //if the date changes
                {
                    QDateTime tmp = QDateTime::fromString(listCou[0] + ":" + listCou[1], "dd'/'MM'/'yyyy:hh:mm:ss");
                    if(tmp.isValid())
                        (*lastDate) = tmp;
                }
            }
        }
    file.close();
    }
}

