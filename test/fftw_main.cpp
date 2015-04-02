#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fftw3.h>
#include <string.h>

double * genereDouble(double nbPoints) {
    double * tab = (double *) malloc(nbPoints * sizeof(double));
    
    for(int i=0; i<nbPoints; i++) {
         
        tab[i] = cos((2*3.14*i)/((double) 10));
        tab[i] += cos(4*(2*3.14*i)/((double) 10));
//         printf("%d %f\n", i, tab[i]);

    }
    
    return tab;
}




int main() {
    fftw_complex *out1, *buf;
    fftw_plan p, q;
    
    int longueur = 10000;
    double * in = genereDouble(longueur);
    
    out1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (longueur)); // basses freq nulles
    buf = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (longueur)); // basses freq nulles


    double * out2 = (double*) malloc(sizeof(double) * (longueur)); // basses freq nulles
    
    p = fftw_plan_dft_r2c_1d(longueur, in, out1, FFTW_ESTIMATE);
    fftw_execute(p);
    memcpy(buf, out1, longueur*sizeof(fftw_complex));
    q = fftw_plan_dft_c2r_1d(longueur, buf, out2, FFTW_ESTIMATE);
    fftw_execute(q);
    
    for(int i=0; i<longueur; i++) {
         printf("%d %f %f %f\n", i, in[i], sqrt(out1[i][0]*out1[i][0]+out1[i][1]+out1[i][1]), out2[i]/10000 + 1);
    }
    
    return 0;
    
}