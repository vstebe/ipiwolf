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

    DataFile final, temp;
    QTextStream in(&_file);
    QDate currentDate;
    QString line = in.readLine();
    QStringList list = line.split("\t");

    while (!in.atEnd())
    {
        if (list[0]!= "")                                                 //if the list[0] is empty
            currentDate = QDate::fromString(list[0], "dd'/'MM'/'yyyy");

        if ((!currentDate.isNull()) && ( currentDate >= _startDate && currentDate<= _endDate))
        {
            temp.push_back( Point(list[4].toFloat(),list[5].toFloat(),list[6].toFloat()));
            line = in.readLine();
            list = line.split("\t");

            while (list[0]== "")      //while the currentDate is the same
            {
                temp.push_back(Point(list[4].toFloat(),list[5].toFloat(),list[6].toFloat()));
                line = in.readLine();
                list = line.split("\t");
            }
            final += secResample(temp);
            temp.clear();
        }
    }
    return final;
}


/**
* \brief Resample a part (a second) of the file
* \param lines the points to resample
* \return A vector of points
*/
 QVector<Point> resampler::secResample(QVector<Point> lines)
 {


   QVector<Point> vect(55);





 }







