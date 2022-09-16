#include "dag.h"


/**
 * @brief DAG's contructor
 * @param firstNode, the root node of the DAG
 */
Dag::Dag()
{ 
    DagNode firstNode = DagNode(0,DagNode::trapezoidNode,std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
    dag.push_back(firstNode);
}

/**
 * @brief Insert a node of the DAG
 * @param newNode, the new node to be inserted in the DAG
 * @return the ID of the new Node in the DAG
 */
size_t Dag::insertNode(const DagNode& newNode){
    dag.push_back(newNode);
    return dag.size()-1;
}

/**
 * @brief Return a node of the DAG as a reference
 * @param node, the id of the node in the DAG
 */
const DagNode& Dag::getNode(const size_t& node) const{
    return dag[node];
}

/**
 * @brief Return all the elements of the DAG
 */
const std::vector<DagNode>& Dag::getDag() const {
    return dag;
}

/**
 * @brief Replace the node in a certain position in the DAG
 * @param oldNode, the id of the node to be replaced
 * @param newNode, the new node to be inserted in the DAG
 */
void Dag::replaceNode(const size_t& oldNode, const DagNode& newNode){
    dag[oldNode] = newNode;
}

/**
 * @brief Clear the vector of nodes
 */
void Dag::clear(){
    dag.clear();
}
