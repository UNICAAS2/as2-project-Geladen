#include <cg3/viewer/mainwindow.h>

#include "managers/trapezoidalmap_manager.h"
#include "data_structures/trapezoid.h"
#include "data_structures/trapezoidalmap.h"
#include "data_structures/dag.h"
#include "algorithms/algorithms.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>
using namespace Algorithms;

int main(int argc, char *argv[]) {

    cg3::Point2d punto1(3,3);
    cg3::Point2d punto2(6,3);
    cg3::Point2d punto3(2,1);
    cg3::Point2d punto4(8,1);
    cg3::Segment2d s1(punto1, punto2);
    cg3::Segment2d s2(punto3, punto4);
    cg3::Point2d punto5(3,3);
    cg3::Point2d punto6(9,8);
    cg3::Segment2d s3(punto5, punto6);
    //cg3::Point2d punto7(4,2);
    //cg3::Point2d punto8(6,3);
    cg3::Segment2d s4(punto3, punto1);

    TrapezoidalMap map = TrapezoidalMap();
    DagNode dnode= DagNode(0,DagNode::trapezoidNode,std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
    Dag dag = Dag(dnode);

    //updateMapAndDag(map,dag,s1);
    //updateMapAndDag(map,dag,s2);
    //updateMapAndDag(map,dag,s3);
    //updateMapAndDag(map,dag,s4);

    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

    QApplication app(argc, argv);

    //Main window, it contains QGLViewer canvas
    cg3::viewer::MainWindow gui;

    //Voronoi manager initialization
    TrapezoidalMapManager vm(&gui);
    gui.addManager(&vm, "Trapezoidal map Manager");

    //Show the GUI
    gui.updateCanvas();
    gui.show();

    return app.exec();
}
