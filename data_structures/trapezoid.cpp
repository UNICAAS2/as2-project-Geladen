#include "trapezoid.h"

/**
 * @brief Trapezoid's constructor.
 * @param leftp, the left point of the trapezoid
 * @param rightp, the right point of the trapezoid
 * @param tops, the top segment of the trapezoid
 * @param bottoms, the bottom segment of the trapezoid
 */

Trapezoid::Trapezoid(const size_t& leftp, const size_t& rightp,
                     const size_t& tops, const size_t& bottoms)
{
    leftP = leftp;
    rightP = rightp;
    topS = tops;
    bottomS = bottoms;
    topLeft = std::numeric_limits<size_t>::max();
    bottomLeft = std::numeric_limits<size_t>::max();
    topRight = std::numeric_limits<size_t>::max();
    bottomRight = std::numeric_limits<size_t>::max();
    idDag = std::numeric_limits<size_t>::max();
}

const size_t& Trapezoid::getLeftP() const{
    return leftP;
}

const size_t& Trapezoid::getRightP() const{
    return rightP;
}

const size_t& Trapezoid::getTopS() const{
    return topS;
}

const size_t& Trapezoid::getBottomS() const{
    return bottomS;
}

void Trapezoid::setLeftP(const size_t& point){
    leftP = point;
}

void Trapezoid::setRightP(const size_t& point){
    rightP = point;
}

void Trapezoid::setTopS(const size_t& segment){
    topS = segment;
}

void Trapezoid::setBottomS(const size_t& segment){
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

const size_t& Trapezoid::getIdDag() const{
    return idDag;
}

void Trapezoid::setIdDag(const size_t& id){
    idDag = id;
}

