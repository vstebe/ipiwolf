#include "frequencyfilter.h"
#include <fftw3.h>
#include <math.h>
#include <QDebug>

FrequencyFilter::FrequencyFilter()
{
    _dataFile = NULL;
}

FrequencyFilter::~FrequencyFilter()
{

}

void FrequencyFilter::setDatafile(DataFile *dataFile) {
    _dataFile = dataFile;
}

void FrequencyFilter::setThreshold(int threshold) {
    _threshold = threshold;
}

void FrequencyFilter::setAxes(Axe axe) {
    _axe = axe;
}

DataFile * FrequencyFilter::process() {
    if(!_dataFile) {
        qDebug() << "datafile nul";
        return NULL;
    }

    fftw_complex *out1, *out2;
    fftw_plan p, q;
    int k;
    FILE *fo;
    char nomf[200];

    double *magnitude = (double *)malloc((_dataFile->size())*sizeof(double)); //norme du spectre
    double *amplitude = (double *)malloc((_dataFile->size())*sizeof(double)); // signal entré
    double *amplitude1 = (double *)malloc((_dataFile->size())*sizeof(double)); // signal reconstruit
    double *amplitude2 = (double *)malloc((_dataFile->size())*sizeof(double)); // signal reconstruit

    out1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (_dataFile->size())); // basses freq nulles
    out2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (_dataFile->size())); // hautes freq nulles

    switch (_axe) {
        case X:
            for(k=0;k<_dataFile->size();k++) amplitude[k]= (*_dataFile)[k].x;
            break;
        case Y:
            for(k=0;k<_dataFile->size();k++) amplitude[k]= (*_dataFile)[k].y;
            break;
        case Z:
            for(k=0;k<_dataFile->size();k++) amplitude[k]= (*_dataFile)[k].z;
            break;
        case XYZ:
            for(k=0;k<_dataFile->size();k++) amplitude[k]= sqrt((*_dataFile)[k].x*(*_dataFile)[k].x+(*_dataFile)[k].y*(*_dataFile)[k].y+(*_dataFile)[k].z*(*_dataFile)[k].z);
            break;
        default:
            break;
    }

    p = fftw_plan_dft_r2c_1d(_dataFile->size(), amplitude, out1, FFTW_ESTIMATE);
    fftw_execute(p);
    memcpy(out2, out1, _dataFile->size()*sizeof(fftw_complex));

    for (k = 0; k < _dataFile->size(); k++) {
        magnitude[k]=sqrt(out1[k][0]*out1[k][0]+out1[k][1]*out1[k][1]);
    }

    // separate low and high frequencies
    int start = (_threshold*_dataFile->size())/100;
    start = _threshold;
    int end = _dataFile->size();
    for(k=start;k<end;k++) out1[k][0]=out1[k][1]= 0.0;
    for(k=0;k<start;k++)   out2[k][0]=out2[k][1]= 0.0;


    q = fftw_plan_dft_c2r_1d(_dataFile->size(), out1, amplitude1, FFTW_ESTIMATE);
    fftw_execute(q);
    q = fftw_plan_dft_c2r_1d(_dataFile->size(), out2, amplitude2, FFTW_ESTIMATE);
    fftw_execute(q);

    DataFile * output = new DataFile;

    for (k = 0; k < _dataFile->size(); k++) {
        output->push_back(Point(amplitude[k],amplitude1[k]/((_dataFile->size()-1)),amplitude2[k]/((_dataFile->size()-1))));
    }

    /*DataFile * output = new DataFile;
    if (wRange > _dataFile->size()) wRange=_dataFile->size();
    for(k = 0; k < wRange; k++) {
        fprintf(fFreq,"%g\n",magnitude[k]);
    }
    fclose(fFreq);

    fclose(fo);*/
    fftw_destroy_plan(p);
    fftw_destroy_plan(q);
    free(amplitude);free(amplitude1);free(amplitude2);
    free(magnitude);
    fftw_free(out1);fftw_free(out2);

    return output;
}
