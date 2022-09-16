#include "trapezoidalmap.h"

/**
 * @brief TrapezoidalMap's contructor.
 */
TrapezoidalMap::TrapezoidalMap()
{
    size_t idP1, idP2, idP3, idP4, idTopS, idBottomS;
    points = std::vector<cg3::Point2d>();
    segments = std::vector<cg3::Segment2d>();
    map = std::vector<Trapezoid>();

    cg3::Point2d p1 = cg3::Point2d(-BOUNDINGBOX, BOUNDINGBOX);
    cg3::Point2d p2 = cg3::Point2d(BOUNDINGBOX, BOUNDINGBOX);
    cg3::Point2d p3 = cg3::Point2d(-BOUNDINGBOX, -BOUNDINGBOX);
    cg3::Point2d p4 = cg3::Point2d(BOUNDINGBOX, -BOUNDINGBOX);

    cg3::Segment2d topS = cg3::Segment2d(p1, p2);
    cg3::Segment2d bottomS = cg3::Segment2d(p3, p4);

    idP1 = insertPoint(p1);
    idP2 = insertPoint(p2);
    idP3 = insertPoint(p3);
    idP4 = insertPoint(p4);

    idTopS = insertSegment(topS);
    idBottomS = insertSegment(bottomS);

    Trapezoid boundingBox = Trapezoid(idP1,idP4,idTopS,idBottomS);
    boundingBox.setIdDag(0);

    map.push_back(boundingBox);
}

/**
 * @brief Set the newTrapezoid vector with the lastest added or modified trapezoids
 * @param trapezoids, the last added or modified trapezoids
 */
void TrapezoidalMap::setNewTrapezoids(std::vector<size_t> trapezoids){

    for(size_t i=0;i<trapezoids.size();i++){
        if(trapezoids[i] != std::numeric_limits<size_t>::max())
            newTrapezoids.push_back(trapezoids[i]);
    }
}

/**
 * @brief Return the vector of trapzoids as a reference
 */
const std::vector<Trapezoid>& TrapezoidalMap::getMap() const {
    return map;
}

/**
 * @brief Replace a trapedoid in the map with a new one
 * @param oldTtrapezoid, the id of the trapazoid to be replaced
 * @param newTrapezoid, the trapezoid to be inserted in the map
 */
void TrapezoidalMap::replaceTrapezoid(const size_t& oldTrapezoid, const Trapezoid &newTrapezoid){
    map[oldTrapezoid] = newTrapezoid;
}

/**
 * @brief Return the point as a reference
 * @param idPoint, the id of the point
 */
const cg3::Point2d& TrapezoidalMap::getPoint(const size_t& idPoint) const{
    return points[idPoint];
}

/**
 * @brief Return the segment as a reference
 * @param idSegment, the id of the segment
 */
const cg3::Segment2d& TrapezoidalMap::getSegment(const size_t& idSegment) const{
    return segments[idSegment];
}

/**
 * @brief Return the trapezoid as a reference
 * @param idTrapezoid, the id of the trapezoid
 */
Trapezoid& TrapezoidalMap::getTrapezoid(const size_t& idTrapezoid){
    return map[idTrapezoid];
}

/**
 * @brief Return the trapezoid as a reference
 * @param idTrapezoid, the id of the trapezoid
 */
const Trapezoid& TrapezoidalMap::getTrapezoid(const size_t& idTrapezoid) const{
    return map[idTrapezoid];
}

/**
 * @brief Insert a new point in the vector of points if it isn't alredy present
 * @param newPoint, the new point to be inserted
 * @return the position of the new point in the vector of points
 */
size_t TrapezoidalMap::insertPoint(const cg3::Point2d& newPoint){

    std::unordered_map<cg3::Point2d, size_t>::iterator it = pointMap.find(newPoint);

    //Point already in the data structure
    if (it != pointMap.end()) {
        return it->second;
    }
    //Point not in the data structure
    else {
        pointMap.insert(std::make_pair(newPoint, points.size()));
        points.push_back(newPoint);
        return points.size()-1;
    }
}

/**
 * @brief Insert a new segment into the vector of segments
 * @param newSegment, the new segment to insert
 * @return the index of the segment in the vector
 */
size_t TrapezoidalMap::insertSegment(const cg3::Segment2d& newSegment){
    segments.push_back(newSegment);
    return segments.size()-1;
}

/**
 * @brief Insert a new trapezoid in the vector of trapezoid at the end of the vector if there aren't free indexes
 * @param newTrapezoid, the new trapezoid to be inserted
 * @return the position of the new trapezoid in the vector of trapezoids
 */
size_t TrapezoidalMap::insertTrapezoid(const Trapezoid& newTrapezoid){

    size_t index;

    if(emptyIndexes.size() != 0){
        index = emptyIndexes[emptyIndexes.size()-1];
        emptyIndexes.pop_back();
        replaceTrapezoid(index,newTrapezoid);
        return index;
    }
    else{
        map.push_back(newTrapezoid);
        return map.size()-1;
    }
}


/**
 * @brief Return the size of the vector of trapezoids
 */
size_t TrapezoidalMap::getMapSize() const{
    return map.size();
}

/**
 * @brief Return the size of the vector of segments
 */
size_t TrapezoidalMap::getSegmentsSize() const{
    return segments.size();
}

/**
 * @brief Return the size of the vector of points
 */
size_t TrapezoidalMap::getPointsSize() const{
    return points.size();
}

/**
 * @brief Split a trapezoid into four new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: left, right, top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitFour(const size_t& trapezoid, std::vector<size_t>& trapezoids, const size_t& idP1, const size_t& idP2){

    size_t idSegment;

    idSegment = segments.size()-1;

    Trapezoid leftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP1, map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid rightTrapezoid = Trapezoid(idP2, map[trapezoid].getRightP(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid topTrapezoid = Trapezoid(idP1, idP2, map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(idP1, idP2, idSegment, map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid, idRightTrapezoid;

    leftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    leftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    leftTrapezoid.setIdDag(map[trapezoid].getIdDag());
    rightTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    rightTrapezoid.setTopRight(map[trapezoid].getTopRight());

    replaceTrapezoid(trapezoid,leftTrapezoid);

    bottomTrapezoid.setBottomLeft(trapezoid);
    topTrapezoid.setTopLeft(trapezoid);

    trapezoids.push_back(trapezoid); //pusha l'id nel vettore da rendere

    idTopTrapezoid = insertTrapezoid(topTrapezoid);
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);
    trapezoids.push_back(idTopTrapezoid);
    trapezoids.push_back(idBottomTrapezoid);

    map[trapezoid].setBottomRight(idBottomTrapezoid);
    map[trapezoid].setTopRight(idTopTrapezoid);

    rightTrapezoid.setBottomLeft(idBottomTrapezoid);
    rightTrapezoid.setTopLeft(idTopTrapezoid);

    idRightTrapezoid = insertTrapezoid(rightTrapezoid);
    trapezoids.push_back(idRightTrapezoid);

    map[idTopTrapezoid].setTopRight(idRightTrapezoid);
    map[idBottomTrapezoid].setBottomRight(idRightTrapezoid);


    if(rightTrapezoid.getTopRight() != std::numeric_limits<size_t>::max())
        map[rightTrapezoid.getTopRight()].setTopLeft(idRightTrapezoid);

    if(rightTrapezoid.getBottomRight() != std::numeric_limits<size_t>::max())
        map[rightTrapezoid.getBottomRight()].setBottomLeft(idRightTrapezoid);

}

/**
 * @brief Split a trapezoid into two new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitTwo(const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent, std::vector<size_t>& trapezoids){

    size_t idSegment;

    idSegment = segments.size()-1;

    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), idSegment, map[trapezoid].getBottomS());
    size_t idBottomTrapezoid;

    topTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    topTrapezoid.setTopRight(map[trapezoid].getTopRight());
    topTrapezoid.setBottomLeft(topAdjacent);
    topTrapezoid.setIdDag(map[trapezoid].getIdDag());


    bottomTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    bottomTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    bottomTrapezoid.setTopLeft(bottomAdjacent);

    replaceTrapezoid(trapezoid, topTrapezoid);
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);

    if(topAdjacent != std::numeric_limits<size_t>::max()){
        map[topAdjacent].setBottomRight(trapezoid);
        map[bottomAdjacent].setTopRight(idBottomTrapezoid);
    }

    if(topTrapezoid.getTopLeft() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopLeft()].setTopRight(trapezoid);

    if(bottomTrapezoid.getBottomLeft() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomLeft()].setBottomRight(idBottomTrapezoid);

    if(topTrapezoid.getTopRight() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopRight()].setTopLeft(trapezoid);

    if(bottomTrapezoid.getBottomRight() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomRight()].setBottomLeft(idBottomTrapezoid);

    trapezoids.push_back(trapezoid);
    trapezoids.push_back(idBottomTrapezoid);
}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, right
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitThreeRight(const size_t& trapezoid, const size_t& topAdjacent, const size_t& bottomAdjacent, std::vector<size_t>& trapezoids, const size_t& idP2){

    size_t  idSegment;

    //idP2 = points.size()-1;
    idSegment = segments.size()-1;

    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP2, map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP2, idSegment, map[trapezoid].getBottomS());
    Trapezoid rightTrapezoid = Trapezoid(idP2, map[trapezoid].getRightP(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid;

    topTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    topTrapezoid.setBottomLeft(topAdjacent);
    topTrapezoid.setTopRight(trapezoid);
    idTopTrapezoid = insertTrapezoid(topTrapezoid);

    bottomTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    bottomTrapezoid.setTopLeft(bottomAdjacent);
    bottomTrapezoid.setBottomRight(trapezoid);
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);

    rightTrapezoid.setBottomLeft(idBottomTrapezoid);
    rightTrapezoid.setTopLeft(idTopTrapezoid);
    rightTrapezoid.setTopRight(map[trapezoid].getTopRight());
    rightTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    rightTrapezoid.setIdDag(map[trapezoid].getIdDag());

    replaceTrapezoid(trapezoid,rightTrapezoid);

    if(topAdjacent != std::numeric_limits<size_t>::max())
        map[topAdjacent].setBottomRight(idTopTrapezoid);
    if(bottomAdjacent != std::numeric_limits<size_t>::max())
        map[bottomAdjacent].setTopRight(idBottomTrapezoid);

    if(topTrapezoid.getTopLeft() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopLeft()].setTopRight(idTopTrapezoid);

    if(bottomTrapezoid.getBottomLeft() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomLeft()].setBottomRight(idBottomTrapezoid);

    trapezoids.push_back(idTopTrapezoid);
    trapezoids.push_back(idBottomTrapezoid);
    trapezoids.push_back(trapezoid);
}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, left
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitThreeLeft(const size_t& trapezoid, std::vector<size_t>& trapezoids, const size_t& idP1){

    size_t  idSegment;

    //idP1 = points.size()-2;
    idSegment = segments.size()-1;

    Trapezoid topTrapezoid = Trapezoid(idP1, map[trapezoid].getRightP(), map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(idP1, map[trapezoid].getRightP(), idSegment, map[trapezoid].getBottomS());
    Trapezoid leftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP1, map[trapezoid].getTopS(), map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid;

    topTrapezoid.setTopLeft(trapezoid);
    topTrapezoid.setTopRight(map[trapezoid].getTopRight());
    idTopTrapezoid = insertTrapezoid(topTrapezoid);

    bottomTrapezoid.setBottomLeft(trapezoid);
    bottomTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);

    leftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    leftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    leftTrapezoid.setTopRight(idTopTrapezoid);
    leftTrapezoid.setBottomRight(idBottomTrapezoid);
    leftTrapezoid.setIdDag(map[trapezoid].getIdDag());

    replaceTrapezoid(trapezoid,leftTrapezoid);

    if(topTrapezoid.getTopRight() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopRight()].setTopLeft(idTopTrapezoid);

    if(bottomTrapezoid.getBottomRight() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomRight()].setBottomLeft(idBottomTrapezoid);

    trapezoids.push_back(trapezoid);
    trapezoids.push_back(idTopTrapezoid);
    trapezoids.push_back(idBottomTrapezoid);
}


/**
 * @brief Given two trapezoids the method merges the trapezoids in the left one, updating the map
 * @param leftTrapezoid, the geometrically leftmost trapezoids.
 * @param rightTrapezoid, the geometrically rightmost trapezoids.
 */
void TrapezoidalMap::mergeTwoTrapezoids(const size_t& leftTrapezoid, const size_t& rightTrapezoid){

    map[leftTrapezoid].setRightP(map[rightTrapezoid].getRightP());

    map[leftTrapezoid].setTopRight(map[rightTrapezoid].getTopRight());
    map[leftTrapezoid].setBottomRight(map[rightTrapezoid].getBottomRight());

    size_t index = map[rightTrapezoid].getTopRight();
    if(index != std::numeric_limits<size_t>::max())
        map[index].setTopLeft(leftTrapezoid);

    if(map[rightTrapezoid].getBottomRight() != std::numeric_limits<size_t>::max())
        map[map[rightTrapezoid].getBottomRight()].setBottomLeft(leftTrapezoid);
}

/**
 * @brief Given a vector of trapezoids the method performs all possible merges, updating the map and the input vector
 * @param trapezoids, the vector that contains all the trapezoids obtained after splits.
 */
void TrapezoidalMap::mergeTrapezoids(std::vector<size_t>& trapezoids){
    size_t i =1;

    while( i<trapezoids.size() - 4 ){
        if(map[trapezoids[i]].getTopRight() == map[trapezoids[i]].getBottomRight()){
            mergeTwoTrapezoids(trapezoids[i], trapezoids[i + OFFSIDE_NEXT_TOP]);
            emptyIndexes.push_back(trapezoids[i + OFFSIDE_NEXT_TOP]);

            trapezoids[i + OFFSIDE_NEXT_TOP] = trapezoids[i];
        }
        else{
            mergeTwoTrapezoids(trapezoids[i + OFFSIDE_BOTTOM], trapezoids[i + OFFSIDE_NEXT_BOTTOM]);
            emptyIndexes.push_back(trapezoids[i + OFFSIDE_NEXT_BOTTOM]);

            trapezoids[i + OFFSIDE_NEXT_BOTTOM] = trapezoids[i + OFFSIDE_BOTTOM];
        }
        i += OFFSIDE_NEXT_TOP;
    }
}


/**
 * @brief Clear alla the vectors used in the trapezoidal map
 */
void TrapezoidalMap::clear(){
    emptyIndexes.clear();
    newTrapezoids.clear();
    map.clear();
    segments.clear();
    points.clear();
    pointMap.clear();
}
