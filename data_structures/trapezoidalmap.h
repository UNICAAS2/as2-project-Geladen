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
    void SplitFour(const cg3::Segment2d& segment, const size_t& trapezoid);
};

#endif // TRAPEZOIDALMAP_H
