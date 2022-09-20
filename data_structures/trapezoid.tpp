#include "trapezoid.h"

/**
 * @brief Return the left point of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getLeftP() const{
    return leftP;
}

/**
 * @brief Return the right point of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getRightP() const{
    return rightP;
}

/**
 * @brief Return the top segment of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getTopS() const{
    return topS;
}

/**
 * @brief Return the bottom segment of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getBottomS() const{
    return bottomS;
}

/**
 * @brief Set the left point of the trapezoid
 */
inline void Trapezoid::setLeftP(const size_t& point){
    leftP = point;
}

/**
 * @brief Set the right point of the trapezoid
 */
inline void Trapezoid::setRightP(const size_t& point){
    rightP = point;
}

/**
 * @brief Set the top segment of the trapezoid
 */
inline void Trapezoid::setTopS(const size_t& segment){
    topS = segment;
}

/**
 * @brief Set the bottom segment of the trapezoid
 */
inline void Trapezoid::setBottomS(const size_t& segment){
    bottomS = segment;
}

/**
 * @brief Return the top left neighbor of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getTopLeft() const{
    return topLeft;
}

/**
 * @brief Return the bottom left neighbor of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getBottomLeft() const{
    return bottomLeft;
}

/**
 * @brief Return the top right neighbor of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getTopRight() const{
    return topRight;
}

/**
 * @brief Return the bottom right neighbor of the trapezoid as a reference
 */
inline const size_t& Trapezoid::getBottomRight() const{
    return bottomRight;
}

/**
 * @brief Set the top left neighbor of the trapezoid
 */
inline void Trapezoid::setTopLeft(const size_t& trapezoid){
    topLeft = trapezoid;
}

/**
 * @brief Set the bottom left neighbor of the trapezoid
 */
inline void Trapezoid::setBottomLeft(const size_t& trapezoid){
    bottomLeft = trapezoid;
}

/**
 * @brief Set the top right neighbor of the trapezoid
 */
inline void Trapezoid::setTopRight(const size_t& trapezoid){
    topRight = trapezoid;
}

/**
 * @brief Set the bottom right neighbor of the trapezoid
 */
inline void Trapezoid::setBottomRight(const size_t& trapezoid){
    bottomRight = trapezoid;
}

/**
 * @brief Return the ID of the trapezoid in the DAG
 */
inline const size_t& Trapezoid::getIdDag() const{
    return idDag;
}

/**
 * @brief Set the ID of the trapezoid in the DAG
 */
inline void Trapezoid::setIdDag(const size_t& id){
    idDag = id;
}
