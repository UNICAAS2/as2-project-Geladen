#include "drawabletrapezoidalmap.h"

/**
 * @brief DrawableTrapezodaialMap's contructor
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap()
{
    TrapezoidalMap();
    polygons = std::vector<DrawablePolygon>();

}

/**
 * @brief draw trapezoids and vertical lines
 */
void DrawableTrapezoidalMap::draw() const{

        for (size_t i=0;i<polygons.size();i++) {
            if(polygons[i].getIsDeleted() == false){
                if(polygons[i].getTopLeftPoint() == polygons[i].getBottomLeftPoint())
                    cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),polygons[i].getColor(),1,true);
                else if(polygons[i].getTopRightPoint() == polygons[i].getBottomRightPoint())
                    cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomLeftPoint(),polygons[i].getColor(),1,true);
                else
                    cg3::opengl::drawQuad2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),polygons[i].getBottomLeftPoint(),polygons[i].getColor(),1,true);
            }
        }
}
/**
 * @brief the vector of DrawablePolygons is updated with the new points calculated after inserting a new segment
 */
void DrawableTrapezoidalMap::update() {
    for (size_t i=0;i<newTrapezoids.size();i++){

        DrawablePolygon polygon = DrawablePolygon(calculatePoint(points[map[newTrapezoids[i]].getLeftP()].x(), segments[map[newTrapezoids[i]].getTopS()]),
                                           calculatePoint(points[map[newTrapezoids[i]].getLeftP()].x(), segments[map[newTrapezoids[i]].getBottomS()]),
                                           calculatePoint(points[map[newTrapezoids[i]].getRightP()].x(), segments[map[newTrapezoids[i]].getTopS()]),
                                           calculatePoint(points[map[newTrapezoids[i]].getRightP()].x(), segments[map[newTrapezoids[i]].getBottomS()]));

        if(newTrapezoids[i] >= polygons.size()){
            polygons.push_back(polygon);
        }
        else{
            polygons[newTrapezoids[i]] = polygon;
        }
    }
    for (size_t i=0;i<emptyIndexes.size();i++){
        polygons[emptyIndexes[i]].setIsDeleted(true);
    }
    newTrapezoids.clear();
}


cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return cg3::Point3d(boundingBox.center().x(), boundingBox.center().y(), 0);
}

double DrawableTrapezoidalMap::sceneRadius() const{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return boundingBox.diag();
}


/**
 * @brief find the y obtained from the intersection of a segment and a x coordinate
 * @param x, the x of which to find the y
 * @param segment, the segment of which to find the y
 */
const cg3::Point2d DrawableTrapezoidalMap::calculatePoint(const double x, const cg3::Segment2d& segment) const{
    double y;
    cg3::Point2d p1 = segment.p1();
    cg3::Point2d p2 = segment.p2();
    y = (x-p1.x())/(p2.x()-p1.x()) * (p2.y()-p1.y()) +p1.y();

    return cg3::Point2d(x,y);
}

