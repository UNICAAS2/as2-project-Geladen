#include "drawablepolygon.h"

/**
 * @brief DrawableTrapezoid's constructor.
 * @param topLeft, the top left point of the polygon
 * @param bottomLeft, the bottom left point of the polygon
 * @param topRight, the top right point of the polygon
 * @param bottomRight, the bottom right point of the polygon
 * @param trapezoid, a boolean that indicates whether this polygon is a trapezoid or a triangle
 */
DrawablePolygon::DrawablePolygon(const cg3::Point2d& topLeft, const cg3::Point2d& bottomLeft,const cg3::Point2d& topRight,const cg3::Point2d& bottomRight, const bool trapezoid)
{
    topLeftPoint = topLeft;
    bottomLeftPoint= bottomLeft;
    topRightPoint = topRight;
    bottomRightPoint = bottomRight;
    isTrapezoid = trapezoid;
}

/**
 * @brief Return the top left point of the polygon as a reference
 */
const cg3::Point2d& DrawablePolygon::getTopLeftPoint() const{
    return topLeftPoint;
}

/**
 * @brief Return the bottom left point of the polygon as a reference
 */
const cg3::Point2d& DrawablePolygon::getBottomLeftPoint() const{
    return bottomLeftPoint;
}

/**
 * @brief Return the top right point of the polygon as a reference
 */
const cg3::Point2d& DrawablePolygon::getTopRightPoint() const{
    return topRightPoint;
}

/**
 * @brief Return the bottom right point of the polygon as a reference
 */
const cg3::Point2d& DrawablePolygon::getBottomRightPoint() const{
    return bottomRightPoint;
}


/**
 * @brief Set the top left point of the polygon
 */
void DrawablePolygon::setTopLeftPoint(const cg3::Point2d& point){
    topLeftPoint = point;
}

/**
 * @brief Set the bottom left point of the polygon
 */
void DrawablePolygon::setBottomLeftPoint(const cg3::Point2d& point){
    bottomLeftPoint = point;
}

/**
 * @brief Set the top right point of the polygon
 */
void DrawablePolygon::setTopRightPoint(const cg3::Point2d& point){
    topRightPoint = point;
}

/**
 * @brief Set the bottom right point of the polygon
 */
void DrawablePolygon::setBottomRightPoint(const cg3::Point2d& point){
    bottomRightPoint = point;
}
