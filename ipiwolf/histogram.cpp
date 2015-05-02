#include "histogram.h"
#include <math.h>
Histogram::Histogram(fftw_complex * tab, int size, int samplingRate) {
    _tab = tab;
    _size = size;
    _samplingRate = samplingRate;

    updateEasyTab();
}

void Histogram::updateEasyTab() {
    _easyTab = QVector<HistogramPoint>(_size/2+1);
    for(int i=0; i<_size/2+1; i++) {
        _easyTab[i].frequency = (((double)i)*_samplingRate)/_size;
        _easyTab[i].amplitude = sqrt(_tab[i][0]*_tab[i][0] + _tab[i][1]*_tab[i][1]);
    }
}

int Histogram::getSize() const {
    return _size;
}

fftw_complex * Histogram::getTab() {
    return _tab;
}

Histogram::~Histogram() {
    fftw_free(_tab);
}

const QVector<HistogramPoint>& Histogram::getEasyTab() const {
    return _easyTab;
}

std::ostream& operator << (std::ostream& O, const Histogram& d)
{
   for(int i=0; i<d.getEasyTab().size(); i++)
       O << d.getEasyTab()[i].frequency << " Hz  <->  " << d.getEasyTab()[i].amplitude << " dB" << std::endl;
   return O;
}
