#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QVector>
#include <QSharedPointer>
#include <fftw3.h>
struct HistogramPoint {
    double frequency;
    double amplitude;
};

class Histogram {
public:
    Histogram(fftw_complex * tab, int size, int samplingRate);
    ~Histogram();

    const QVector<HistogramPoint>& getEasyTab() const;
    void updateEasyTab();

    fftw_complex * getTab();
    int getSize() const;



protected:
    fftw_complex * _tab;
    int _size;
    int _samplingRate;
    QVector<HistogramPoint> _easyTab;
};

typedef QSharedPointer<Histogram> HistogramPtr;

std::ostream& operator << (std::ostream& O, const Histogram& d);


#endif // HISTOGRAM_H

