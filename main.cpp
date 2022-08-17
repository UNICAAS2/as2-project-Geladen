#include <cg3/viewer/mainwindow.h>

#include "managers/trapezoidalmap_manager.h"
#include "data_structures/trapezoid.h"
#include "data_structures/trapezoidalmap.h"
#include <cg3/geometry/point2.h>
#include <cg3/geometry/segment2.h>

int main(int argc, char *argv[]) {

    cg3::Point2d punto1(30,50);
    cg3::Point2d punto2(80,60);
    cg3::Point2d punto3(10,90);
    cg3::Point2d punto4(80,60);
    cg3::Segment2d s1(punto1, punto2);
    cg3::Segment2d s2(punto3, punto4);
    //cg3::Point2d punto5(60,70);
    //cg3::Point2d punto6(90,60);
    //cg3::Segment2d s3(punto5, punto6);
    //Trapezoid trap(punto5,punto6,s1,s2);


    TrapezoidalMap map = TrapezoidalMap();
    size_t idtrap = map.getMap().size()-1;
    map.splitFour(s1, idtrap);
    map.splitThreeLeft(s2,0);
    map.splitTwo(s2,1,4,5);

    std::vector<size_t> trapezoids;

    trapezoids.push_back(0);
    trapezoids.push_back(4);
    trapezoids.push_back(5);
    trapezoids.push_back(1);
    trapezoids.push_back(6);
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
