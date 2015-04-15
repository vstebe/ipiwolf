#include "datafile.h"
#include <QFile>
#include <QTextStream>

DataFile::DataFile()
{
    _samplingRate = 0;
}

DataFile::DataFile(int size) : QVector<Point>(size) {}

void DataFile::saveInFile(QString filename) {
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        for(QVector<Point>::const_iterator it = this->constBegin(); it != this->constEnd(); it++) {
            stream  << it->x << '\t' << it->y << '\t' << it->z << endl;
        }
    }
}


void DataFile::setSamplingRate(int samplingRate) {
    _samplingRate = samplingRate;
}

int DataFile::getSamplingRate() const {
    return _samplingRate;
}
