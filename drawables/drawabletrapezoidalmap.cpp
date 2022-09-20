#include "drawabletrapezoidalmap.h"
#include "cg3/utilities/timer.h"

/**
 * @brief DrawableTrapezodaialMap's contructor
 */
DrawableTrapezoidalMap::DrawableTrapezoidalMap():
    polygons(std::vector<DrawablePolygon>()),
    selectedPolygon(std::numeric_limits<size_t>::max())
{
    TrapezoidalMap(); // super
    polygons.push_back(DrawablePolygon(points[0],points[1],points[2],points[3],cg3::Color(MAX_RGB,MAX_RGB,MAX_RGB)));
}

/**
 * @brief draw trapezoids and vertical lines
 */
void DrawableTrapezoidalMap::draw() const{

        for (size_t i=0;i<polygons.size();i++) {

            if(i == selectedPolygon){
                if(polygons[i].getIsDeleted() == false){
                    if(polygons[i].getTopLeftPoint() == polygons[i].getBottomLeftPoint()){
                        cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }else if(polygons[i].getTopRightPoint() == polygons[i].getBottomRightPoint()){
                        cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopLeftPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }else{
                        cg3::opengl::drawQuad2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                        cg3::opengl::drawLine2(polygons[i].getTopLeftPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }
                }
            }
            else{
                if(polygons[i].getIsDeleted() == false){
                    if(polygons[i].getTopLeftPoint() == polygons[i].getBottomLeftPoint()){
                        cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),polygons[i].getColor(),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }else if(polygons[i].getTopRightPoint() == polygons[i].getBottomRightPoint()){
                        cg3::opengl::drawTriangle2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomLeftPoint(),polygons[i].getColor(),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopLeftPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }else{
                        cg3::opengl::drawQuad2(polygons[i].getTopLeftPoint(),polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),polygons[i].getBottomLeftPoint(),polygons[i].getColor(),1,true);
                        cg3::opengl::drawLine2(polygons[i].getTopRightPoint(),polygons[i].getBottomRightPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                        cg3::opengl::drawLine2(polygons[i].getTopLeftPoint(),polygons[i].getBottomLeftPoint(),cg3::Color(MIN_RGB,MIN_RGB,MIN_RGB),3);
                    }
                }
            }
        }
}

/**
 * @brief the vector of DrawablePolygons is updated with the new points calculated after inserting a new segment
 */
void DrawableTrapezoidalMap::update() {

    std::minstd_rand0 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(MIN_RANGE_RGB,MAX_RGB);

    cg3::Point2d topLeft,bottomLeft,topRight,bottomRight;

    for (size_t i=0;i<newTrapezoids.size();i++){


        if(segments[map[newTrapezoids[i]].getTopS()].p1() != points[map[newTrapezoids[i]].getLeftP()])
            topLeft = calculatePoint(points[map[newTrapezoids[i]].getLeftP()].x(), segments[map[newTrapezoids[i]].getTopS()]);
        else
            topLeft = points[map[newTrapezoids[i]].getLeftP()];

        if(segments[map[newTrapezoids[i]].getBottomS()].p1() != points[map[newTrapezoids[i]].getLeftP()])
            bottomLeft = calculatePoint(points[map[newTrapezoids[i]].getLeftP()].x(), segments[map[newTrapezoids[i]].getBottomS()]);
        else
            bottomLeft = points[map[newTrapezoids[i]].getLeftP()];

        if(segments[map[newTrapezoids[i]].getTopS()].p2() != points[map[newTrapezoids[i]].getRightP()])
            topRight = calculatePoint(points[map[newTrapezoids[i]].getRightP()].x(), segments[map[newTrapezoids[i]].getTopS()]);
        else
            topRight = points[map[newTrapezoids[i]].getRightP()];

        if(segments[map[newTrapezoids[i]].getBottomS()].p2() != points[map[newTrapezoids[i]].getRightP()])
            bottomRight = calculatePoint(points[map[newTrapezoids[i]].getRightP()].x(), segments[map[newTrapezoids[i]].getBottomS()]);
        else
            bottomRight = points[map[newTrapezoids[i]].getRightP()];

        DrawablePolygon polygon = DrawablePolygon(topLeft, bottomLeft, topRight, bottomRight,cg3::Color(dist(rng),dist(rng),dist(rng)));

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
 * @brief truncates the value to 6 decimal digits
 * @param x, the value to be rounded
 */
double DrawableTrapezoidalMap::roundValue(const double x) const {
    double n =  (static_cast<long long int> (x*10*6)) /(10*6);
    return n;
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

    return cg3::Point2d(roundValue(x),roundValue(y));
}

/**
 * @brief Set the id of the polygon that the user selected with the query point
 * @param idPolygon, the id of the selected polygon
 */
void DrawableTrapezoidalMap::setSelectedPolygon(const size_t idPolygon){
    selectedPolygon = idPolygon;
}

/**
 * @brief clear the memory used in the trapwzoidal map
 */
void DrawableTrapezoidalMap::clear(){
    polygons.clear();
    TrapezoidalMap::clear();
}
