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

    leftTrapezoid.setBottomLeft(map[trapezoid].getBottomLeft());
    leftTrapezoid.setTopLeft(map[trapezoid].getTopLeft());

    rightTrapezoid.setBottomRight(map[trapezoid].getBottomRight());
    rightTrapezoid.setTopRight(map[trapezoid].getTopRight());


    replaceTrapezoid(trapezoid,leftTrapezoid);

    map.push_back(rightTrapezoid);
    map.push_back(topTrapezoid);
    map.push_back(bottomTrapezoid);

}
