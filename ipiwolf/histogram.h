#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QVector>
#include <QSharedPointer>

struct HistogramPoint {
    double frequency;
    double amplitude;
};

typedef QVector<HistogramPoint> Histogram;
typedef QSharedPointer<Histogram> HistogramPtr;

std::ostream& operator << (std::ostream& O, const Histogram& d);


#endif // HISTOGRAM_H

