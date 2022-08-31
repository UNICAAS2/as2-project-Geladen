#ifndef TRAPEZOIDALMAP_H
#define TRAPEZOIDALMAP_H
#include <vector>
#include <unordered_map>
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
    std::vector<cg3::Point2d> points;
    std::vector<cg3::Segment2d> segments;
    std::vector<Trapezoid> map;
    std::vector<size_t> emptyIndexes;

    std::unordered_map<cg3::Point2d, size_t> pointMap;

public:
    TrapezoidalMap();
    const std::vector<Trapezoid>& getMap() const;

    size_t insertPoint(const cg3::Point2d& newPoint);
    size_t insertSegment(const cg3::Segment2d& newSegment);
    size_t insertTrapezoid(const Trapezoid& newTrapezoid);
    void replaceTrapezoid(const size_t& oldTrapezoid, const Trapezoid& newTrapezoid);
    const cg3::Point2d& getPoint(const size_t& idPoint) const;
    const cg3::Segment2d& getSegment(const size_t& idSegment) const;
    Trapezoid& getTrapezoid(const size_t& idTrapezoid);
    const Trapezoid& getTrapezoid(const size_t& idTrapezoid) const;
    size_t getMapSize() const;
    size_t getSegmentsSize() const;
    size_t getPointsSize() const;

    void splitFour(const size_t& trapezoid, std::vector<size_t>& trapezoids, const size_t& idP1, const size_t& idP2);
    void splitTwo(const size_t& trapezoid, const size_t& topAdjacent, const size_t& bottomAdjacent, std::vector<size_t>& trapezoids);
    void splitThreeLeft(const size_t& trapezoid, std::vector<size_t>& trapezoids, const size_t& idP1);
    void splitThreeRight(const size_t& trapezoid, const size_t& topAdjacent, const size_t& bottomAdjacent, std::vector<size_t>& trapezoids, const size_t& idP2);
    void mergeTwoTrapezoids(const size_t& leftTrapezoid, const size_t& rightTrapezoid);
    void mergeTrapezoids(std::vector<size_t>& trapezoids);
};

#endif // TRAPEZOIDALMAP_H
