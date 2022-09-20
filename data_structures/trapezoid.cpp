#include "trapezoid.h"

/**
 * @brief Trapezoid's constructor.
 * @param leftp, the left point of the trapezoid
 * @param rightp, the right point of the trapezoid
 * @param tops, the top segment of the trapezoid
 * @param bottoms, the bottom segment of the trapezoid
 */
Trapezoid::Trapezoid(const size_t& leftp, const size_t& rightp,const size_t& tops, const size_t& bottoms):
     leftP(leftp),
     rightP(rightp),
     topS(tops),
     bottomS(bottoms),
     topLeft(std::numeric_limits<size_t>::max()),
     bottomLeft(std::numeric_limits<size_t>::max()),
     topRight(std::numeric_limits<size_t>::max()),
     bottomRight(std::numeric_limits<size_t>::max()),
     idDag(std::numeric_limits<size_t>::max())
{
}

