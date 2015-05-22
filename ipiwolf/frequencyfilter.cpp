#include "frequencyfilter.h"
#include <fftw3.h>
#include <math.h>
#include <QDebug>

FrequencyFilter::FrequencyFilter()
{
    _dataFile = DataFilePtr();
}

FrequencyFilter::~FrequencyFilter()
{

}

void FrequencyFilter::setDatafile(DataFilePtr dataFile) {
    _dataFile = dataFile;
}

void FrequencyFilter::setThreshold(double threshold) {
    _threshold = threshold;
}

void FrequencyFilter::setAxes(Axe axe) {
    _axe = axe;
}

void FrequencyFilter::setDirection(Direction d) {
    _direction = d;
}

SpectrumPtr FrequencyFilter::getSpectrum(std::function<double (DataFilePtr, int)> f) {
    if(!_dataFile) {
        qDebug() << "datafile nul";
        return SpectrumPtr();
    }

    fftw_complex *out1;
    fftw_plan p;
    int k;


    double *amplitude = (double *)fftw_malloc((_dataFile->size())*sizeof(double)); // signal entré


    out1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (_dataFile->size())); // basses freq nulles


    for(k=0;k<_dataFile->size();k++) amplitude[k]= f(_dataFile,k);

    p = fftw_plan_dft_r2c_1d(_dataFile->size(), amplitude, out1, FFTW_ESTIMATE);



    fftw_execute(p);

    SpectrumPtr res(new Spectrum(out1, _dataFile->size(), _dataFile->getSamplingRate()));


    fftw_free(amplitude);
    fftw_destroy_plan(p);
    fftw_cleanup();

    return res;
}

MultiSpectrum FrequencyFilter::getSpectrum(bool x, bool y, bool z, bool xyz) {
    MultiSpectrum res;
    if(x)
        res.x = getSpectrum(X);
    if(y)
        res.y = getSpectrum(Y);
    if(z)
        res.z = getSpectrum(Z);
    if(xyz)
        res.xyz = getSpectrum(XYZ);
    return res;
}

SpectrumPtr FrequencyFilter::getSpectrum(Axe axe) {
    if(axe == X) {
        return getSpectrum([](DataFilePtr df, int k) { return df->at(k).x; });
    }
    else if(axe == Y) {
        return getSpectrum([](DataFilePtr df, int k) { return df->at(k).y; });
    }
    else if(axe == Z) {
        return getSpectrum([](DataFilePtr df, int k) { return df->at(k).z; });
    }
    else {
        return getSpectrum([](DataFilePtr df, int k) { return (*df)[k].getXYZ(); });
    }
}

void FrequencyFilter::process() {

    SpectrumPtr histo = getSpectrum(_axe);

    fftw_complex * n = histo->getTab();
    double *output = (double *)fftw_malloc((histo->getSize())*sizeof(double));

    int start = (_dataFile->size() * _threshold)/_dataFile->getSamplingRate();



    for(int i=0; i<histo->getSize(); i++) {
        if((i>start && _direction == HIGH) || (i<= start && _direction == LOW)) {
            n[i][0] = histo->getTab()[i][0];
            n[i][1] = histo->getTab()[i][1];
         } else {
            n[i][0] = 0;
            n[i][1] = 0;
        }
    }

    fftw_plan q = fftw_plan_dft_c2r_1d(_dataFile->size(), n, output, FFTW_ESTIMATE);

    fftw_execute(q);

    if(_axe == X) {
        for(int i=0; i<_dataFile->size(); i++)
            (*_dataFile)[i].x = output[i]/_dataFile->size();
    } else if(_axe == Y) {
        for(int i=0; i<_dataFile->size(); i++)
            (*_dataFile)[i].y = output[i]/_dataFile->size();
    } else if(_axe == Z) {
        for(int i=0; i<_dataFile->size(); i++)
            (*_dataFile)[i].z = output[i]/_dataFile->size();
    } else {
        for(int i=0; i<_dataFile->size(); i++) {
            (*_dataFile)[i].x = 0;
            (*_dataFile)[i].y = 0;
            (*_dataFile)[i].z = 0;
            (*_dataFile)[i].setXYZ(output[i]/_dataFile->size());
        }
    }


    fftw_destroy_plan(q);


}
