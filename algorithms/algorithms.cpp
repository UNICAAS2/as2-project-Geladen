#include "algorithms.h"


void followSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids){

    size_t idTrapezoid;
    idTrapezoid = search(map,dag,segment.p1(),segment.p2());


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

size_t search(const TrapezoidalMap& map, const Dag& dag, const cg3::Point2d& point, const cg3::Point2d& point2){

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


void updateMapAndDag(TrapezoidalMap& map,  Dag& dag, const cg3::Segment2d newSegment){

    std::vector<size_t> trapezoids, newTrapezoids;
    size_t idSegment, idP1, idP2;

    idSegment = map.insertSegment(newSegment);
    idP1 = map.insertPoint(newSegment.p1());
    idP2 = map.insertPoint(newSegment.p2());
    followSegment(map, dag, newSegment, trapezoids);

    if(trapezoids.size() == 1){ //segment inside one trapezoid -> split4
        map.splitFour(trapezoids[0], newTrapezoids);
        addFourInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0],newTrapezoids[1],newTrapezoids[2],newTrapezoids[3]);
    }
    else{

        size_t i=0;
        while(true){ // finche ci sono elementi nel vettore?

            if (newSegment.p1().x() != map.getPoint(map.getTrapezoid(trapezoids[0]).getLeftP()).x()){

                //split3 sinistra

            }
            else if(newSegment.p2().x() != map.getPoint(map.getTrapezoid(trapezoids.size()-1).getRightP()).x()){

                //spit 3 a destra
            }
            else{

                // split2
                //addTwoInDag();
            }

        }
    }

}

void addFourInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& leftTrapezoid, const size_t& rightTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idSegment, idP1, idP2, idSegmentNode, idP2Node, idLeftTrapezoid, idRightTrapezoid, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;
    idP1 = map.getPointsSize()-2;
    idP2 = map.getMapSize()-1;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idTopTrapezoid = dag.insertNode(topTrapezoidNode);
    idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode,idTopTrapezoid,idBottomTrapezoid);
    idSegmentNode = dag.insertNode(segmentNode);

    DagNode rightTrapezoidNode = DagNode(rightTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idRightTrapezoid = dag.insertNode(rightTrapezoidNode);

    DagNode p2Node = DagNode(idP2, DagNode::pointNode,idSegmentNode,idRightTrapezoid);
    idP2Node = dag.insertNode(p2Node);

    DagNode leftTrapezoidNode = DagNode(leftTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idLeftTrapezoid = dag.insertNode(leftTrapezoidNode);

    DagNode p1Node = DagNode(idP1, DagNode::pointNode,idLeftTrapezoid,idP2Node);
    dag.replaceNode(oldNode,p1Node);

    map.getTrapezoid(leftTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(rightTrapezoid).setIdDag(idRightTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}

void addTwoInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idSegment, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    dag.replaceNode(oldNode,segmentNode);

    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}


void addThreeLInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idSegment, idP1, idSegmentNode, idLeftTrapezoid, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;
    idP1 = map.getPointsSize()-2;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idTopTrapezoid = dag.insertNode(topTrapezoidNode);
    idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode,idTopTrapezoid,idBottomTrapezoid);
    idSegmentNode = dag.insertNode(segmentNode);

    DagNode leftTrapezoidNode = DagNode(leftTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idLeftTrapezoid = dag.insertNode(leftTrapezoidNode);

    DagNode p1Node = DagNode(idP1, DagNode::pointNode,idLeftTrapezoid,idSegmentNode);
    dag.replaceNode(oldNode,p1Node);

    map.getTrapezoid(leftTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}


void addThreeRInDag(TrapezoidalMap& map, Dag& dag, const size_t& oldNode, const size_t& rightTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idSegment, idP2, idSegmentNode, idLeftTrapezoid, idRightTrapezoid, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;
    idP2 = map.getMapSize()-1;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    idSegmentNode = dag.insertNode(segmentNode);

    DagNode rightTrapezoidNode = DagNode(rightTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idRightTrapezoid = dag.insertNode(rightTrapezoidNode);

    DagNode p2Node = DagNode(idP2, DagNode::pointNode,idSegmentNode,idRightTrapezoid);
    dag.replaceNode(oldNode,p2Node);

    map.getTrapezoid(rightTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}
