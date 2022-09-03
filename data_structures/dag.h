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
    const DagNode& getNode(const size_t& node) const;
    const std::vector<DagNode>& getDag() const;
    void replaceNode(const size_t& oldNode, const DagNode& newNode);
};

#endif // DAG_H
