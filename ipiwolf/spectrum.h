#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QVector>
#include <QSharedPointer>
#include <fftw3.h>

/**
 * @brief Structure representing a point of the spectrum (couple hertz-amplitude)
 */
struct SpectrumPoint {
    double frequency;
    double amplitude;
};

/**
 * @brief Spectrum class with two representations : FFTW usable array, and a QVector of points that can be understood by anyone (and used to draw the graph)
 */
class Spectrum {
public:
    /**
     * @brief Constructs the spectrum from an array computed by FFTW
     * @param tab FFTW array
     * @param size array size
     * @param samplingRate the sampling rate of the signal
     */
    Spectrum(fftw_complex * tab, int size, int samplingRate);
    ~Spectrum();

    /**
     * @brief Returns a QVector of the points of the spectrum, sorted by frequency
     * The QVector should be updated (with updateEasyTab()) if the FFTW array has been modified
     * @return vector of points
     */
    const QVector<SpectrumPoint>& getEasyTab() const;

    /**
     * @brief Generates the QVector 'easyTab' from the FFTW array
     */
    void updateEasyTab();

    /**
     * @brief Returns the FFTW array. If this array is modified, updateEasyTab() should be called
     * @return the fftw array
     */
    fftw_complex * getTab();

    /**
     * @brief Returns the size of the FFTW array
     * @return  FFTW array size
     */
    int getSize() const;



protected:
    fftw_complex * _tab;
    int _size;
    int _samplingRate;
    QVector<SpectrumPoint> _easyTab;
};



typedef QSharedPointer<Spectrum> SpectrumPtr;

/**
 * @brief Structure for manipulating a spectrum for each axe of the signal
 */
struct MultiSpectrum {
    SpectrumPtr x;
    SpectrumPtr y;
    SpectrumPtr z;
    SpectrumPtr xyz;
};

std::ostream& operator << (std::ostream& O, const Spectrum& d);


#endif // HISTOGRAM_H

