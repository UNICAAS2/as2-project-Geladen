#include "segmentutils.h"

namespace SegmentUtils {

cg3::Segment2d sortSegment(const cg3::Segment2d& segment){

    if(segment.p1().x()> segment.p2().x()){
        cg3::Segment2d sortedSegment = cg3::Segment2d(segment.p2(),segment.p1());
        return sortedSegment;
    }
    else
        return segment;
}

}
