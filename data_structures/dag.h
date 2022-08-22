#ifndef DAG_H
#define DAG_H
#include "data_structures/dagnode.h"
#include <cg3/geometry/point2.h>

class Dag
{
private:
    std::vector<DagNode> dag;

public:
    Dag(const DagNode& firstNode);
    size_t insertNode(const DagNode& newNode);
    const std::vector<DagNode>& getDag() const;
    size_t replaceNode(const size_t& oldNode, const DagNode& newNode);
    //void addTwo(const size_t& oldNode, const size_t& idSegment, const size_t& topTrapezoid, const size_t& bottomTrapezoid);
    //void addThreeLeft(const size_t& oldNode, const size_t& idPoint, const size_t& idSegment, const size_t& LeftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid);
};

#endif // DAG_H
