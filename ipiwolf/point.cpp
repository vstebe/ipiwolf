#include "point.h"
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
}
