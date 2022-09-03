#include "drawabletrapezoidalmap.h"

DrawableTrapezoidalMap::DrawableTrapezoidalMap()
{
}

void DrawableTrapezoidalMap::draw() const {

}

cg3::Point3d DrawableTrapezoidalMap::sceneCenter() const{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();

    return cg3::Point3d(boundingBox.center().x(), boundingBox.center().y(), 0);
}

double DrawableTrapezoidalMap::sceneRadius() const{
    const cg3::BoundingBox2& boundingBox = cg3::BoundingBox2();
    return boundingBox.diag();
}

