#include "dag.h"

Dag::Dag(const DagNode& firstNode)
{ 
    dag.push_back(firstNode);
}

size_t Dag::insertNode(const DagNode& newNode){
    dag.push_back(newNode);
    return dag.size()-1;
}

const DagNode Dag::getNode(const size_t& node) const{
    return dag[node];
}

const std::vector<DagNode>& Dag::getDag() const {
    return dag;
}

void Dag::replaceNode(const size_t& oldNode, const DagNode& newNode){
    dag[oldNode] = newNode;
}
