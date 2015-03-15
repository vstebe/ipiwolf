#ifndef RESAMPLER_H
#define RESAMPLER_H
#include "QString"
#include "QDate"
#include "QFile"

class resampler
{
public:
    resampler();
    resampler(QString filename);
    void setFile (QString filename);


};

#endif // RESAMPLER_H
