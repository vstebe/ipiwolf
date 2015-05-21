#include "point.h"

#include "math.h"
/**
* \brief Default constructor for a Point object
*/
Point::Point()
{
}

/**
* \brief Constructor of a Point object
* \param x
* \param y
* \param z
*/
Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->xyz = 0;
}

float Point::getXYZ() {
    if(xyz == 0)
        xyz = sqrt(x*x+y*y+z*z);
    return xyz;
}

void Point::setXYZ(float xyz) {
    this->xyz = xyz;
}


std::ostream& operator << (std::ostream& O, const Point& p) {
    O << "Point X=" << p.x << " Y=" << p.y << " Z=" << p.z;
    return O;
}
