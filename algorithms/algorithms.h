#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include <cg3/geometry/utils2.h>


void followSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids);
size_t search(const TrapezoidalMap& map, const Dag& dag, const cg3::Point2d& point, const cg3::Point2d& point2);
void addFourInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& leftTrapezoid, const size_t& rightTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid);
void addTwoInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid);
void addThreeLInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid);
void addThreeRInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& rightTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid);

void updateMapAndDag(TrapezoidalMap& map,  Dag& dag, const cg3::Segment2d newSegment);


#endif // ALGORITHMS_H
