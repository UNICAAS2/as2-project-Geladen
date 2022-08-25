#include "trapezoidalmap.h"


TrapezoidalMap::TrapezoidalMap()
{
    size_t idP1, idP2, idP3, idP4, idTopS, idBottomS;
    points = std::vector<cg3::Point2d>();
    segments = std::vector<cg3::Segment2d>();
    map = std::vector<Trapezoid>();

    cg3::Point2d p1 = cg3::Point2d(MIN_DOUBLE, MAX_DOUBLE);
    cg3::Point2d p2 = cg3::Point2d(MIN_DOUBLE, MAX_DOUBLE);
    cg3::Point2d p3 = cg3::Point2d(MIN_DOUBLE, MIN_DOUBLE);
    cg3::Point2d p4 = cg3::Point2d(MAX_DOUBLE, MIN_DOUBLE);

    cg3::Segment2d topS = cg3::Segment2d(p1, p2);
    cg3::Segment2d bottomS = cg3::Segment2d(p3, p4);

    idP1 = insertPoint(p1);
    idP2 = insertPoint(p2);
    idP3 = insertPoint(p3);
    idP4 = insertPoint(p4);

    idTopS = insertSegment(topS);
    idBottomS = insertSegment(bottomS);

    Trapezoid boundingBox = Trapezoid(idP1,idP4,idTopS,idBottomS);

    map.push_back(boundingBox);
}

const std::vector<Trapezoid>& TrapezoidalMap::getMap() const {
    return map;
}

void TrapezoidalMap::replaceTrapezoid(const size_t &oldTrapezoid, const Trapezoid &newTrapezoid){
    map[oldTrapezoid] = newTrapezoid;
}


const cg3::Point2d TrapezoidalMap::getPoint(const size_t& idPoint) const{
    return points[idPoint];
}

const cg3::Segment2d TrapezoidalMap::getSegment(const size_t& idSegment) const{
    return segments[idSegment];
}

Trapezoid TrapezoidalMap::getTrapezoid(const size_t& idTrapezoid) const{
    return map[idTrapezoid];
}


size_t TrapezoidalMap::insertPoint(const cg3::Point2d& newPoint){
    points.push_back(newPoint);
    return points.size()-1;
}

size_t TrapezoidalMap::insertSegment(const cg3::Segment2d& newSegment){
    segments.push_back(newSegment);
    return segments.size()-1;
}

size_t TrapezoidalMap::insertTrapezoid(const Trapezoid& newTrapezoid){
    map.push_back(newTrapezoid);
    return map.size()-1;
}

size_t TrapezoidalMap::getMapSize(){
    return map.size();
}

size_t TrapezoidalMap::getSegmentsSize(){
    return segments.size();
}

size_t TrapezoidalMap::getPointsSize(){
    return points.size();
}

/**
 * @brief Split a trapezoid into four new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: left, right, top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitFour(const size_t& trapezoid, std::vector<size_t>& trapezoids){

    size_t idP1,idP2, idSegment;

    idP1 = points.size()-2;
    idP2 = points.size()-1;
    idSegment = segments.size()-1;

    Trapezoid leftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP1, map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid rightTrapezoid = Trapezoid(idP2, map[trapezoid].getRightP(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid topTrapezoid = Trapezoid(idP1, idP2, map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(idP1, idP2, idSegment, map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid, idRightTrapezoid;

    leftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    leftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
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
        map[topTrapezoid.getTopRight()].setTopLeft(idRightTrapezoid);

    if(rightTrapezoid.getBottomRight() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomRight()].setBottomLeft(idRightTrapezoid);

}

/**
 * @brief Split a trapezoid into two new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitTwo(const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){

    size_t idSegment;

    idSegment = segments.size()-1;

    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), idSegment, map[trapezoid].getBottomS());
    size_t idBottomTrapezoid;

    topTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    topTrapezoid.setTopRight(map[trapezoid].getTopRight());
    topTrapezoid.setBottomLeft(topAdjacent);

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
}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, right
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitThreeRight(const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){

    size_t idP2, idSegment;

    idP2 = points.size()-1;
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
    replaceTrapezoid(trapezoid,rightTrapezoid);

    map[topAdjacent].setBottomRight(idTopTrapezoid);
    map[bottomAdjacent].setTopRight(idBottomTrapezoid);

    if(topTrapezoid.getTopLeft() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopLeft()].setTopRight(idTopTrapezoid);

    if(bottomTrapezoid.getBottomLeft() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomLeft()].setBottomRight(idBottomTrapezoid);

}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, left
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitThreeLeft(const size_t& trapezoid){

    size_t idP1, idSegment;

    idP1 = points.size()-2;
    idSegment = segments.size()-1;

    Trapezoid topTrapezoid = Trapezoid(idP1, map[trapezoid].getRightP(), map[trapezoid].getTopS(), idSegment);
    Trapezoid bottomTrapezoid = Trapezoid(idP1, map[trapezoid].getRightP(), idSegment, map[trapezoid].getBottomS());
    Trapezoid LeftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), idP1, map[trapezoid].getTopS(), map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid;

    topTrapezoid.setTopLeft(trapezoid);
    topTrapezoid.setTopRight(map[trapezoid].getTopRight());
    idTopTrapezoid = insertTrapezoid(topTrapezoid);

    bottomTrapezoid.setBottomLeft(trapezoid);
    bottomTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);

    LeftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    LeftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    LeftTrapezoid.setTopRight(idTopTrapezoid);
    LeftTrapezoid.setBottomRight(idBottomTrapezoid);
    replaceTrapezoid(trapezoid,LeftTrapezoid);


    if(topTrapezoid.getTopRight() != std::numeric_limits<size_t>::max())
        map[topTrapezoid.getTopRight()].setTopLeft(idTopTrapezoid);

    if(bottomTrapezoid.getBottomRight() != std::numeric_limits<size_t>::max())
        map[bottomTrapezoid.getBottomRight()].setBottomLeft(idBottomTrapezoid);
}


/**
 * @brief Merge 2 trapezoids
 * Given two trapezoids the method merge the trapezoids in the left one, updating the map
 * @param leftTrapezoid, the geometrically leftmost trapezoids.
 * @param rightTrapezoid, the geometrically rightmost trapezoids.
 */
void TrapezoidalMap::mergeTwoTrapezoids(const size_t& leftTrapezoid, const size_t& rightTrapezoid){

    map[leftTrapezoid].setRightP(map[rightTrapezoid].getRightP());

    map[leftTrapezoid].setTopRight(map[rightTrapezoid].getTopRight());
    map[leftTrapezoid].setBottomRight(map[rightTrapezoid].getBottomRight());

    size_t index = map[rightTrapezoid].getTopRight();
    map[index].setTopLeft(leftTrapezoid);

    map[map[rightTrapezoid].getBottomRight()].setBottomLeft(leftTrapezoid);
}

/**
 * @brief Merge trapezoids from the vector
 * Given a vector of trapezoids the method performs all possible merges, updating the map and the input vector
 * @param trapezoids, the vector that contains all the trapezoids obtained after splits.
 */
void TrapezoidalMap::mergeTrapezoids(std::vector<size_t>& trapezoids){
    size_t i =1, k;
    std::vector<size_t> indexesToUpdate;

    while( i<trapezoids.size() - 4 ){
        if(map[trapezoids[i]].getTopRight() == map[trapezoids[i]].getBottomRight()){
            mergeTwoTrapezoids(trapezoids[i], trapezoids[i + OFFISIDE_NEXT_TOP]);
            emptyIndexes.push_back(trapezoids[i + OFFISIDE_NEXT_TOP]);

            if(trapezoids[indexesToUpdate.size()-1] == i){
                indexesToUpdate.push_back(i + OFFISIDE_NEXT_TOP);
                for(k=0;k<indexesToUpdate.size();k++)
                    trapezoids[indexesToUpdate[k]] = trapezoids[i];
            }
            else{
                indexesToUpdate.clear();
                indexesToUpdate.push_back(i);
                indexesToUpdate.push_back(i + OFFISIDE_NEXT_TOP);
                for(k=0;k<indexesToUpdate.size();k++)
                    trapezoids[indexesToUpdate[k]] = trapezoids[i];
            }
        }
        else{
            mergeTwoTrapezoids(trapezoids[i + OFFISIDE_BOTTOM], trapezoids[i + OFFISIDE_NEXT_BOTTOM]);
            emptyIndexes.push_back(trapezoids[i + OFFISIDE_NEXT_BOTTOM]);

            if(trapezoids[indexesToUpdate.size()-1] == i + OFFISIDE_BOTTOM){
                indexesToUpdate.push_back(i + OFFISIDE_NEXT_BOTTOM);
                for(k=0;k<indexesToUpdate.size();k++)
                    trapezoids[indexesToUpdate[k]] = trapezoids[i + OFFISIDE_BOTTOM];
            }
            else{
                indexesToUpdate.clear();
                indexesToUpdate.push_back(i + OFFISIDE_BOTTOM);
                indexesToUpdate.push_back(i + OFFISIDE_NEXT_BOTTOM);
                for(k=0;k<indexesToUpdate.size();k++)
                    trapezoids[indexesToUpdate[k]] = trapezoids[i + OFFISIDE_BOTTOM];
            }
        }
        i+=2;
    }
}
