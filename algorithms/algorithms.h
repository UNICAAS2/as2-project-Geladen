#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include <cg3/geometry/utils2.h>


void FollowSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids);
size_t Search(const TrapezoidalMap& map, const Dag& dag, const cg3::Point2d& point, const cg3::Point2d& point2);
void addTwoInDag(Dag dag, const size_t& oldNode, const size_t& idSegment, const size_t& leftTrapezoid, const size_t& rightTrapezoid);

#endif // ALGORITHMS_H
