#include "drawablepolygon.h"

/**
 * @brief DrawableTrapezoid's constructor.
 * @param topLeft, the top left point of the polygon
 * @param bottomLeft, the bottom left point of the polygon
 * @param topRight, the top right point of the polygon
 * @param bottomRight, the bottom right point of the polygon
 * @param trapezoid, a boolean that indicates whether this polygon is a trapezoid or a triangle
 */
DrawablePolygon::DrawablePolygon(const cg3::Point2d& topLeft,const cg3::Point2d& bottomLeft,const cg3::Point2d& topRight,const cg3::Point2d& bottomRight)
{
    std::mt19937 rng;

    topLeftPoint = topLeft;
    bottomLeftPoint = bottomLeft;
    topRightPoint = topRight;
    bottomRightPoint = bottomRight;
    isDeleted = false;

    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> dist(0,244);
    color = cg3::Color(dist(rng),dist(rng),dist(rng));
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
 * @brief Return the color of the polygon as a reference
 */
const cg3::Color& DrawablePolygon::getColor() const{
    return color;
}

/**
 * @brief Set the color of the polygon
 */
void DrawablePolygon::setColor(const cg3::Color& newColor){
    color = newColor;
}

/**
 * @brief Return the flag to to check if the polygon has been deleted
 */
bool DrawablePolygon::getIsDeleted() const{
    return isDeleted;
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

/**
 * @brief Set the flag to to check if the polygon has been deleted
 */
void DrawablePolygon::setIsDeleted(const bool& flag){
    isDeleted = flag;
}
