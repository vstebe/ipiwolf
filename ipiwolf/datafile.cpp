#include "datafile.h"
#include <QFile>
#include <QTextStream>

DataFile::DataFile()
{
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
