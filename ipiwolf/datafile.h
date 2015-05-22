#ifndef DATAFILE_H
#define DATAFILE_H

#include <QVector>
#include <QSharedPointer>

#include "point.h"

class DataFile;
typedef QSharedPointer<DataFile> DataFilePtr;

/**
 * @brief Class representing a signal. The signal is a list of 3-axe points with a specified sampling rate.
 */
class DataFile : public QVector<Point>
{
public:
    /**
     * @brief Constructs a empty datafile
     */
    DataFile();

    /**
     * @brief Constructs a datafile with "size" points initialized with (0,0,0)
     * @param size number of points
     */
    DataFile(int size);

    /**
     * @brief Saves the signal in a three-colomn text format
     * point1.x point1.y point1.z
     * point2.x point2.y point2.z
     * point3.x point3.y point3.z
     * (..)
     * @param filename name of the file which will be saved
     */
    void saveInFile(QString filename);

    /**
     * @brief Sets the sampling rate of the signal
     * @param samplingRate the new sampling rate
     */
    void setSamplingRate(int samplingRate);

    /**
     * @brief Gets the sampling rate of the signal
     * @return the sampling rate
     */
    int getSamplingRate() const;

    /**
     * @brief Loads a signal saved in a three-colomn text file
     * point1.x point1.y point1.z
     * point2.x point2.y point2.z
     * point3.x point3.y point3.z
     * (..)
     * @param filename name of the file to open
     * @return SharedPointer to the new Datafile
     */
    static DataFilePtr openFile(const QString& filename);

    ~DataFile();

protected:
    int _samplingRate;
};

std::ostream& operator << (std::ostream& O, const DataFile& d);


#endif // DATAFILE_H
