#include "algorithms.h"


void followSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids){

    size_t idTrapezoid;
    idTrapezoid = search(map,dag,segment.p1(),segment.p2());
    trapezoids.push_back(idTrapezoid);

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
                    node = dag.getNode(node.getLeftChild());
                else
                    node = dag.getNode(node.getRightChild());
            }
            else{

                if(cg3::isPointAtLeft(segment.p1(),segment.p2(),point))
                    node = dag.getNode(node.getLeftChild());
                else
                    node = dag.getNode(node.getRightChild());
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

    if(trapezoids.size() == 1){ //segment inside one trapezoid

        if(map.getPoint(map.getTrapezoid(trapezoids[0]).getLeftP()).x() == newSegment.p1().x()){

            if(map.getPoint(map.getTrapezoid(trapezoids[0]).getRightP()).x() == newSegment.p2().x()){

                map.splitTwo(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids);
                addTwoInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0],newTrapezoids[1]);
            }
            else{
                map.splitThreeRight(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids);
                addThreeRInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0],newTrapezoids[1],newTrapezoids[2]);

            }
        }
        else if(map.getPoint(map.getTrapezoid(trapezoids[0]).getRightP()).x() == newSegment.p2().x()){
            map.splitThreeLeft(trapezoids[0], newTrapezoids);
            addThreeLInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0],newTrapezoids[1],newTrapezoids[2]);
        }
        else{
            map.splitFour(trapezoids[0], newTrapezoids);
            addFourInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0],newTrapezoids[1],newTrapezoids[2],newTrapezoids[3]);
        }
    }
    else{

        if(map.getPoint(map.getTrapezoid(trapezoids[0]).getLeftP()).x() == newSegment.p1().x()){
            newTrapezoids.push_back(std::numeric_limits<size_t>::max());
            map.splitTwo(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids);
        }
        else
            map.splitThreeLeft(trapezoids[0],newTrapezoids);

        size_t i=1;
        while(i < trapezoids.size()-1){ // finche ci sono elementi nel vettore?
            map.splitTwo(trapezoids[i],newTrapezoids[newTrapezoids.size()-2],newTrapezoids[newTrapezoids.size()-1], newTrapezoids);
            i++;
        }

        if(map.getPoint(map.getTrapezoid(trapezoids[trapezoids.size()-1]).getRightP()).x() == newSegment.p2().x()){
            map.splitTwo(trapezoids[i],newTrapezoids[newTrapezoids.size()-2],newTrapezoids[newTrapezoids.size()-1], newTrapezoids);
            newTrapezoids.push_back(std::numeric_limits<size_t>::max());
        }
        else
            map.splitThreeRight(trapezoids[trapezoids.size()-1], newTrapezoids[newTrapezoids.size()-2], newTrapezoids[newTrapezoids.size()-1], newTrapezoids);



        map.mergeTrapezoids(newTrapezoids);

        if(newTrapezoids[0] == std::numeric_limits<size_t>::max())
            addTwoInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[1],newTrapezoids[2]);
        else
            addThreeLInDag(map,dag,map.getTrapezoid(trapezoids[0]).getIdDag(),newTrapezoids[0], newTrapezoids[1],newTrapezoids[2]);

        i=3;
        while(i < newTrapezoids.size()-3){
            addTwoInDag(map,dag,map.getTrapezoid(trapezoids[i/2]).getIdDag(),newTrapezoids[i],newTrapezoids[i+1]);
            i+=2;
        }

        if(newTrapezoids[newTrapezoids.size()-1] == std::numeric_limits<size_t>::max())

            addTwoInDag(map,dag,map.getTrapezoid(trapezoids[trapezoids.size()-1]).getIdDag(),newTrapezoids[newTrapezoids.size()-3],newTrapezoids[newTrapezoids.size()-2]);
        else
            addThreeRInDag(map,dag,map.getTrapezoid(trapezoids[trapezoids.size()-1]).getIdDag(),newTrapezoids[newTrapezoids.size()-3], newTrapezoids[newTrapezoids.size()-2],newTrapezoids[newTrapezoids.size()-1]);


    }

    trapezoids.clear();
    newTrapezoids.clear();

}

void addFourInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid, const size_t& rightTrapezoid){

    size_t idSegment, idP1, idP2, idSegmentNode, idP2Node, idLeftTrapezoid, idRightTrapezoid, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;
    idP1 = map.getPointsSize()-2;
    idP2 = map.getPointsSize()-1;

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
    dag.replaceNode(oldNode, p1Node);

    map.getTrapezoid(leftTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(rightTrapezoid).setIdDag(idRightTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}

void addTwoInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

    size_t idSegment, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
        map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
        map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    dag.replaceNode(oldNode,segmentNode);

}


void addThreeLInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid){

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


void addThreeRInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid, const size_t& rightTrapezoid){

    size_t idSegment, idP2, idSegmentNode, idLeftTrapezoid, idRightTrapezoid, idTopTrapezoid, idBottomTrapezoid;

    idSegment = map.getSegmentsSize()-1;
    idP2 = map.getPointsSize()-1;

    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
        map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
        map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    idSegmentNode = dag.insertNode(segmentNode);

    DagNode rightTrapezoidNode = DagNode(rightTrapezoid, DagNode::trapezoidNode, std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max());
    idRightTrapezoid = dag.insertNode(rightTrapezoidNode);

    DagNode p2Node = DagNode(idP2, DagNode::pointNode,idSegmentNode,idRightTrapezoid);
    dag.replaceNode(oldNode,p2Node);

    map.getTrapezoid(rightTrapezoid).setIdDag(idRightTrapezoid);
}
