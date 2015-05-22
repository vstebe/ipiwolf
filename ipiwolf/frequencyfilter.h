#ifndef FREQUENCYFILTER_H
#define FREQUENCYFILTER_H

#include <functional>
#include <QSharedPointer>

#include "datafile.h"
#include "spectrum.h"

/**
 * @brief Class allowing to compute the spectrum of a signal and filter it
 */
class FrequencyFilter
{
public:
    enum Axe {X, Y, Z, XYZ};
    enum Direction {LOW, HIGH};

    /**
     * @brief Constructs the filter
     */
    FrequencyFilter();

    /**
     * @brief Sets the datafile containing the signal to process
     * @param dataFile SharedPointer to the datafile
     */
    void setDatafile(DataFilePtr dataFile);

    /**
     * @brief Sets the threshold to use for the filtering
     * @param threshold threshold to use
     */
    void setThreshold(double threshold);

    /**
     * @brief Sets the axes to filter
     * @param axes axes to filter
     */
    void setAxes(Axe axes);

    /**
     * @brief Sets to direction of the filtering.
     * If LOW, every frequency below the threshold will be set to zero
     * if HIGH, every frequency higher than the threshold, will be set to zero
     * @param d the direction
     */
    void setDirection(Direction d);

    /**
     * @brief Compute the spectrum from the given datafile
     * @param x x axis spectrum will be computed if true
     * @param y y axis spectrum will be computed if true
     * @param z z axis spectrum will be computed if true
     * @param xyz the magnitude of the spectrum will be computed if true
     * @return structure representing the different sprectums. Axes not computed are NULL
     */
    MultiSpectrum getSpectrum(bool x, bool y, bool z, bool xyz);

    /**
     * @brief Process the filtering
     */
    void process();
    ~FrequencyFilter();

protected:
    /**
     * @brief Compute the spectrum with the given function called for each point
     * @return
     */
    SpectrumPtr getSpectrum(std::function<double (DataFilePtr, int)> );
    SpectrumPtr getSpectrum(Axe axe);

    DataFilePtr _dataFile;
    Axe _axe;
    Direction _direction;
    double _threshold;
};




#endif // FREQUENCYFILTER_H
