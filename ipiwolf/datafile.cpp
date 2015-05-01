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

DataFilePtr DataFile::openFile(const QString& filename) {

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        return DataFilePtr();
    }

    DataFilePtr res(new DataFile());
    QTextStream in(&file);

    QString line;

    while (!in.atEnd())
    {
        line = in.readLine();

        if(!line.trimmed().isEmpty()) {

            QStringList subLines = line.split("\t");
            if(subLines.size() != 3)
                return DataFilePtr();
            bool ok1, ok2, ok3;

            res->append(Point(subLines[0].toDouble(&ok1), subLines[1].toDouble(&ok2), subLines[2].toDouble(&ok3)));
            if(!ok1 || !ok2 || !ok3)
                return DataFilePtr();
        }
    }

    file.close();

    return res;
}


void DataFile::setSamplingRate(int samplingRate) {
    _samplingRate = samplingRate;
}

int DataFile::getSamplingRate() const {
    return _samplingRate;
}

std::ostream& operator << (std::ostream& O, const DataFile& d) {
    O << "Sampling Rate : " << d.getSamplingRate() << " Hz" << std::endl;
    for(int i=0; i<d.size(); i++)
        O << d[i] << std::endl;
    return O;
}
