#include "trapezoidalmap.h"


TrapezoidalMap::TrapezoidalMap()
{
    cg3::Segment2d topS = cg3::Segment2d(cg3::Point2d(MIN_DOUBLE, MAX_DOUBLE), cg3::Point2d(MAX_DOUBLE, MAX_DOUBLE));
    cg3::Segment2d bottomS = cg3::Segment2d(cg3::Point2d(MIN_DOUBLE, MIN_DOUBLE), cg3::Point2d(MAX_DOUBLE, MIN_DOUBLE));

    map = std::vector<Trapezoid>();

    Trapezoid boundingBox = Trapezoid(topS.p1(),bottomS.p2(),topS,bottomS);

    map.push_back(boundingBox);
}

const std::vector<Trapezoid>& TrapezoidalMap::getMap() const {
    return map;
}

void TrapezoidalMap::replaceTrapezoid(const size_t &oldTrapezoid, const Trapezoid &newTrapezoid){
    map[oldTrapezoid] = newTrapezoid;
}

size_t TrapezoidalMap::insertTrapezoid(const Trapezoid &newTrapezoid){
    map.push_back(newTrapezoid);
    return map.size()-1;
}

/**
 * @brief Split a trapezoid into four new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: left, right, top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::splitFour(const cg3::Segment2d& segment, const size_t& trapezoid){

    Trapezoid leftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), segment.p1(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid rightTrapezoid = Trapezoid(segment.p2(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());
    Trapezoid topTrapezoid = Trapezoid(segment.p1(), segment.p2(), map[trapezoid].getTopS(), segment);
    Trapezoid bottomTrapezoid = Trapezoid(segment.p1(), segment.p2(), segment, map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid, idRightTrapezoid;

    leftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    leftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    rightTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    rightTrapezoid.setTopRight(map[trapezoid].getTopRight());

    replaceTrapezoid(trapezoid,leftTrapezoid);

    bottomTrapezoid.setBottomLeft(trapezoid);
    topTrapezoid.setTopLeft(trapezoid);

    idTopTrapezoid = insertTrapezoid(topTrapezoid);
    idBottomTrapezoid = insertTrapezoid(bottomTrapezoid);

    map[trapezoid].setBottomRight(idBottomTrapezoid);
    map[trapezoid].setTopRight(idTopTrapezoid);

    rightTrapezoid.setBottomLeft(idBottomTrapezoid);
    rightTrapezoid.setTopLeft(idTopTrapezoid);

    idRightTrapezoid = insertTrapezoid(rightTrapezoid);

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
void TrapezoidalMap::splitTwo(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){
    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), segment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), segment, map[trapezoid].getBottomS());
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
void TrapezoidalMap::splitThreeRight(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){

    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), segment.p2(), map[trapezoid].getTopS(), segment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), segment.p2(), segment, map[trapezoid].getBottomS());

    Trapezoid rightTrapezoid = Trapezoid(segment.p2(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid, idRightTrapezoid;

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
void TrapezoidalMap::splitThreeLeft(const cg3::Segment2d& segment, const size_t& trapezoid){

    Trapezoid topTrapezoid = Trapezoid(segment.p1(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), segment);
    Trapezoid bottomTrapezoid = Trapezoid(segment.p1(), map[trapezoid].getRightP(), segment, map[trapezoid].getBottomS());
    Trapezoid LeftTrapezoid = Trapezoid(map[trapezoid].getLeftP(), segment.p1(), map[trapezoid].getTopS(), map[trapezoid].getBottomS());

    size_t idBottomTrapezoid, idTopTrapezoid, idLeftTrapezoid;

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

    map[map[rightTrapezoid].getTopRight()].setTopLeft(leftTrapezoid);
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
