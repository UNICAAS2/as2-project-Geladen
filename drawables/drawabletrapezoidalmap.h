#ifndef DRAWABLETRAPEZOIDALMAP_H
#define DRAWABLETRAPEZOIDALMAP_H

#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/bounding_box2.h>
#include <cg3/viewer/interfaces/drawable_object.h>
#include "drawablepolygon.h"
#include <cg3/viewer/opengl_objects/opengl_objects2.h>
#include <random>

#define MIN_RANGE_RGB 75
#define MAX_RGB 245
#define MIN_RGB 0

/**
 * @brief This class manages the graphic part of the trapezoidal map. It's composed of a vector of Drawable polygon
 */
class DrawableTrapezoidalMap : public TrapezoidalMap, public cg3::DrawableObject {

private:

    std::vector<DrawablePolygon> polygons;
    size_t selectedPolygon;

public:

    DrawableTrapezoidalMap();

    void draw() const;
    cg3::Point3d sceneCenter() const;
    double sceneRadius() const;

    void update();
    void clear();

    double roundValue(const double x) const;
    const cg3::Point2d calculatePoint(const double x, const cg3::Segment2d& segment) const;

    void setSelectedPolygon(const size_t idPolygon);
};


#endif // DRAWABLETRAPEZOIDALMAP_H
