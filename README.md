IPI Wolf Documentation
===================
IPI Wolf is a software program allowing you to resample and filter signals stored in the following text file format :
~~~~~~~~~~~~~
$File has 224955801 lines.                                                                                                                            
Logger date      Logger time     N       N prime         X       Y       Z 
15/05/2014      08:00:01        28      1       -0.141  -1.609  1.531
                                -0.109  -0.078  1.016
                                -0.109  -0.078  1.016
                                -0.094  -0.078  1
                                -0.094  -0.078  1.016
                                -0.094  -0.078  1
                                -0.094  -0.078  1.031
                                -0.094  -0.062  1.016
(***)
~~~~~~~~~~~~~
##Dependencies
This project use two dependencies :
* Qt 5.4
* FFTW 3.4

##How to compile
Simply enter the source directory and run these commands :
~~~~~~~~~~~~~
qmake
make
~~~~~~~~~~~~~