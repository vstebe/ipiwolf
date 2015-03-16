#include "resampler.h"

/**
* \brief Constructor of the object resampler
*/
resampler::resampler()
{
}

/**
* \brief Constructor of the object resampler
* \param filename the name of the file
*/
resampler::resampler(QString filename)
{
    resampler::setFile(filename);
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
   /* if date == ok
    * tant que datefin est pas atteinte :
    * faire vector point
    * envoyer vector à resampler et concat avec le vecteur total
    * fin quand date fin est atteinte
    */

    if(!_file.open(QIODevice::ReadOnly))
    {
        printf("Impossible d'ouvrir le fichier !");
        return DataFile();
    }
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







