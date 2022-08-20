#ifndef DAGNODE_H
#define DAGNODE_H
#include <cg3/geometry/point2.h>


/**
  * @brief This class represents the node that will compose the Dag
  */
class DagNode
{

public:
    enum infoType {point, segment, trapezoid};

    DagNode(const size_t& idInfo, const infoType& nodeType);

    DagNode(const size_t& idInfo, const infoType& nodeType, const size_t& idLeftChild, const size_t& idRightChild);

    const size_t& getInfo() const;
    const infoType& getType() const;
    const size_t& getRightChild() const;
    const size_t& getLeftChild() const;

    void setInfo(const size_t& info);
    void setType(const infoType& type);
    void setRightChild(const size_t& node);
    void setLeftChild(const size_t& node);

private:
    size_t info;
    infoType type;
    size_t rightChild;
    size_t leftChild;
};

#endif // DAGNODE_H
