#include "drawablepolygon.h"

/**
 * @brief Return the top left point of the polygon as a reference
 */
inline const cg3::Point2d& DrawablePolygon::getTopLeftPoint() const{
    return topLeftPoint;
}

/**
 * @brief Return the bottom left point of the polygon as a reference
 */
inline const cg3::Point2d& DrawablePolygon::getBottomLeftPoint() const{
    return bottomLeftPoint;
}

/**
 * @brief Return the top right point of the polygon as a reference
 */
inline const cg3::Point2d& DrawablePolygon::getTopRightPoint() const{
    return topRightPoint;
}

/**
 * @brief Return the bottom right point of the polygon as a reference
 */
inline const cg3::Point2d& DrawablePolygon::getBottomRightPoint() const{
    return bottomRightPoint;
}

/**
 * @brief Return the color of the polygon as a reference
 */
inline const cg3::Color& DrawablePolygon::getColor() const{
    return color;
}

/**
 * @brief Set the color of the polygon
 */
inline void DrawablePolygon::setColor(const cg3::Color& newColor){
    color = newColor;
}

/**
 * @brief Return the flag to to check if the polygon has been deleted
 */
inline bool DrawablePolygon::getIsDeleted() const{
    return isDeleted;
}


/**
 * @brief Set the top left point of the polygon
 */
inline void DrawablePolygon::setTopLeftPoint(const cg3::Point2d& point){
    topLeftPoint = point;
}

/**
 * @brief Set the bottom left point of the polygon
 */
inline void DrawablePolygon::setBottomLeftPoint(const cg3::Point2d& point){
    bottomLeftPoint = point;
}

/**
 * @brief Set the top right point of the polygon
 */
inline void DrawablePolygon::setTopRightPoint(const cg3::Point2d& point){
    topRightPoint = point;
}

/**
 * @brief Set the bottom right point of the polygon
 */
inline void DrawablePolygon::setBottomRightPoint(const cg3::Point2d& point){
    bottomRightPoint = point;
}

/**
 * @brief Set the flag to to check if the polygon has been deleted
 */
inline void DrawablePolygon::setIsDeleted(const bool& flag){
    isDeleted = flag;
}
