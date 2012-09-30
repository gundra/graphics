#include "Point.h"

std::ostream& operator << (std::ostream& lhs, const Point& rhs)
{
    lhs << "[" << rhs.x << ":" << rhs.y << "]";

    return lhs;
}


