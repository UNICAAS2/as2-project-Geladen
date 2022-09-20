#ifndef DRAWABLEPOLYGON_H
#define DRAWABLEPOLYGON_H

#include <cg3/geometry/point2.h>
#include <cg3/utilities/color.h>



/**
  * @brief this class represents the polygon that will be used in the graphic part. Each trapezoid is made up of four points and a flag
  * that indicates whether the polygon is a trapezoid or a triangle
  */
class DrawablePolygon
{
public:
    DrawablePolygon(const cg3::Point2d& topLeft,
                    const cg3::Point2d& bottomLeft,
                    const cg3::Point2d& topRight,
                    const cg3::Point2d& bottomRight,
                    const cg3::Color& randColor);

    inline const cg3::Point2d& getTopLeftPoint() const;
    inline const cg3::Point2d& getBottomLeftPoint() const;
    inline const cg3::Point2d& getTopRightPoint() const;
    inline const cg3::Point2d& getBottomRightPoint() const;
    inline const cg3::Color& getColor() const;
    inline bool getIsDeleted() const;


    inline void setTopLeftPoint(const cg3::Point2d& point);
    inline void setBottomLeftPoint(const cg3::Point2d& point);
    inline void setTopRightPoint(const cg3::Point2d& point);
    inline void setBottomRightPoint(const cg3::Point2d& point);
    inline void setColor(const cg3::Color& newColor);
    inline void setIsDeleted(const bool& flag);


private:
    cg3::Point2d topLeftPoint;
    cg3::Point2d bottomLeftPoint;
    cg3::Point2d topRightPoint;
    cg3::Point2d bottomRightPoint;
    cg3::Color color;
    bool isDeleted;
};

#include "drawablepolygon.tpp"

#endif // DRAWABLEPOLYGON_H
