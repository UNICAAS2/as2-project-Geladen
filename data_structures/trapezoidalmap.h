#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H
#include <vector>
#include "trapezoid.h"

#define MAX_DOUBLE std::numeric_limits<double>::max()
#define MIN_DOUBLE std::numeric_limits<double>::min()
#define OFFISIDE_NEXT_TOP 2
#define OFFISIDE_NEXT_BOTTOM 3
#define OFFISIDE_BOTTOM 1

/**
  * @brief This class implemets the trapezoidal map as a vector of trapezoids
  */
class TrapezoidalMap
{
private:
    std::vector<Trapezoid> map;
    std::vector<size_t> emptyIndexes;

public:
    TrapezoidalMap();
    const std::vector<Trapezoid>& getMap() const;
    void replaceTrapezoid(const size_t& oldTrapezoid, const Trapezoid& newTrapezoid);
    size_t insertTrapezoid(const Trapezoid &newTrapezoid);
    void splitFour(const cg3::Segment2d& segment, const size_t& trapezoid);
    void splitTwo(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent);
    void splitThreeLeft(const cg3::Segment2d& segment, const size_t& trapezoid);
    void splitThreeRight(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent);
    void mergeTwoTrapezoids(const size_t& leftTrapezoid,const size_t& rightTrapezoid);
    void mergeTrapezoids(std::vector<size_t>& trapezoids);
};

#endif // TRAPEZOIDALMAP_H
