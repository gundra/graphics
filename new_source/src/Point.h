#ifndef POINT_H
#define POINT_H

class Point
{
    public:
        float x;
        float y;
        float z;
};

#include <iostream>

std::ostream& operator << (std::ostream& lhs, const Point& rhs);

#endif /* POINT_H */
