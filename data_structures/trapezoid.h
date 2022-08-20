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
    size_t leftP;
    size_t rightP;
    size_t topS;
    size_t bottomS;
    size_t topLeft; // adjacent trapezoid in top left
    size_t bottomLeft; // adjacent trapezoid in bottom left
    size_t topRight; // adjacent trapezoid in top right
    size_t bottomRight; // adjacent trapezoid in bottom right


public:
    Trapezoid(const size_t& leftp, const size_t& rightp,
              const size_t& tops, const size_t& bottoms);
    const size_t& getLeftP() const;
    const size_t& getRightP() const;
    const size_t& getTopS() const;
    const size_t& getBottomS() const;

    void setLeftP(const size_t& point);
    void setRightP(const size_t& point);
    void setTopS(const size_t& segment);
    void setBottomS(const size_t& segment);

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
