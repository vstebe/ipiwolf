#ifndef POINT_H
#define POINT_H

#include <iostream>

/**
 * @brief Class representing a 3-axe point of a signal
 */
class Point
{
public:
    /**
     * @brief Constructs a point (0,0,0)
     */
    Point();

    /**
     * @brief Constructs a point with the given values
     * @param x x value to set
     * @param y y value to set
     * @param z z value to set
     */
    Point(float x, float y, float z);

    /**
     * @brief Sets the norm of the point if the signal has been filtered on the magnitude
     * @param xyz magnitude to set
     */
    void setXYZ(float xyz);

    /**
     * @brief Get the norm of the point (standard norm-2 of the point or a custom value if it has been set)
     * @return norm of the point
     */
    float getXYZ();
    float x;
    float y;
    float z;
    float xyz;


};

std::ostream& operator << (std::ostream& O, const Point& p);

#endif // POINT_H
