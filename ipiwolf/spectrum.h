#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QVector>
#include <QSharedPointer>
#include <fftw3.h>
struct SpectrumPoint {
    double frequency;
    double amplitude;
};

class Spectrum {
public:
    Spectrum(fftw_complex * tab, int size, int samplingRate);
    ~Spectrum();

    const QVector<SpectrumPoint>& getEasyTab() const;
    void updateEasyTab();

    fftw_complex * getTab();
    int getSize() const;



protected:
    fftw_complex * _tab;
    int _size;
    int _samplingRate;
    QVector<SpectrumPoint> _easyTab;
};



typedef QSharedPointer<Spectrum> SpectrumPtr;

struct MultiSpectrum {
    SpectrumPtr x;
    SpectrumPtr y;
    SpectrumPtr z;
    SpectrumPtr xyz;
};

std::ostream& operator << (std::ostream& O, const Spectrum& d);


#endif // HISTOGRAM_H

