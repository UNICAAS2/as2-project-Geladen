#include "dagnode.h"

/**
 * @brief DagNode's constructor
 * @param idInfo, the id of the element
 * @param nodeType, the type of the node
 */
DagNode::DagNode(const size_t& idInfo, const infoType& nodeType) {
    info = idInfo;
    type = nodeType;
    leftChild = std::numeric_limits<size_t>::max();
    rightChild = std::numeric_limits<size_t>::max();
}

/**
 * @brief DagNode's constructor
 * @param idInfo, the id of the element
 * @param nodeType, the type of the node
 * @paragraph idLeftChild, the id of the left child of the node
 * @paragraph idRightChild, the id of the right child of the node
 */
DagNode::DagNode(const size_t& idInfo, const infoType& nodeType, const size_t& idLeftChild, const size_t& idRightChild) {
    info = idInfo;
    type = nodeType;
    leftChild = idLeftChild;
    rightChild = idRightChild;
}


/**
 * @brief Return the index of the element
 */
const size_t& DagNode::getInfo() const{
    return info;
}

/**
 * @brief Return the type of the node
 */
const DagNode::infoType& DagNode::getType() const{
    return type;
}

/**
 * @brief Return the index of the right child stored in the DAG
 */
const size_t& DagNode::getRightChild() const{
    return rightChild;
}

/**
 * @brief Return the index of the left child stored in the DAG
 */
const size_t& DagNode::getLeftChild() const{
    return leftChild;
}

/**
 * @brief Set the index of the element
 */
void DagNode::setInfo(const size_t& idInfo){
    info = idInfo;
}

/**
 * @brief Set the type of the node
 */
void DagNode::setType(const infoType& nodeType){
    type = nodeType;
}

/**
 * @brief Set the index of the right child
 */
void DagNode::setRightChild(const size_t& idNode){
    rightChild = idNode;
}

/**
 * @brief Set the index of the left child
 */
void DagNode::setLeftChild(const size_t& idNode){
    leftChild = idNode;
}
