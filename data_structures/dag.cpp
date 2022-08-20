#include "dag.h"

Dag::Dag(const DagNode& firstNode)
{ 
    dag.push_back(firstNode);
}

size_t Dag::insertNode(const DagNode& newNode){
    dag.push_back(newNode);
    return dag.size()-1;
}
