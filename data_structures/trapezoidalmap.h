#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H
#include <vector>
#include "trapezoid.h"

#define MAX_DOUBLE std::numeric_limits<double>::max()
#define MIN_DOUBLE std::numeric_limits<double>::min()

/**
  * @brief This class implemets the trapezoidal map as a vector of trapezoids
  */
class TrapezoidalMap
{
private:
    std::vector<Trapezoid> map;
    std::vector<size_t> empty_index;

public:
    TrapezoidalMap();
    const std::vector<Trapezoid>& getMap() const;
    void replaceTrapezoid(const size_t& oldTrapezoid, const Trapezoid& newTrapezoid);
    size_t insertTrapezoid(const Trapezoid &newTrapezoid);
    void SplitFour(const cg3::Segment2d& segment, const size_t& trapezoid);
    void SplitTwo(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent);
    void SplitThreeLeft(const cg3::Segment2d& segment, const size_t& trapezoid);
    void SplitThreeRight(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent);
};

#endif // TRAPEZOIDALMAP_H
