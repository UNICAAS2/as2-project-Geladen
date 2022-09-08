#ifndef DRAWABLEPOLYGON_H
#define DRAWABLEPOLYGON_H

#include <cg3/geometry/point2.h>


/**
  * @brief this class represents the polygon that will be used in the graphic part. Each trapezoid is made up of four points and a flag
  * that indicates whether the polygon is a trapezoid or a triangle
  */
class DrawablePolygon
{
public:
    DrawablePolygon(const cg3::Point2d& topLeft, const cg3::Point2d& bottomLeft,const cg3::Point2d& topRight,const cg3::Point2d& bottomRight, const bool trapezoid);

    const cg3::Point2d& getTopLeftPoint() const;
    const cg3::Point2d& getBottomLeftPoint() const;
    const cg3::Point2d& getTopRightPoint() const;
    const cg3::Point2d& getBottomRightPoint() const;

    void setTopLeftPoint(const cg3::Point2d& point);
    void setBottomLeftPoint(const cg3::Point2d& point);
    void setTopRightPoint(const cg3::Point2d& point);
    void setBottomRightPoint(const cg3::Point2d& point);


private:
    cg3::Point2d topLeftPoint;
    cg3::Point2d bottomLeftPoint;
    cg3::Point2d topRightPoint;
    cg3::Point2d bottomRightPoint;
    bool isTrapezoid;

};

#endif // DRAWABLEPOLYGON_H
