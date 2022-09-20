#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>


/**
  * @brief This class represents the trapezoids that will compose the trapzoidal. A trapezoid is composed by two points leftP and rightP,
  * two segments topS and topS, each trapezoid can have zero to four neighbors topLeft bottomLeft topRoght bottomRight. All the attributes
  * that make up the class are of type size_t which represent the indices of the elements stored in the TrapezoidalMap.
  * In addition, the class contains a index, idDag, representing the position of the trapezoid in the dag.
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

    size_t idDag;

public:
    Trapezoid(const size_t& leftp, const size_t& rightp,
              const size_t& tops, const size_t& bottoms);

    inline const size_t& getLeftP() const;
    inline const size_t& getRightP() const;
    inline const size_t& getTopS() const;
    inline const size_t& getBottomS() const;

    inline void setLeftP(const size_t& point);
    inline void setRightP(const size_t& point);
    inline void setTopS(const size_t& segment);
    inline void setBottomS(const size_t& segment);

    inline const size_t& getTopLeft() const;
    inline const size_t& getBottomLeft() const;
    inline const size_t& getTopRight() const;
    inline const size_t& getBottomRight() const;

    inline void setTopLeft(const size_t& trapezoid);
    inline void setBottomLeft(const size_t& trapezoid);
    inline void setTopRight(const size_t& trapezoid);
    inline void setBottomRight(const size_t& trapezoid);

    inline const size_t& getIdDag() const;
    inline void setIdDag(const size_t& id);
};

#include "trapezoid.tpp"

#endif // TRAPEZOID_H
