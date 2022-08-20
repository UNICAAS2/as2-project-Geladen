#include "dag.h"

Dag::Dag(const DagNode& firstNode)
{ 
    dag.push_back(firstNode);
}

size_t Dag::insertNode(const DagNode& newNode){
    dag.push_back(newNode);
    return dag.size()-1;
}

void Dag::addTwo(const size_t& oldNode, const size_t& idSegment, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idTopTrapezoid, idBottomTrapezoid;

    dag[oldNode].setType(DagNode::segmentNode);
    dag[oldNode].setInfo(idSegment);

    idTopTrapezoid = insertNode(DagNode(topTrapezoid, DagNode::trapezoidNode));
    idBottomTrapezoid = insertNode(DagNode(bottomTrapezoid, DagNode::trapezoidNode));

    dag[oldNode].setLeftChild(idTopTrapezoid);
    dag[oldNode].setRightChild(idBottomTrapezoid);
}
