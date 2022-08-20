#include "dagnode.h"

DagNode::DagNode(const size_t& idInfo, const infoType& nodeType)
{
    info = idInfo;
    type = nodeType;
}

DagNode::DagNode(const size_t& idInfo, const infoType& nodeType, const size_t& idLeftChild, const size_t& idRightChild)
{
    info = idInfo;
    type = nodeType;
    leftChild = idLeftChild;
    rightChild = idRightChild;
}



const size_t& DagNode::getInfo() const{
    return info;
}

const DagNode::infoType& DagNode::getType() const{
    return type;
}

const size_t& DagNode::getRightChild() const{
    return rightChild;
}

const size_t& DagNode::getLeftChild() const{
    return leftChild;
}

void DagNode::setInfo(const size_t& idInfo){
    info = idInfo;
}

void DagNode::setType(const infoType& nodeType){
    type = nodeType;
}

void DagNode::setRightChild(const size_t& idNode){
    rightChild = idNode;
}

void DagNode::setLeftChild(const size_t& idNode){
    leftChild = idNode;
}
