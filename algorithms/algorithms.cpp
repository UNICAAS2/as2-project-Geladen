#include "algorithms.h"


void FollowSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids){

    size_t idTrapezoid;
    idTrapezoid = Search(map,dag,segment.p1(),segment.p2());


    while(segment.p2().x() > map.getPoint(map.getTrapezoid(idTrapezoid).getRightP()).x()){

        if(cg3::isPointAtLeft(segment.p1(),segment.p2(),map.getPoint(map.getTrapezoid(idTrapezoid).getRightP()))){
            idTrapezoid = map.getTrapezoid(idTrapezoid).getBottomRight();
            trapezoids.push_back(idTrapezoid);
        }
        else{
            idTrapezoid = map.getTrapezoid(idTrapezoid).getTopRight();
            trapezoids.push_back(idTrapezoid);
        }
    }
}

size_t Search(const TrapezoidalMap& map, const Dag& dag, const cg3::Point2d& point, const cg3::Point2d& point2){

    DagNode node = dag.getNode(0);
    cg3::Segment2d segment;

    while(node.getType() != DagNode::trapezoidNode){

        if(node.getType() == DagNode::pointNode){ // punto

            if(point.x() >= map.getPoint(node.getInfo()).x())
                node = dag.getNode(node.getRightChild()); // punto a destra
            else
                node = dag.getNode(node.getLeftChild()); //punto a sinistra
        }
        else{ //segmento
            segment = map.getSegment(node.getInfo());

            if(segment.p1().operator == (point) || segment.p2().operator == (point)){ // se `e sovrapposto al segmento

                if(cg3::isPointAtLeft(segment.p1(),segment.p2(),point2))
                    node = dag.getNode(node.getRightChild());
                else
                    node = dag.getNode(node.getLeftChild());
            }
            else{

                if(cg3::isPointAtLeft(segment.p1(),segment.p2(),point))
                    node = dag.getNode(node.getRightChild());
                else
                    node = dag.getNode(node.getLeftChild());
            }
        }
    }
    return node.getInfo();
}


void addTwoInDag(Dag dag, const size_t& oldNode, const size_t& idSegment, const size_t& leftTrapezoid, const size_t& rightTrapezoid){

    size_t idLeftTrapezoid, idRightTrapezoid;

    idLeftTrapezoid = dag.insertNode(DagNode(leftTrapezoid, DagNode::trapezoidNode));
    idRightTrapezoid = dag.insertNode(DagNode(rightTrapezoid, DagNode::trapezoidNode));

    DagNode newNode = DagNode(idSegment, DagNode::segmentNode, idLeftTrapezoid, idRightTrapezoid);
    dag.replaceNode(oldNode, newNode);
}
