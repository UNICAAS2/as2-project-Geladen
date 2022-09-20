#include "drawablepolygon.h"
#include "cg3/utilities/timer.h"

/**
 * @brief DrawableTrapezoid's constructor.
 * @param topLeft, the top left point of the polygon
 * @param bottomLeft, the bottom left point of the polygon
 * @param topRight, the top right point of the polygon
 * @param bottomRight, the bottom right point of the polygon
 * @param trapezoid, a boolean that indicates whether this polygon is a trapezoid or a triangle
 */
DrawablePolygon::DrawablePolygon(const cg3::Point2d& topLeft,const cg3::Point2d& bottomLeft,const cg3::Point2d& topRight,const cg3::Point2d& bottomRight, const cg3::Color& randColor):
    topLeftPoint(topLeft),
    bottomLeftPoint(bottomLeft),
    topRightPoint(topRight),
    bottomRightPoint(bottomRight),
    color(randColor),
    isDeleted(false)
{
}
