#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>


/**
  * @brief This class represents the trapezoids that will compose the trapzoidal map
  */
class Trapezoid
{

private:
    cg3::Point2d leftP;
    cg3::Point2d rightP;
    cg3::Segment2d topS;
    cg3::Segment2d bottomS;
    size_t topLeft; // adjacent trapezoid in top left
    size_t bottomLeft; // adjacent trapezoid in bottom left
    size_t topRight; // adjacent trapezoid in top right
    size_t bottomRight; // adjacent trapezoid in bottom right


public:
    Trapezoid(const cg3::Point2d& leftp, const cg3::Point2d& rightp,
              const cg3::Segment2d& tops, const cg3::Segment2d& bottoms);
    const cg3::Point2d& getLeftP() const;
    const cg3::Point2d& getRightP() const;
    const cg3::Segment2d& getTopS() const;
    const cg3::Segment2d& getBottomS() const;

    void setLeftP(const cg3::Point2d& point);
    void setRightP(const cg3::Point2d& point);
    void setTopS(const cg3::Segment2d& segment);
    void setBottomS(const cg3::Segment2d& segment);

    const size_t& getTopLeft() const;
    const size_t& getBottomLeft() const;
    const size_t& getTopRight() const;
    const size_t& getBottomRight() const;

    void setTopLeft(const size_t& trapezoid);
    void setBottomLeft(const size_t& trapezoid);
    void setTopRight(const size_t& trapezoid);
    void setBottomRight(const size_t& trapezoid);

};

#endif // TRAPEZOID_H
