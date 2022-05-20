#include "trapezoid.h"

Trapezoid::Trapezoid(const cg3::Point2d& leftp, const cg3::Point2d& rightp,
                     const cg3::Segment2d& tops, const cg3::Segment2d& bottoms)
{
    leftP = leftp;
    rightP = rightp;
    topS = tops;
    bottomS = bottoms;
    topLeft = std::numeric_limits<size_t>::max();
    bottomLeft = std::numeric_limits<size_t>::max();
    topRight = std::numeric_limits<size_t>::max();
    bottomRight = std::numeric_limits<size_t>::max();
}

const cg3::Point2d& Trapezoid::getLeftP() const{
    return leftP;
}

const cg3::Point2d& Trapezoid::getRightP() const{
    return rightP;
}

const cg3::Segment2d& Trapezoid::getTopS() const{
    return topS;
}

const cg3::Segment2d& Trapezoid::getBottomS() const{
    return bottomS;
}

void Trapezoid::setLeftP(const cg3::Point2d& point){
    leftP = point;
}

void Trapezoid::setRightP(const cg3::Point2d& point){
    rightP = point;
}

void Trapezoid::setTopS(const cg3::Segment2d& segment){
    topS = segment;
}

void Trapezoid::setBottomS(const cg3::Segment2d& segment){
    bottomS = segment;
}

const size_t& Trapezoid::getTopLeft() const{
    return topLeft;
}

const size_t& Trapezoid::getBottomLeft() const{
    return bottomLeft;
}

const size_t& Trapezoid::getTopRight() const{
    return topRight;
}

const size_t& Trapezoid::getBottomRight() const{
    return bottomRight;
}

void Trapezoid::setTopLeft(const size_t& trapezoid){
    topLeft = trapezoid;
}

void Trapezoid::setBottomLeft(const size_t& trapezoid){
    bottomLeft = trapezoid;
}

void Trapezoid::setTopRight(const size_t& trapezoid){
    topRight = trapezoid;
}

void Trapezoid::setBottomRight(const size_t& trapezoid){
    bottomRight = trapezoid;
}

