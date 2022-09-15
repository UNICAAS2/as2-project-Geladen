#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/bounding_box2.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include "drawablepolygon.h"
#include "algorithms/algorithms.h"

class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject
{

private:
    std::vector<DrawablePolygon> polygons;

public:
    DrawableTrapezoidalMap();

    void draw() const;
    cg3::Point3d sceneCenter() const;
    double sceneRadius() const;
};


#endif // DRAWABLETRAPEZOIDALMAP_H
