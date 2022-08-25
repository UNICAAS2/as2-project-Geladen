#include <cg3/viewer/mainwindow.h>

#include "managers/trapezoidalmap_manager.h"
#include "data_structures/trapezoid.h"
#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>

int main(int argc, char *argv[]) {

    cg3::Point2d punto1(2,2);
    cg3::Point2d punto2(4,2);
    cg3::Point2d punto3(1,1);
    cg3::Point2d punto4(5,1);
    cg3::Segment2d s1(punto1, punto2);
    cg3::Segment2d s2(punto3, punto4);
    cg3::Point2d punto5(1,1);
    cg3::Point2d punto6(4,2);
    cg3::Segment2d s3(punto5, punto6);
    //Trapezoid trap(punto5,punto6,s1,s2);


    TrapezoidalMap map = TrapezoidalMap();
    size_t idtrap = map.getMap().size()-1;
    map.insertPoint(punto1);
    map.insertPoint(punto2);
    map.insertSegment(s1);

    std::vector<size_t> newTrapezoids;
    map.splitFour(idtrap, newTrapezoids);

    map.insertPoint(punto3);
    map.insertPoint(punto4);
    map.insertSegment(s2);

    map.splitThreeLeft(0);
    map.splitTwo(2,4,5);
    map.splitThreeRight(3,2,6);

    std::vector<size_t> trapezoids;

    trapezoids.push_back(0);
    trapezoids.push_back(4);
    trapezoids.push_back(5);
    trapezoids.push_back(2);
    trapezoids.push_back(6);
    trapezoids.push_back(7);
    trapezoids.push_back(8);
    trapezoids.push_back(3);
    //trapezoids.push_back(std::numeric_limits<size_t>::max());

    map.mergeTrapezoids(trapezoids);

    map.insertPoint(punto5);
    map.insertPoint(punto6);
    map.insertSegment(s3);

    map.splitTwo(4,std::numeric_limits<size_t>::max(),std::numeric_limits<size_t>::max());
    map.splitTwo(2,4,9);

    trapezoids.clear();
    trapezoids.push_back(std::numeric_limits<size_t>::max());
    trapezoids.push_back(4);
    trapezoids.push_back(9);
    trapezoids.push_back(2);
    trapezoids.push_back(10);
    trapezoids.push_back(std::numeric_limits<size_t>::max());

    map.mergeTrapezoids(trapezoids);

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
