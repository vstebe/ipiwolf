#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point
{
public:
    Point();
    Point(float x, float y, float z);
    void setXYZ(float xyz);
    float getXYZ();
    float x;
    float y;
    float z;
    float xyz;


};

std::ostream& operator << (std::ostream& O, const Point& p);

#endif // POINT_H
