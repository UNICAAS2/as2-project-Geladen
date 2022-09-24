#include "segmentutils.h"

namespace SegmentUtils {

/**
 * @brief If the x coordinate of p2 is greater than the x coordinate of p1, create a new segment with the swapped points
 * @param segment, the segment to check
 * @return the segment sorted by the x coordinate
 */
cg3::Segment2d sortSegment(const cg3::Segment2d& segment){

    if(segment.p1().x()> segment.p2().x()){
        cg3::Segment2d sortedSegment = cg3::Segment2d(segment.p2(),segment.p1());
        return sortedSegment;
    }
    else
        return segment;
}

}
