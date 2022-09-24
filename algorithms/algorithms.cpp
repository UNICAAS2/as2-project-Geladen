#include "algorithms.h"

namespace Algorithms {

/**
 * @brief Given a segment finds all trapezoids intersected by that segment and places them in the vector trapezoids
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the Dag in which perform the search
 * @param segment, the new inserted segment
 * @param trapezoids, the vector that will contain the trapezoids intersected by the new segment
 */
void followSegment(const TrapezoidalMap& map, const Dag& dag, const cg3::Segment2d& segment, std::vector<size_t>& trapezoids) {

    //Id of the trapezoid to which the first endpoint of the segment belongs
    size_t idTrapezoid = search(map,dag,segment.p1(),segment.p2());
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

/**
 * @brief Search which trapezoid an input point belongs to
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag in which perform the search
 * @param point, the point to be searched
 * @param point2, the second point of a segment, it is useful if the first point is equal to a point in the dag
 * @return the index of the trapzoid found in the trapezoidal map
 */
size_t search(const TrapezoidalMap& map, const Dag& dag, const cg3::Point2d& point, const cg3::Point2d& point2) {

    DagNode node = dag.getNode(0);
    cg3::Segment2d segment;

    while(node.getType() != DagNode::trapezoidNode){

        //If the current node is a point
        if(node.getType() == DagNode::pointNode){

            if(point.x() >= map.getPoint(node.getInfo()).x())
                node = dag.getNode(node.getRightChild()); // punto a destra
            else
                node = dag.getNode(node.getLeftChild()); //punto a sinistra
        }
        else{ //If the current node is a segment
            segment = map.getSegment(node.getInfo());

            //If the point is equal to an endpoint of the segment
            if(segment.p1().operator == (point) || segment.p2().operator == (point)){
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

/**
 * @brief Given a segment this function updates the trapezoidal map and the dag
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag in which perform the search
 * @param newSegment, the new segment inserted
 */
void updateMapAndDag(TrapezoidalMap& map,  Dag& dag, const cg3::Segment2d newSegment) {

    std::vector<size_t> trapezoids, newTrapezoids;

    //Insert the segment and points into their respective vectors
    map.insertSegment(newSegment);
    size_t idP1 = map.insertPoint(newSegment.p1());
    size_t idP2 = map.insertPoint(newSegment.p2());

    //Search which trapezoids the new segment belongs to
    followSegment(map, dag, newSegment, trapezoids);

    //if the segment belongs to only one trapezoid
    if(trapezoids.size() == 1){

        if(map.getPoint(map.getTrapezoid(trapezoids[0]).getLeftP()).x() == newSegment.p1().x()){

            if(map.getPoint(map.getTrapezoid(trapezoids[0]).getRightP()).x() == newSegment.p2().x()){
                // Split the trapezoid in 2 new trapezoids, push them in the vector of new trapezoids and update the dag
                map.splitTwo(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids);
                map.setNewTrapezoids(newTrapezoids);
                addTwoInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[0], newTrapezoids[1]);
            }
            else{
                // Split the trapezoid in 3 new trapezoids, push them in the vector of new trapezoids and update the dag
                map.splitThreeRight(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids, idP2);
                map.setNewTrapezoids(newTrapezoids);
                addThreeRInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[0], newTrapezoids[1], newTrapezoids[2], idP2);

            }
        }
        else if(map.getPoint(map.getTrapezoid(trapezoids[0]).getRightP()).x() == newSegment.p2().x()){
            // Split the trapezoid in 3 new trapezoids, push them in the vector of new trapezoids and update the dag
            map.splitThreeLeft(trapezoids[0], newTrapezoids,idP1);
            map.setNewTrapezoids(newTrapezoids);
            addThreeLInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[0], newTrapezoids[1], newTrapezoids[2],idP1);
        }
        else{
            // Split the trapezoid in 4 new trapezoids, push them in the vector of new trapezoids and update the dag
            map.splitFour(trapezoids[0], newTrapezoids, idP1,idP2);
            map.setNewTrapezoids(newTrapezoids);
            addFourInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[0], newTrapezoids[1], newTrapezoids[2], newTrapezoids[3], idP1, idP2);
        }
    }
    else{ //If the segment belongs to more than one trapezoid

        //Split the first trapezoid into 3 or 2 new trazoids
        if(map.getPoint(map.getTrapezoid(trapezoids[0]).getLeftP()).x() == newSegment.p1().x()){
            newTrapezoids.push_back(std::numeric_limits<size_t>::max());
            map.splitTwo(trapezoids[0], std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max(), newTrapezoids);
        }
        else
            map.splitThreeLeft(trapezoids[0],newTrapezoids,idP1);

        // Split the trapezoids between the first and the last, in 2 new trapezoids
        size_t i=1;
        while(i < trapezoids.size()-1){
            map.splitTwo(trapezoids[i], newTrapezoids[newTrapezoids.size()-2], newTrapezoids[newTrapezoids.size()-1], newTrapezoids);
            i++;
        }

        //Split the last trapezoid into 3 or 2 new trazoids
        if(map.getPoint(map.getTrapezoid(trapezoids[trapezoids.size()-1]).getRightP()).x() == newSegment.p2().x()){
            map.splitTwo(trapezoids[i], newTrapezoids[newTrapezoids.size()-2], newTrapezoids[newTrapezoids.size()-1], newTrapezoids);
            newTrapezoids.push_back(std::numeric_limits<size_t>::max());
        }
        else
            map.splitThreeRight(trapezoids[trapezoids.size()-1], newTrapezoids[newTrapezoids.size()-2], newTrapezoids[newTrapezoids.size()-1], newTrapezoids,idP2);

        //Update the vector of new trapezoids in the map
        map.setNewTrapezoids(newTrapezoids);
        //Merge the adjacent trapezoids obtained after splitting
        map.mergeTrapezoids(newTrapezoids);


        //Update the dag
        if(newTrapezoids[0] == std::numeric_limits<size_t>::max())
            addTwoInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[1], newTrapezoids[2]);
        else
            addThreeLInDag(map, dag, map.getTrapezoid(trapezoids[0]).getIdDag(), newTrapezoids[0], newTrapezoids[1], newTrapezoids[2], idP1);

        i=3;
        while(i < newTrapezoids.size()-3){
            addTwoInDag(map, dag, map.getTrapezoid(trapezoids[i/2]).getIdDag(), newTrapezoids[i], newTrapezoids[i+1]);
            i+=2;
        }

        if(newTrapezoids[newTrapezoids.size()-1] == std::numeric_limits<size_t>::max())
            addTwoInDag(map, dag, map.getTrapezoid(trapezoids[trapezoids.size()-1]).getIdDag(),newTrapezoids[newTrapezoids.size()-3], newTrapezoids[newTrapezoids.size()-2]);
        else
            addThreeRInDag(map, dag, map.getTrapezoid(trapezoids[trapezoids.size()-1]).getIdDag(), newTrapezoids[newTrapezoids.size()-3], newTrapezoids[newTrapezoids.size()-2], newTrapezoids[newTrapezoids.size()-1], idP2);
    }
}

/**
 * @brief Update the Dag by adding 4 new trapezoids: left, top, bottom, right and the necessary points and segments
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag to be updated
 * @param oldNode, the node that contains and old trapezoid
 * @param leftTrapezoid, the new left trapezoid inserted in the map
 * @param topTrapezoid, the new top trapezoid inserted in the map
 * @param bottomTrapezoid, the new bottom trapezoid inserted in the map
 * @param rightTrapezoid, the new right trapezoid inserted in the map
 * @param idP1, ID of the first endpoint of the new insterted segment
 * @param idP2, ID of the second endpoint of the new insterted segment
 */
void addFourInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid, const size_t& rightTrapezoid, const size_t& idP1, const size_t& idP2) {

    //Id of the new inserted segment
    size_t idSegment = map.getSegmentsSize()-1;

    //Update the id of the dag contained in the old trapezoid
    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    //Insert the nodes of the top and bottom trapezoids into the Dag
    DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode);
    DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode);
    size_t idTopTrapezoid = dag.insertNode(topTrapezoidNode);
    size_t idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);

    //Insert the node of the segment in the Dag
    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode,idTopTrapezoid,idBottomTrapezoid);
    size_t idSegmentNode = dag.insertNode(segmentNode);

    //Insert the node of the right trapezoid in the Dag
    DagNode rightTrapezoidNode = DagNode(rightTrapezoid, DagNode::trapezoidNode);
    size_t idRightTrapezoid = dag.insertNode(rightTrapezoidNode);

    //Insert the node of the second endpoint of the segment in the Dag
    DagNode p2Node = DagNode(idP2, DagNode::pointNode,idSegmentNode,idRightTrapezoid);
    size_t idP2Node = dag.insertNode(p2Node);

    //Insert the node of the left trapezoid in the Dag
    DagNode leftTrapezoidNode = DagNode(leftTrapezoid, DagNode::trapezoidNode);
    size_t idLeftTrapezoid = dag.insertNode(leftTrapezoidNode);

    //Insert the node of the first endpoint of the segment in the Dag
    DagNode p1Node = DagNode(idP1, DagNode::pointNode,idLeftTrapezoid,idP2Node);
    dag.replaceNode(oldNode, p1Node);

    //Update the id of the Dag for each trapezoid
    map.getTrapezoid(leftTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(rightTrapezoid).setIdDag(idRightTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}

/**
 * @brief Update the Dag by adding 2 new trapezoids and the necessary points and segments
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag to be updated
 * @param oldNode, the node that contains and old trapezoid
 * @param topTrapezoid, the new top trapezoid inserted in the map
 * @param bottomTrapezoid, the new bottom trapezoid inserted in the map
 */
void addTwoInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid) {

    size_t idSegment, idTopTrapezoid, idBottomTrapezoid;

    //Id of the new inserted segment
    idSegment = map.getSegmentsSize()-1;

    //Update the id of the dag contained in the old trapezoid
    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    //Update the node of the segment and insert the node of the top trapezoid if it's not already inserted in the Dag
    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode);
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
        map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    //Update the node of the segment and insert the node of the bottom trapezoid if it's not already inserted in the Dag
    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode);
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
        map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    //Insert the node of the segment in the Dag
    dag.replaceNode(oldNode,segmentNode);

}

/**
 * @brief Update the Dag by adding 3 new trapezoids: left, top, bottom and the necessary points and segments
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag to be updated
 * @param oldNode, the node that contains and old trapezoid
 * @param leftTrapezoid, the new left trapezoid inserted in the map
 * @param topTrapezoid, the new top trapezoid inserted in the map
 * @param bottomTrapezoid, the new bottom trapezoid inserted in the map
 * @param idP1, ID of the first endpoint of the new insterted segment
 */
void addThreeLInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& leftTrapezoid, const size_t& topTrapezoid, const size_t& bottomTrapezoid, const size_t& idP1) {

    //Id of the new inserted segment
    size_t idSegment = map.getSegmentsSize()-1;

    //Update the id of the dag contained in the old trapezoid
    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    //Insert the nodes of the top and bottom trapezoids into the Dag
    DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode);
    DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode);
    size_t idTopTrapezoid = dag.insertNode(topTrapezoidNode);
    size_t idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);

    //Insert the node of the segment in the Dag
    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode,idTopTrapezoid,idBottomTrapezoid);
    size_t idSegmentNode = dag.insertNode(segmentNode);

    //Insert the node of the left trapezoid in the Dag
    DagNode leftTrapezoidNode = DagNode(leftTrapezoid, DagNode::trapezoidNode);
    size_t idLeftTrapezoid = dag.insertNode(leftTrapezoidNode);

    //Insert the node of the first endpoint of the segment in the Dag
    DagNode p1Node = DagNode(idP1, DagNode::pointNode,idLeftTrapezoid,idSegmentNode);
    dag.replaceNode(oldNode,p1Node);

    //Update the id of the Dag for each trapezoid
    map.getTrapezoid(leftTrapezoid).setIdDag(idLeftTrapezoid);
    map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
}


/**
 * @brief Update the Dag by adding 3 new trapezoids: top, bottom, right and the necessary points and segments
 * @param map, the trapezoidal map (vector of trapezoids)
 * @param dag, the dag to be updated
 * @param oldNode, the node that contains and old trapezoid
 * @param topTrapezoid, the new top trapezoid inserted in the map
 * @param bottomTrapezoid, the new bottom trapezoid inserted in the map
 * @param rightTrapezoid, the new right trapezoid inserted in the map
 * @param idP2, ID of the second endpoint of the new insterted segment
 */
void addThreeRInDag(TrapezoidalMap& map, Dag& dag, const size_t oldNode, const size_t& topTrapezoid, const size_t& bottomTrapezoid, const size_t& rightTrapezoid,const size_t& idP2) {

    size_t idTopTrapezoid, idBottomTrapezoid;

    //Id of the new inserted segment
    size_t idSegment = map.getSegmentsSize()-1;

    //Update the id of the dag contained in the old trapezoid
    map.getTrapezoid(dag.getNode(oldNode).getInfo()).setIdDag(std::numeric_limits<size_t>::max());

    DagNode segmentNode = DagNode(idSegment, DagNode::segmentNode);

    //Update the node of the segment and insert the node of the top trapezoid if it's not already inserted in the Dag
    if(map.getTrapezoid(topTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode topTrapezoidNode = DagNode(topTrapezoid, DagNode::trapezoidNode);
        idTopTrapezoid = dag.insertNode(topTrapezoidNode);
        segmentNode.setLeftChild(idTopTrapezoid);
        map.getTrapezoid(topTrapezoid).setIdDag(idTopTrapezoid);
    }
    else
        segmentNode.setLeftChild(map.getTrapezoid(topTrapezoid).getIdDag());

    //Update the node of the segment and insert the node of the bottom trapezoid if it's not already inserted in the Dag
    if(map.getTrapezoid(bottomTrapezoid).getIdDag() == std::numeric_limits<size_t>::max()){
        DagNode bottomTrapezoidNode = DagNode(bottomTrapezoid, DagNode::trapezoidNode);
        idBottomTrapezoid = dag.insertNode(bottomTrapezoidNode);
        segmentNode.setRightChild(idBottomTrapezoid);
        map.getTrapezoid(bottomTrapezoid).setIdDag(idBottomTrapezoid);
    }
    else
        segmentNode.setRightChild(map.getTrapezoid(bottomTrapezoid).getIdDag());

    //Insert the node of the segment in the Dag
    size_t idSegmentNode = dag.insertNode(segmentNode);

    //Insert the nodes of the right trapezoids into the Dag
    DagNode rightTrapezoidNode = DagNode(rightTrapezoid, DagNode::trapezoidNode);
    size_t idRightTrapezoid = dag.insertNode(rightTrapezoidNode);

    //Insert the node of the second endpoint of the segment in the Dag
    DagNode p2Node = DagNode(idP2, DagNode::pointNode,idSegmentNode,idRightTrapezoid);
    dag.replaceNode(oldNode,p2Node);

    //Update the id of the Dag in the right trapezoid
    map.getTrapezoid(rightTrapezoid).setIdDag(idRightTrapezoid);
}

}
