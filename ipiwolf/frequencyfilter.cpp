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

void FrequencyFilter::setThreshold(int threshold) {
    _threshold = threshold;
}

void FrequencyFilter::setAxes(Axe axe) {
    _axe = axe;
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
        return getSpectrum([](DataFilePtr df, int k) { return sqrt(df->at(k).x*df->at(k).x + df->at(k).y*df->at(k).y + df->at(k).z*df->at(k).y); });
    }
}

DataFilePtr FrequencyFilter::process() {
/*

    memcpy(out2, out1, _dataFile->size()*sizeof(fftw_complex));

    for (k = 0; k < _dataFile->size(); k++) {
        magnitude[k]=sqrt(out1[k][0]*out1[k][0]+out1[k][1]*out1[k][1]);
    }

    // separate low and high frequencies
    int start =(_threshold*_dataFile->getSamplingRate())/_dataFile->size();
    int end = _dataFile->size() - start;

    std::cout << "start : " << start << std::endl;
    std::cout << "end : " << end << std::endl;
    std::cout << "size : " << _dataFile->size() << std::endl;


    for(k=start;k<end;k++) out1[k][0]=out1[k][1]= 0.0;
    for(k=0;k<start;k++)   out2[k][0]=out2[k][1]= 0.0;


    q = fftw_plan_dft_c2r_1d(_dataFile->size(), out1, amplitude1, FFTW_ESTIMATE);
    fftw_execute(q);
    q = fftw_plan_dft_c2r_1d(_dataFile->size(), out2, amplitude2, FFTW_ESTIMATE);
    fftw_execute(q);

    DataFilePtr output(new DataFile());
    output->setSamplingRate(_dataFile->getSamplingRate());
    for (k = 0; k < _dataFile->size(); k++) {
        output->push_back(Point(amplitude[k],amplitude1[k]/((_dataFile->size()-1)),amplitude2[k]/((_dataFile->size()-1))));
    }


    fftw_destroy_plan(p);
    fftw_destroy_plan(q);
    free(amplitude);free(amplitude1);free(amplitude2);
    free(magnitude);
    fftw_free(out1);fftw_free(out2);

    return output;*/


    SpectrumPtr histo = getSpectrum(_axe);

    fftw_complex * n = histo->getTab();
    double *output = (double *)fftw_malloc((histo->getSize())*sizeof(double));

    int start = (_dataFile->size() * _threshold)/_dataFile->getSamplingRate();
    int end = _dataFile->size() - start;

    for(int i=0; i<histo->getSize(); i++) {
        if(i>start && i<end) {
            n[i][0] = histo->getTab()[i][0];
            n[i][1] = histo->getTab()[i][1];
         } else {
            n[i][0] = 0;
            n[i][1] = 0;
        }
    }

    fftw_plan q = fftw_plan_dft_c2r_1d(_dataFile->size(), n, output, FFTW_ESTIMATE);

    fftw_execute(q);

    DataFilePtr newDataFile(new DataFile(_dataFile->size()));
    newDataFile->setSamplingRate(_dataFile->getSamplingRate());
    for(int i=0; i<_dataFile->size(); i++) {
        (*newDataFile)[i] = Point(output[i]/_dataFile->size(),0,0);
    }

    fftw_destroy_plan(q);

    histo->updateEasyTab();

    std::cout << (*histo) << std::endl;

    std::cout << "start : " << start << std::endl;
    std::cout << "end : " << end << std::endl;
    std::cout << "size : " << _dataFile->size() << std::endl;

     return newDataFile;
}
