#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/bounding_box2.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include "drawablepolygon.h"
#include "algorithms/algorithms.h"
#include <cg3/viewer/opengl_objects/opengl_objects2.h>

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{

private:
    std::vector<DrawablePolygon> polygons;

public:
    DrawableTrapezoidalMap();

    void draw() const;
    cg3::Point3d sceneCenter() const;
    double sceneRadius() const;
    //void replacePolygon(const size_t& oldPolygon, const DrawablePolygon& newPolygon);
    const cg3::Point2d calculatePoint(const double x, const cg3::Segment2d& segment) const;
    void update();
};


#endif // DRAWABLETRAPEZOIDALMAP_H
