#include "spectrum.h"
#include <math.h>
Spectrum::Spectrum(fftw_complex * tab, int size, int samplingRate) {
    _tab = tab;
    _size = size;
    _samplingRate = samplingRate;

    updateEasyTab();
}

void Spectrum::updateEasyTab() {
    _easyTab = QVector<SpectrumPoint>(_size/2+1);
    for(int i=0; i<_size/2+1; i++) {
        _easyTab[i].frequency = (((double)i)*_samplingRate)/_size;
        _easyTab[i].amplitude = sqrt(_tab[i][0]*_tab[i][0] + _tab[i][1]*_tab[i][1]);
    }
}

int Spectrum::getSize() const {
    return _size;
}

fftw_complex * Spectrum::getTab() {
    return _tab;
}

Spectrum::~Spectrum() {
    fftw_free(_tab);
}

const QVector<SpectrumPoint>& Spectrum::getEasyTab() const {
    return _easyTab;
}

std::ostream& operator << (std::ostream& O, const Spectrum& d)
{
   for(int i=0; i<d.getEasyTab().size(); i++)
       O << d.getEasyTab()[i].frequency << " Hz  <->  " << d.getEasyTab()[i].amplitude << " dB" << std::endl;
   return O;
}
