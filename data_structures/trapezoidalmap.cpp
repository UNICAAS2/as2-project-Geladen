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
void TrapezoidalMap::SplitFour(const cg3::Segment2d& segment, const size_t& trapezoid){

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

    idBottomTrapezoid = insertTrapezoid(topTrapezoid);
    idTopTrapezoid = insertTrapezoid(bottomTrapezoid);

    map[trapezoid].setBottomRight(idBottomTrapezoid);
    map[trapezoid].setTopRight(idTopTrapezoid);

    rightTrapezoid.setBottomLeft(idBottomTrapezoid);
    rightTrapezoid.setTopLeft(idTopTrapezoid);

    idRightTrapezoid = insertTrapezoid(rightTrapezoid);

    map[idTopTrapezoid].setTopRight(idRightTrapezoid);
    map[idBottomTrapezoid].setBottomRight(idRightTrapezoid);

}

/**
 * @brief Split a trapezoid into two new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::SplitTwo(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){
    Trapezoid topTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), map[trapezoid].getTopS(), segment);
    Trapezoid bottomTrapezoid = Trapezoid(map[trapezoid].getLeftP(), map[trapezoid].getRightP(), segment, map[trapezoid].getBottomS());


    topTrapezoid.setTopLeft(map[trapezoid].getTopLeft());
    topTrapezoid.setTopRight(map[trapezoid].getTopRight());
    topTrapezoid.setBottomLeft(topAdjacent);

    bottomTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    bottomTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    bottomTrapezoid.setTopLeft(bottomAdjacent);

    replaceTrapezoid(trapezoid, topTrapezoid);
    insertTrapezoid(bottomTrapezoid);
}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, right
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::SplitThreeRight(const cg3::Segment2d& segment, const size_t& trapezoid, const size_t& topAdjacent, const size_t&  bottomAdjacent){

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
}

/**
 * @brief Split a trapezoid into three new trapezoids
 * Given a new segment and the id of a trapezoid in the Trapezoidal Map returns four new trapezoids: top, bottom, left
 * @param segment, the new segment inserted.
 * @param trapezoid, id of the trapezoid that contains the new segment.
 */
void TrapezoidalMap::SplitThreeLeft(const cg3::Segment2d& segment, const size_t& trapezoid){

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
}
